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
  return nullptr;
}


Queue::ptr_t Channel::declareQueue(const string& name, QueueArguments args)
{
  return nullptr;
}


void Channel::basicConsume(Queue::ptr_t& queue)
{
}

/*Queue* AMQP::createQueue(const string& name)
{
  if (!isConnected()) {
    throw Exception("Not connected to RabbitMQ server!", __FILE__, __LINE__);
  }

  int channel_number = channels_.size() + 1;
  Queue* q = new Queue(conn_, channel_number, name);

  channels_.push_back(q);
  return q;
}*/
////////////////////////////////////////////////////////////////////////////////////////////
}}
