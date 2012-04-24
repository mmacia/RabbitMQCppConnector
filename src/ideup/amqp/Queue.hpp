/***********************************************
 * This file is part of RabbitMQ C++ Connector *
 * See LICENSE file for details                *
 *                                             *
 * @author Moisés Maciá <mmacia@gmail.com>     *
 ***********************************************/

/*************************************************************
* Copyright (c) 2012 Moisés Maciá Guilló
*
* Permission is hereby granted, free of charge, to any
* person obtaining a copy of this software and associated
* documentation files (the "Software"), to deal in the
* Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the
* Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice
* shall be included in all copies or substantial portions of
* the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
* KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
* PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
* OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
* OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*************************************************************/

#ifndef __IDEUP_AMQP_QUEUE_HPP__
#define __IDEUP_AMQP_QUEUE_HPP__

#include "common.hpp"
#include "Message.hpp"
#include "Observer.hpp"
#include "Exception.hpp"
#include "Base.hpp"
#include <librabbitmq/amqp.h>
#include <librabbitmq/amqp_framing.h>
#include <bitset>


namespace ideup { namespace amqp {
/////////////////////////////////////////////////////////////////////////////////////

class Observer;

using namespace std;

enum Events {
  AMQP_MESSAGE,
  AMQP_SIGUSR,
  AMQP_CANCEL,
  AMQP_CLOSE_CHANNEL
};

/*enum QueueArg {
  QUEUE_PASSIVE,
  QUEUE_DURABLE,
  QUEUE_EXCLUSIVE,
  QUEUE_AUTO_DELETE,
  numQueueArgs
};*/

enum ConsumerArg {
  CONSUMER_NO_LOCAL,
  CONSUMER_NO_ACK,
  CONSUMER_EXCLUSIVE,
  numConsumerArgs
};


class Queue : public Base
{
  public:
    typedef shared_ptr<Queue> ptr_t;

    Queue(amqp_connection_state_t conn, int channel_number, const string& name);
    ~Queue();

    //void declare(bitset<numQueueArgs>& queue_args);
    void declare();
    void bind(const string& exchange_name, const string& key);
    void unbind(const string& exchange_name, const string& key);
    //void basicConsume(bitset<numConsumerArgs>& consumer_args);
    void basicConsume();
    void setConsumerTag(const string& tag) { consumer_tag_ = tag; };
    string getConsumerTag() { return consumer_tag_; };
    void attach(Observer* obs);
    void notify(Message& message) const;
    string name() const { return name_; };

  protected:
  private:
    string                  consumer_tag_;
    string                  name_;
    int                     channel_number_;
    amqp_connection_state_t conn_;
    vector<Observer*>       observers_;

    //void sendDeclareCommand(bitset<numQueueArgs>& arguments);
    void sendBindCommand(const string& exchange_name, const string& key);
    void sendUnbindCommand(const string& exchange_name, const string& key);
    //void sendConsumeCommand(bitset<numConsumerArgs>& arguments);
    void openChannel();
    void closeChannel();
};

/////////////////////////////////////////////////////////////////////////////////////
}}

#endif //__IDEUP_AMQP_QUEUE_HPP__
