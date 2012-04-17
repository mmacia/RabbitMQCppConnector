/***********************************************
 * This file is part of RabbitMQ C++ Connector *
 * See LICENSE file for details                *
 *                                             *
 * @author Moisés Maciá <mmacia@gmail.com>     *
 ***********************************************/

#include "Message.hpp"

namespace ideup { namespace amqp {
////////////////////////////////////////////////////////////////////////////////////////////


Message::Message(const char* message, int len)
{
  body_ = string(message, len);
}

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


////////////////////////////////////////////////////////////////////////////////////////////
}}
