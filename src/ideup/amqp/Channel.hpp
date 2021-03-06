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

#ifndef __IDEUP_AMQP_CHANNEL_HPP__
#define __IDEUP_AMQP_CHANNEL_HPP__

#include "common.hpp"
#include "Queue.hpp"
#include "Exception.hpp"
#include "Connection.hpp"
#include "Message.hpp"
#include "Exchange.hpp"
#include <librabbitmq/amqp.h>
#include <librabbitmq/amqp_framing.h>
#include <bitset>


namespace ideup { namespace amqp {
/////////////////////////////////////////////////////////////////////////////////////

using namespace std;

class Connection;

/**
 *
 * @author Moisés Maciá <mmacia@gmail.com>
 */
class Channel
{
  public:
    /**
     * Default constructor
     *
     * @param[in] conn RabbitMQ connection object
     */
    Channel(Connection* conn);
    /**
     * Default destructor
     */
    virtual ~Channel();


    /**
     * Creates a new exchange in RabbitMQ server
     *
     * Note that exchange type must be one of theese parameters: direct, fanout or topic. Otherwise Exception will be
     * thrown.
     *
     * @param[in] name Exchange name.
     * @param[in] type Exchange type.
     */
    void declareExchange(const string& name, const string& type);
    /**
     * Creates a new exchange in RabbitMQ server
     *
     * @param[in] name Exchange name.
     * @param[in] type Exchange type.
     * @param[in] args Declaration arguments.
     *
     * @see {Channel::declareExchange}
     */
    void declareExchange(const string& name, const string& type, Exchange::arguments_t args);

    /**
     * Creates a new queue in RabbitMQ server
     *
     * @param[in] name Queue name.
     */
    Queue::ptr_t declareQueue(const string& name);
    /**
     * Creates a new queue in RabbitMQ server
     *
     * @param[in] name Queue name.
     * @param[in] args Declaration arguments.
     */
    Queue::ptr_t declareQueue(const string& name, Queue::arguments_t& args);

    void deleteQueue(Queue::ptr_t& queue);
    void deleteQueue(Queue::ptr_t& queue, Queue::delete_args_t& args);
    void bindQueue(const string& queue_name, const string& exchange_name, const string& routing_key = "");
    void unbindQueue(const string& queue_name, const string& exchange_name, const string& routing_key = "");
    void purgeQueue(Queue::ptr_t& queue, bool no_wait = false);
    /*void basicAck();*/

    /**
     * Publish a new message through given exchange name
     *
     * @param[in] message Message enclosure.
     * @param[in] exchange_name Exchange name.
     */
    void basicPublish(Message::ptr_t message, const string& exchange_name);
    void basicPublish(Message::ptr_t message, const string& exchange_name, const string& routing_key);
    void basicPublish(Message::ptr_t message, const string& exchange_name, const string& routing_key, Queue::publisher_args_t args);

    void basicConsume(Queue::ptr_t& queue);
    void basicConsume(Queue::ptr_t& queue, Queue::consumer_args_t& args);

    void basicCancel(const string& consumer_tag);

  protected:
  private:
    Connection* conn_;

    void         sendDeclareExchangeCommand(const string& name, const string& type, Exchange::arguments_t& args);
    Queue::ptr_t sendDeclareCommand(const string& name, Queue::arguments_t& args);
    void         sendBindCommand(const string& queue_name, const string& exchange_name, const string& routing_key);
    void         sendUnbindCommand(const string& queue_name, const string& exchange_name, const string& routing_key);
    void         sendBasicConsumeCommand(Queue::ptr_t& queue, Queue::consumer_args_t& args);
    void         sendBasicPublishCommand(Message::ptr_t message, const string& exchange_name, const string& routing_key, Queue::publisher_args_t& args);
    void         sendDeleteQueue(const string& queue_name, Queue::delete_args_t& args);
    void         sendBasicCancel(const string& consumer_tag);
    void         sendPurgeQueueCommand(const string& queue_name, bool no_wait);
};

/////////////////////////////////////////////////////////////////////////////////////
}}

#endif //__IDEUP_AMQP_CHANNEL_HPP__
