/***********************************************
 * This file is part of RabbitMQ C++ Connector *
 * See LICENSE file for details                *
 *                                             *
 * @author Moisés Maciá <mmacia@gmail.com>     *
 ***********************************************/

#include "Channel.hpp"

namespace ideup { namespace amqp {
////////////////////////////////////////////////////////////////////////////////////////////


Channel::Channel(Connection* conn) :
  conn_(conn)
{
  amqp_channel_open(conn_->getConnection(), conn_->getChannel());
}


Channel::~Channel()
{
  if (conn_->getChannel() > 0 && conn_->getConnection() != 0) {
    // close channel
    amqp_rpc_reply_t ret = amqp_channel_close(conn_->getConnection(), conn_->getChannel(), AMQP_REPLY_SUCCESS);

    if (ret.reply_type != AMQP_RESPONSE_NORMAL) {
      throw Exception("Error closing channel.", ret, __FILE__, __LINE__);
    }
  }
}


Queue::ptr_t Channel::declareQueue(const string& name)
{
  auto args = Queue::arguments_t();
  return sendDeclareCommand(name, args);
}


Queue::ptr_t Channel::declareQueue(const string& name, Queue::arguments_t& args)
{
  return sendDeclareCommand(name, args);
}


Queue::ptr_t Channel::sendDeclareCommand(const string& name, Queue::arguments_t& args)
{
  if (!name.size()) {
    throw Exception("The queue must have a name", __FILE__, __LINE__);
  }

  amqp_queue_declare_ok_t* r = amqp_queue_declare(
      conn_->getConnection(),
      conn_->getChannel(),
      amqp_cstring_bytes(name.c_str()),
      args.test(QUEUE_PASSIVE) ? 1 : 0,
      args.test(QUEUE_DURABLE) ? 1 : 0,
      args.test(QUEUE_EXCLUSIVE) ? 1 : 0,
      args.test(QUEUE_AUTO_DELETE) ? 1 : 0,
      amqp_empty_table);

  amqp_rpc_reply_t ret = amqp_get_rpc_reply(conn_->getConnection());

  if (ret.reply_type != AMQP_RESPONSE_NORMAL) {
    throw Exception("Error declaring queue.", ret, __FILE__, __LINE__);
  }

  if (r->queue.bytes == NULL) {
    throw Exception("Out of memory while copying queue name.", __FILE__, __LINE__);
  }

  return make_shared<Queue>(*this, string(static_cast<char*>(r->queue.bytes), r->queue.len));
}


void Channel::bindQueue(const string& queue_name, const string& exchange_name, const string& routing_key)
{
  sendBindCommand(queue_name, exchange_name, routing_key);
}


void Channel::sendBindCommand(const string& queue_name, const string& exchange_name, const string& routing_key)
{
  amqp_queue_bind(
      conn_->getConnection(),
      conn_->getChannel(),
      amqp_cstring_bytes(queue_name.c_str()),
      amqp_cstring_bytes(exchange_name.c_str()),
      amqp_cstring_bytes(routing_key.c_str()),
      amqp_empty_table);

  amqp_rpc_reply_t ret = amqp_get_rpc_reply(conn_->getConnection());

  if (ret.reply_type != AMQP_RESPONSE_NORMAL) {
    stringstream ss;
    ss << "Cannot bind queue \"" << queue_name << "\" to exchange \"" << exchange_name
       << "\" with key \"" << routing_key << "\".";
    throw Exception(ss.str(), ret, __FILE__, __LINE__);
  }
}


void Channel::unbindQueue(const string& queue_name, const string& exchange_name, const string& routing_key)
{
  sendUnbindCommand(queue_name, exchange_name, routing_key);
}


void Channel::sendUnbindCommand(const string& queue_name, const string& exchange_name, const string& routing_key)
{
  amqp_queue_unbind(
      conn_->getConnection(),
      conn_->getChannel(),
      amqp_cstring_bytes(queue_name.c_str()),
      amqp_cstring_bytes(exchange_name.c_str()),
      amqp_cstring_bytes(routing_key.c_str()),
      amqp_empty_table);

  amqp_rpc_reply_t ret = amqp_get_rpc_reply(conn_->getConnection());

  if (ret.reply_type != AMQP_RESPONSE_NORMAL) {
    stringstream ss;
    ss << "Cannot unbind queue \"" << queue_name << "\" to exchange \"" << exchange_name
       << "\" with key \"" << routing_key << "\".";
    throw Exception(ss.str(), ret, __FILE__, __LINE__);
  }
}


void Channel::basicConsume(Queue::ptr_t& queue)
{
  auto args = Queue::consumer_args_t();
  basicConsume(queue, args);
}


void Channel::basicConsume(Queue::ptr_t& queue, Queue::consumer_args_t& args)
{
  sendBasicConsumeCommand(queue, args);
}


void Channel::sendBasicConsumeCommand(Queue::ptr_t& queue, Queue::consumer_args_t& args)
{
  amqp_basic_consume(
      conn_->getConnection(),
      conn_->getChannel(),
      amqp_cstring_bytes(queue->getName().c_str()),
      amqp_cstring_bytes(queue->getConsumerTag().c_str()),
      args.test(CONSUMER_NO_LOCAL) ? 1 : 0,
      args.test(CONSUMER_NO_ACK) ? 1 : 0,
      args.test(CONSUMER_EXCLUSIVE) ? 1 : 0,
      amqp_empty_table);

  amqp_rpc_reply_t ret = amqp_get_rpc_reply(conn_->getConnection());

  if (ret.reply_type != AMQP_RESPONSE_NORMAL) {
    throw Exception("Unable to send consume command", ret, __FILE__, __LINE__);
  }

  int result;

  while (true) {
    amqp_frame_t frame;
    amqp_maybe_release_buffers(conn_->getConnection());

    result = amqp_simple_wait_frame(conn_->getConnection(), &frame);
    if (result < 0) {
      throw Exception("Error in header frame", __FILE__, __LINE__);
    }

    if (frame.frame_type != AMQP_FRAME_METHOD) {
      continue;
    }

    // TODO implement cancel message

    if (frame.payload.method.id != AMQP_BASIC_DELIVER_METHOD) {
      continue;
    }

    // TODO fetch message metadata

    result = amqp_simple_wait_frame(conn_->getConnection(), &frame);
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
      result = amqp_simple_wait_frame(conn_->getConnection(), &frame);
      if (result < 0) {
        return;
      }

      if (frame.frame_type != AMQP_FRAME_BODY) {
        throw Exception("Expected body frame!", __FILE__, __LINE__);
      }

      void* body_ptr = reinterpret_cast<char*>(body.bytes) + body_received;

      memcpy(body_ptr, frame.payload.body_fragment.bytes, frame.payload.body_fragment.len);
      body_received += frame.payload.body_fragment.len;
    }

    Message msg(static_cast<char*>(body.bytes), body.len);
    amqp_bytes_free(body);

    queue->notify(msg); // notify observers
  }
}


void Channel::deleteQueue(Queue::ptr_t& queue)
{
  auto args = Queue::delete_args_t();
  deleteQueue(queue, args);
}

void Channel::deleteQueue(Queue::ptr_t& queue, Queue::delete_args_t& args)
{
  sendDeleteQueue(queue->getName(), args);
}


void Channel::sendDeleteQueue(const string& queue_name, Queue::delete_args_t& args)
{
  amqp_queue_delete(
      conn_->getConnection(),
      conn_->getChannel(),
      amqp_cstring_bytes(queue_name.c_str()),
      args.test(QUEUE_IF_UNUSED) ? 1 : 0,
      args.test(QUEUE_IF_EMPTY) ? 1 : 0);

  amqp_rpc_reply_t ret = amqp_get_rpc_reply(conn_->getConnection());

  if (ret.reply_type != AMQP_RESPONSE_NORMAL) {
    throw Exception("Error deleting queue.", ret, __FILE__, __LINE__);
  }
}


void Channel::basicCancel(const string& consumer_tag)
{
  sendBasicCancel(consumer_tag);
}


void Channel::sendBasicCancel(const string& consumer_tag)
{
  amqp_method_number_t replies[2] = { AMQP_BASIC_CANCEL_OK_METHOD, 0 };
  amqp_basic_cancel_t req;
  req.consumer_tag = amqp_cstring_bytes(consumer_tag.c_str());
  req.nowait = 0;

  amqp_rpc_reply_t ret = amqp_simple_rpc(
      conn_->getConnection(),
      conn_->getChannel(),
      AMQP_BASIC_CANCEL_METHOD,
      replies,
      &req);

  if (ret.reply_type != AMQP_RESPONSE_NORMAL) {
    throw Exception("Error canceling queue.", ret, __FILE__, __LINE__);
  }
}


void Channel::purgeQueue(Queue::ptr_t& queue, bool no_wait)
{
  sendPurgeQueueCommand(queue->getName(), no_wait);
}


void Channel::sendPurgeQueueCommand(const string& queue_name, bool no_wait)
{
  amqp_queue_delete_t s;

  memset(&s, 0, sizeof(s));
  s.ticket = 0;
  s.queue = amqp_cstring_bytes(queue_name.c_str());
  s.nowait = no_wait;

  amqp_method_number_t method_ok = AMQP_QUEUE_PURGE_OK_METHOD;

  amqp_rpc_reply_t ret = amqp_simple_rpc(
      conn_->getConnection(),
      conn_->getChannel(),
      AMQP_QUEUE_PURGE_METHOD,
      &method_ok,
      &s);

  if (ret.reply_type != AMQP_RESPONSE_NORMAL) {
    throw Exception("Error purging queue.", ret, __FILE__, __LINE__);
  }
}


////////////////////////////////////////////////////////////////////////////////////////////
}}
