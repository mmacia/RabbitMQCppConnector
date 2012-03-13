/***********************************************
 * This file is part of RabbitMQ C++ Connector *
 * See LICENSE file for details                *
 *                                             *
 * @author Moisés Maciá <mmacia@gmail.com>     *
 ***********************************************/

#include "Queue.hpp"

namespace ideup { namespace amqp {
////////////////////////////////////////////////////////////////////////////////////////////

Queue::Queue(amqp_connection_state_t conn, int channel_number, const string& name) :
  name_(name),
  channel_number_(channel_number),
  conn_(conn)
{
  openChannel();
}


Queue::~Queue()
{
  closeChannel();

  // clean up attached observers
  if (!observers_.empty()) {
    for (auto i = observers_.begin(); i != observers_.end(); ++i) {
      delete (Observer*)*i;
    }

    observers_.clear();
  }
}


void Queue::closeChannel()
{
  amqp_rpc_reply_t ret = amqp_channel_close(conn_, channel_number_, AMQP_REPLY_SUCCESS);

  if (ret.reply_type != AMQP_RESPONSE_NORMAL) {
    throw Exception("Error closing channel.", ret, __FILE__, __LINE__);
  }
}


void Queue::openChannel()
{
  amqp_channel_open(conn_, channel_number_);
}


void Queue::declare()
{
  auto arguments = bitset<numQueueArgs>();
  sendDeclareCommand(arguments);
}


void Queue::declare(bitset<numQueueArgs>& queue_args)
{
  sendDeclareCommand(queue_args);
}


void Queue::sendDeclareCommand(bitset<numQueueArgs>& arguments)
{
  if (!name_.size()) {
    throw Exception("The queue must have a name", __FILE__, __LINE__);
  }

  amqp_queue_declare_ok_t* r = amqp_queue_declare(
      conn_,
      channel_number_,
      amqp_cstring_bytes(name_.c_str()),
      arguments.test(QUEUE_PASSIVE) ? 1 : 0,
      arguments.test(QUEUE_DURABLE) ? 1 : 0,
      arguments.test(QUEUE_EXCLUSIVE) ? 1 : 0,
      arguments.test(QUEUE_AUTO_DELETE) ? 1 : 0,
      amqp_empty_table);

  amqp_rpc_reply_t ret = amqp_get_rpc_reply(conn_);

  if (ret.reply_type != AMQP_RESPONSE_NORMAL) {
    throw Exception("Error declaring queue.", ret, __FILE__, __LINE__);
  }

  amqp_bytes_t queue_name = amqp_bytes_malloc_dup(r->queue);

  if (queue_name.bytes == NULL) {
    throw Exception("Out of memory while copying queue name.", __FILE__, __LINE__);
  }

  amqp_bytes_free(queue_name);
}


void Queue::bind(const string& exchange_name, const string& key)
{
  sendBindCommand(exchange_name, key);
}


void Queue::sendBindCommand(const string& exchange_name, const string& key)
{
  amqp_queue_bind(
      conn_,
      channel_number_,
      amqp_cstring_bytes(name_.c_str()),
      amqp_cstring_bytes(exchange_name.c_str()),
      amqp_cstring_bytes(key.c_str()),
      amqp_empty_table);

  amqp_rpc_reply_t ret = amqp_get_rpc_reply(conn_);

  if (ret.reply_type != AMQP_RESPONSE_NORMAL) {
    stringstream ss;
    ss << "Cannot bind queue to exchange \"" << exchange_name << "\" with key \"" << key << "\".";
    throw Exception(ss.str(), ret, __FILE__, __LINE__);
  }
}


void Queue::consume()
{
  bitset<numConsumerArgs> args;
  consume(args);
}


void Queue::consume(bitset<numConsumerArgs>& consumer_args)
{
  sendConsumeCommand(consumer_args);
}


void Queue::sendConsumeCommand(bitset<numConsumerArgs>& arguments)
{
  amqp_basic_consume(
      conn_,
      channel_number_,
      amqp_cstring_bytes(name_.c_str()),
      amqp_cstring_bytes(consumer_tag_.c_str()),
      arguments.test(CONSUMER_NO_LOCAL) ? 1 : 0,
      arguments.test(CONSUMER_NO_ACK) ? 1 : 0,
      arguments.test(CONSUMER_EXCLUSIVE) ? 1 : 0,
      amqp_empty_table);

  amqp_rpc_reply_t ret = amqp_get_rpc_reply(conn_);

  if (ret.reply_type != AMQP_RESPONSE_NORMAL) {
    throw Exception("Unable to send consume command", ret, __FILE__, __LINE__);
  }

  amqp_frame_t frame;
  int result;

  while (true) {
    amqp_maybe_release_buffers(conn_);

    result = amqp_simple_wait_frame(conn_, &frame);
    if (result < 0) {
      return;
    }

    if (frame.frame_type != AMQP_FRAME_METHOD) {
      continue;
    }

    // TODO implement cancel message

    if (frame.payload.method.id != AMQP_BASIC_DELIVER_METHOD) {
      continue;
    }

    // TODO fetch message metadata

    result = amqp_simple_wait_frame(conn_, &frame);
    if (result < 0) {
      throw Exception("Message frame is invalid!", __FILE__, __LINE__);
    }

    if (frame.frame_type != AMQP_FRAME_HEADER) {
      throw Exception("Expected header!", __FILE__, __LINE__);
    }

    // TODO fetch headers

    size_t body_size = frame.payload.properties.body_size;
    size_t body_received = 0;

    amqp_bytes_t body = amqp_bytes_malloc(body_size);

    while (body_received < body_size) {
      result = amqp_simple_wait_frame(conn_, &frame);
      if (result < 0) {
        return;
      }

      if (frame.frame_type != AMQP_FRAME_BODY) {
        throw Exception("Expected body!", __FILE__, __LINE__);
      }

      memcpy(
          (void*)((size_t)body.bytes + body_received),
          frame.payload.body_fragment.bytes,
          frame.payload.body_fragment.len);

      body_received += frame.payload.body_fragment.len;
    }

    string body_str(static_cast<char*>(body.bytes), body.len);
    amqp_bytes_free(body);

    notify(body_str); // notify observers
  }
}


void Queue::notify(const string& message) const
{
  for (auto i = observers_.begin(); i != observers_.end(); ++i) {
    auto observer = (Observer*)*i;
    observer->update(message);
  }
}


void Queue::attach(Observer* obs)
{
  obs->subject(this);
  observers_.push_back(obs);
}


////////////////////////////////////////////////////////////////////////////////////////////
}}
