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


////////////////////////////////////////////////////////////////////////////////////////////
}}
