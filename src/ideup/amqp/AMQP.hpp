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

#ifndef __IDEUP_AMQP_AMQP_HPP__
#define __IDEUP_AMQP_AMQP_HPP__

#include "common.hpp"
#include "Queue.hpp"
#include "Exception.hpp"
#include <librabbitmq/amqp.h>
#include <librabbitmq/amqp_framing.h>


namespace ideup { namespace amqp {
/////////////////////////////////////////////////////////////////////////////////////

using namespace std;

/**
 *
 * @author Moisés Maciá <mmacia@gmail.com>
 */
class AMQP
{
  public:
    /**
     * Default constructor
     */
    AMQP();
    /**
     * Parametrized constructor.
     * Use this constructor to pass connection parameters AND connect to the server.
     *
     * @param host
     * @param port
     * @param user
     * @param pass
     * @param vhost
     */
    AMQP(const string& host, int port, const string& user, const string& pass, const string& vhost);
    /**
     * Default destructor
     */
    ~AMQP();

    /**
     * Sets host
     *
     * @param host
     */
    void host(const string& host) { host_ = host; };
    /**
     * Gets host
     */
    string host() const { return host_; };

    /**
     * Sets connection port
     *
     * @param port
     */
    void port(int port) { port_ = port; };
    /**
     * Gets connection port
     */
    int port() const { return port_; };

    /**
     * Sets login user
     *
     * @param user
     */
    void user(const string& user) { user_ = user; };
    /**
     * Gets login user
     */
    string user() const { return user_; };

    /**
     * Sets connection password
     *
     * @param password
     */
    void password(const string& password) { password_ = password; };

    /**
     * Sets virtual host
     *
     * @param vhost
     */
    void vhost(const string& vhost) { vhost_ = vhost; };
    /**
     * Gets virtual host
     */
    string vhost() { return vhost_; };

    /**
     * Check if connection is stablished.
     */
    bool isConnected() { return is_connected_; };
    /**
     * Connect to RabbitMQ server
     */
    void connect();

    /**
     * Create a queue in server
     *
     * @param name Name of queue
     */
    Queue* createQueue(const string& name);
    //void createExchange();


  protected:
  private:
    string                  host_;
    string                  user_;
    string                  password_;
    string                  vhost_;
    int                     port_;
    bool                    is_connected_;
    amqp_connection_state_t conn_;
    int                     sock_;
    vector<Queue*>          channels_;
};

/////////////////////////////////////////////////////////////////////////////////////
}}

#endif //__IDEUP_AMQP_AMQP_HPP__
