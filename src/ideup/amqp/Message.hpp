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

#ifndef __IDEUP_AMQP_MESSAGE_HPP__
#define __IDEUP_AMQP_MESSAGE_HPP__

#include "common.hpp"
#include "Exception.hpp"
#include <librabbitmq/amqp.h>
#include <librabbitmq/amqp_framing.h>


namespace ideup { namespace amqp {
/////////////////////////////////////////////////////////////////////////////////////

using namespace std;

enum DeliveryMode {
  DELIVER_NON_PERSISTENT = 1,
  DELIVER_PERSISTENT = 2
};


/**
 *
 * @author Moisés Maciá <mmacia@gmail.com>
 */
class Message
{
  public:
    typedef shared_ptr<Message> ptr_t;

    Message(const string& message);
    virtual ~Message();

    string getBody() const;

    void setContentType(const string& mime);
    string getContentType() const;

    void setDeliveryMode(DeliveryMode mode);
    DeliveryMode getDeliveryMode() const;

    void setContentEncoding(const string& encoding);
    string getContentEncoding() const;

    void setMessageId(const string& id);
    string getMessageId() const;

    void setUserId(const string& id);
    string getUserId() const;

    void setAppId(const string& id);
    string getAppId() const;

    void setClusterId(const string& id);
    string getClusterId() const;

    void setCorrelationId(const string& id);
    string getCorrelationId() const;

    void setPriority(uint8_t priority);
    uint8_t getPriority() const;

    void setTimestamp(uint64_t timestamp);
    uint64_t getTimestamp() const;

    void setExpiration(const string& expiration);
    string getExpiration() const;

    void setType(const string& type);
    string getType() const;

    void setReplyTo(const string& replyTo);
    string getReplyTo() const;

    const amqp_basic_properties_t* getProperties();

  protected:
  private:
    string body_;
    string contentType_;
    uint8_t deliveryMode_;
    string contentEncoding_;
    string messageId_;
    string userId_;
    string appId_;
    string clusterId_;
    string correlationId_;
    uint8_t priority_;
    uint64_t timestamp_;
    string expiration_;
    string type_;
    string replyTo_;

    amqp_basic_properties_t props_;
};

/////////////////////////////////////////////////////////////////////////////////////
}}

#endif //__IDEUP_AMQP_MESSAGE_HPP__
