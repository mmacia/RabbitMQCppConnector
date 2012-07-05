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

#ifndef __IDEUP_AMQP_CONNECTIONFACTORY_HPP__
#define __IDEUP_AMQP_CONNECTIONFACTORY_HPP__

#include <string>
#include <memory>
#include "Connection.hpp"

namespace ideup { namespace amqp {
///////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

/**
 * class ConnectionFactory
 */
class ConnectionFactory
{
  public:
    /**
     * @return Connection shared pointer
     *
     * @param  host
     * @param  port
     * @param  user
     * @param  pass
     * @param  vhost
     */
    static shared_ptr<Connection> newConnection(
        const string& host  = "localhost",
        int port            = 5672,
        const string& user  = "guest",
        const string& pass  = "guest",
        const string& vhost = "/")
    {
      return make_shared<Connection>(host, port, user, pass, vhost);
    };

  protected:
  private:
    /**
     * Empty Constructor
     */
    ConnectionFactory();

    /**
     * Empty Destructor
     */
    virtual ~ConnectionFactory();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
}}

#endif // __IDEUP_AMQP_CONNECTIONFACTORY_HPP__
