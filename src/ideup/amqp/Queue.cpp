/***********************************************
 * This file is part of RabbitMQ C++ Connector *
 * See LICENSE file for details                *
 *                                             *
 * @author Moisés Maciá <mmacia@gmail.com>     *
 ***********************************************/

#include "Queue.hpp"

namespace ideup { namespace amqp {
////////////////////////////////////////////////////////////////////////////////////////////

Queue::Queue(const Channel& channel, const string& name) :
  channel_(channel),
  name_(name)
{
}


Queue::~Queue()
{
  // clean up attached observers
  /*if (!observers_.empty()) {
    for (auto i = observers_.begin(); i != observers_.end(); ++i) {
      delete (Observer*)*i;
    }

    observers_.clear();
  }*/
}


/*void Queue::unbind(const string& exchange_name, const string& key)
{
  sendUnbindCommand(exchange_name, key);
}*/


/*void Queue::sendUnbindCommand(const string& exchange_name, const string& key)
{
  amqp_queue_unbind(
      conn_,
      channel_number_,
      amqp_cstring_bytes(name_.c_str()),
      amqp_cstring_bytes(exchange_name.c_str()),
      amqp_cstring_bytes(key.c_str()),
      amqp_empty_table);

  amqp_rpc_reply_t ret = amqp_get_rpc_reply(conn_);

  if (ret.reply_type != AMQP_RESPONSE_NORMAL) {
    stringstream ss;
    ss << "Cannot unbind queue to exchange \"" << exchange_name << "\" with key \"" << key << "\".";
    throw Exception(ss.str(), ret, __FILE__, __LINE__);
  }
}*/


/*void Queue::sendConsumeCommand(bitset<numConsumerArgs>& arguments)
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

    Message body_str(static_cast<char*>(body.bytes), body.len);
    amqp_bytes_free(body);

    notify(body_str); // notify observers
  }
}*/


/*void Queue::notify(Message& message) const
{
  for (auto i = observers_.begin(); i != observers_.end(); ++i) {
    auto observer = (Observer*)*i;
    observer->update(message);
  }
}*/


void Queue::attach(Observer* obs)
{
  obs->subject(this);
  observers_.push_back(obs);
}


////////////////////////////////////////////////////////////////////////////////////////////
}}
