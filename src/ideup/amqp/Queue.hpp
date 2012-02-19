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
#include "Subject.hpp"
#include "Base.hpp"
#include <librabbitmq/amqp.h>


namespace ideup { namespace amqp {
/////////////////////////////////////////////////////////////////////////////////////

using namespace std;

enum AMQPEvents {
  AMQP_MESSAGE,
  AMQP_SIGUSR,
  AMQP_CANCEL,
  AMQP_CLOSE_CHANNEL
};


class Queue : public Base, public Subject
{
  public:
    Queue(amqp_connection_state_t conn, int channel_number, const string& name);
    ~Queue();


  protected:
  private:
};

/////////////////////////////////////////////////////////////////////////////////////
}}

#endif //__IDEUP_AMQP_QUEUE_HPP__
