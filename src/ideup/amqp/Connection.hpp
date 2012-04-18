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

#ifndef __IDEUP_AMQP_CONNECTION_HPP_
#define __IDEUP_AMQP_CONNECTION_HPP_

#include <string>
#include <librabbitmq/amqp.h>
#include <librabbitmq/amqp_framing.h>
#include "Channel.hpp"


namespace ideup { namespace amqp {
///////////////////////////////////////////////////////////////////////////////////////////

/**
 * class Connection
 *
 * @author Moisés Maciá <mmacia@gmail.com>
 */
class Connection
{
  public:
    typedef shared_ptr<Connection> ptr_t;

     /**
      * @param  host
      * @param  port
      * @param  user
      * @param  pass
      * @param  vhost
      */
    Connection(string host, int port, string user, string pass, string vhost);

    /**
     * Empty Destructor
     */
    virtual ~Connection();

    /**
     * @return Channel
     */
    Channel::ptr_t createChannel();

    /**
     * @param  host
     */
    void setHost(string host);

    /**
     * @return string
     */
    string getHost();

    /**
     * @param  port
     */
    void setPort(int port);

    /**
     * @return int
     */
    int getPort();

    /**
     */
    void connect();

    /**
     */
    void close();


  private:
    string                  host_;
    string                  user_;
    string                  password_;
    string                  vhost_;
    int                     port_;
    int                     sock_;
    unsigned int            channel_next_;
    amqp_connection_state_t conn_;
    vector<Queue::ptr_t>    channels_;


    /**
     * @return bool
     */
    bool isConnected();
};

///////////////////////////////////////////////////////////////////////////////////////////
}}

#endif // __IDEUP_AMQP_CONNECTION_HPP_
