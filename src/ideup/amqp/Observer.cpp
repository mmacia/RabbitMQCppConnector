/***********************************************
 * This file is part of RabbitMQ C++ Connector *
 * See LICENSE file for details                *
 *                                             *
 * @author Moisés Maciá <mmacia@gmail.com>     *
 ***********************************************/

#include "Observer.hpp"

namespace ideup { namespace amqp {
////////////////////////////////////////////////////////////////////////////////////////////

Observer::Observer()
{
}


Observer::~Observer()
{
}


void Observer::update(const string& message)
{
}


void Observer::subject(Queue* subject)
{
  if (!subject_) {
    subject_ = subject;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
}}
