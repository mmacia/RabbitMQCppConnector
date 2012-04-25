/***********************************************
 * This file is part of RabbitMQ C++ Connector *
 * See LICENSE file for details                *
 *                                             *
 * @author Moisés Maciá <mmacia@gmail.com>     *
 ***********************************************/

#include "Channel.hpp"

namespace ideup { namespace amqp {
////////////////////////////////////////////////////////////////////////////////////////////


Channel::Channel(const amqp_connection_state_t& conn, const int number) :
  conn_(conn),
  number_(number)
{
  amqp_channel_open(conn_, number_);
}


Channel::~Channel()
{
  // close channel
  amqp_rpc_reply_t ret = amqp_channel_close(conn_, number_, AMQP_REPLY_SUCCESS);

  if (ret.reply_type != AMQP_RESPONSE_NORMAL) {
    throw Exception("Error closing channel.", ret, __FILE__, __LINE__);
  }
}


Queue::ptr_t Channel::declareQueue(const string& name)
{
  auto args = Queue::arguments_t();
  return sendDeclareCommand(name, args);
}


Queue::ptr_t Channel::declareQueue(const string& name, Queue::arguments_t args)
{
  return sendDeclareCommand(name, args);
}


Queue::ptr_t Channel::sendDeclareCommand(const string& name, Queue::arguments_t& args)
{
  if (!name.size()) {
    throw Exception("The queue must have a name", __FILE__, __LINE__);
  }

  amqp_queue_declare_ok_t* r = amqp_queue_declare(
      conn_,
      number_,
      amqp_cstring_bytes(name.c_str()),
      args.test(QUEUE_PASSIVE) ? 1 : 0,
      args.test(QUEUE_DURABLE) ? 1 : 0,
      args.test(QUEUE_EXCLUSIVE) ? 1 : 0,
      args.test(QUEUE_AUTO_DELETE) ? 1 : 0,
      amqp_empty_table);

  amqp_rpc_reply_t ret = amqp_get_rpc_reply(conn_);

  if (ret.reply_type != AMQP_RESPONSE_NORMAL) {
    throw Exception("Error declaring queue.", ret, __FILE__, __LINE__);
  }

  if (r->queue.bytes == NULL) {
    throw Exception("Out of memory while copying queue name.", __FILE__, __LINE__);
  }

  return make_shared<Queue>(*this, string(static_cast<char*>(r->queue.bytes), r->queue.len));
}


void Channel::basicConsume(Queue::ptr_t& queue)
{
}

////////////////////////////////////////////////////////////////////////////////////////////
}}
