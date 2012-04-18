/***********************************************
 * This file is part of RabbitMQ C++ Connector *
 * See LICENSE file for details                *
 *                                             *
 * @author Moisés Maciá <mmacia@gmail.com>     *
 ***********************************************/

#include "Channel.hpp"

namespace ideup { namespace amqp {
////////////////////////////////////////////////////////////////////////////////////////////


Channel::Channel()
{
}


Channel::~Channel()
{
}


Queue::ptr_t Channel::declareQueue(const string& name)
{
  return nullptr;
}


void Channel::close()
{
  // TODO implement me!
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
