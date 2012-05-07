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

#ifndef __IDEUP_AMQP_EXCEPTION_HPP__
#define __IDEUP_AMQP_EXCEPTION_HPP__

#include "common.hpp"
#include <librabbitmq/amqp.h>
#include <librabbitmq/amqp_framing.h>
#include <exception>


namespace ideup { namespace amqp {
/////////////////////////////////////////////////////////////////////////////////////

using namespace std;

/**
 * Wraps AMQP errors into exceptions.
 *
 * @author Moisés Maciá <mmacia@gmail.com>
 */
class Exception : public exception
{
  public:
    /**
     * Constructor
     *
     * @param message Exception descriptive message.
     * @param file    File in wich exection was raised (for debugging pourposes only).
     * @param line    Line number on wich exception was raised (for debugging pourposes only).
     */
    Exception(const string& message, const string& file = "<unknwon>", int line = 0);
    /**
     * Constructor
     *
     * @param message  Exception descriptive message.
     * @param response AQMP returned structure to retrieve server error from.
     * @param file     File in wich exection was raised (for debugging pourposes only).
     * @param line     Line number on wich exception was raised (for debugging pourposes only).
     */
    Exception(const string& message, amqp_rpc_reply_t& response, const string& file = "<unknwon>", int line = 0);

    virtual ~Exception() throw() {};

    /**
     * Gets the exception message.
     */
    virtual const char* what() const throw() { return message_.c_str(); };
    /**
     * Gets the file in wich exception was raised.
     */
    string file() const { return file_; };
    /**
     * Gets the line number on wich exception was raised.
     */
    int line() { return line_; };


  protected:
  private:
    string message_;
    string file_;
    int line_;
};

/////////////////////////////////////////////////////////////////////////////////////
}}

#endif //__IDEUP_AMQP_EXCEPTION_HPP__
