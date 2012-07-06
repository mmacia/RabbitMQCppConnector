/***********************************************
 * This file is part of RabbitMQ C++ Connector *
 * See LICENSE file for details                *
 *                                             *
 * @author Moisés Maciá <mmacia@gmail.com>     *
 ***********************************************/

#include "Message.hpp"

namespace ideup { namespace amqp {
////////////////////////////////////////////////////////////////////////////////////////////


Message::Message(const string& message)
{
  body_ = message;
}

Message::~Message()
{
  // TODO Implement me!
}


string Message::getBody() const
{
  return body_;
}


void Message::addProperty(const string& name, const string& value)
{
  // TODO implement properties setter
}


const amqp_basic_properties_t* Message::getProperties() const
{
  return &props_;
}


////////////////////////////////////////////////////////////////////////////////////////////
}}
