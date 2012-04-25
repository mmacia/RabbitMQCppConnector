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
  name_(name),
  consumer_tag_("")
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


void Queue::notify(Message& message) const
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
