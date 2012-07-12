/***********************************************
 * This file is part of RabbitMQ C++ Connector *
 * See LICENSE file for details                *
 *                                             *
 * @author Moisés Maciá <mmacia@gmail.com>     *
 ***********************************************/

#include "Message.hpp"

namespace ideup { namespace amqp {
////////////////////////////////////////////////////////////////////////////////////////////


Message::Message(const string& message) :
  body_(message),
  contentType_("plain/text"),
  deliveryMode_(DELIVER_PERSISTENT),
  contentEncoding_(""),
  messageId_(""),
  userId_(""),
  appId_(""),
  clusterId_(""),
  correlationId_(""),
  priority_(0),
  timestamp_(0),
  expiration_(""),
  type_(""),
  replyTo_("")
{
}

Message::~Message()
{
  // TODO Implement me!
}


string Message::getBody() const
{
  return body_;
}


void Message::setDeliveryMode(DeliveryMode mode)
{
  deliveryMode_ = static_cast<uint8_t>(mode);
}


DeliveryMode Message::getDeliveryMode() const
{
  return static_cast<DeliveryMode>(deliveryMode_);
}


void Message::setAppId(const string& id)
{
  appId_ = id;
}


string Message::getAppId() const
{
  return appId_;
}


void Message::setClusterId(const string& id)
{
  clusterId_ = id;
}


string Message::getClusterId() const
{
  return clusterId_;
}


void Message::setContentEncoding(const string& encoding)
{
  contentEncoding_ = encoding;
}


string Message::getContentEncoding() const
{
  return contentEncoding_;
}


void Message::setContentType(const string& mime)
{
  contentType_ = mime;
}


string Message::getContentType() const
{
  return contentType_;
}


void Message::setCorrelationId(const string& id)
{
  correlationId_ = id;
}


string Message::getCorrelationId() const
{
  return correlationId_;
}


void Message::setExpiration(const string& expiration)
{
  expiration_ = expiration;
}


string Message::getExpiration() const
{
  return expiration_;
}


void Message::setMessageId(const string& id)
{
  messageId_ = id;
}


string Message::getMessageId() const
{
  return messageId_;
}


void Message::setReplyTo(const string& replyTo)
{
  replyTo_ = replyTo;
}


string Message::getReplyTo() const
{
  return replyTo_;
}


void Message::setType(const string& type)
{
  type_ = type;
}


string Message::getType() const
{
  return type_;
}


void Message::setUserId(const string& id)
{
  userId_ = id;
}


string Message::getUserId() const
{
  return userId_;
}


void Message::setTimestamp(uint64_t timestamp)
{
  timestamp_ = timestamp;
}


uint64_t Message::getTimestamp() const
{
  return timestamp_;
}


void Message::setPriority(uint8_t priority)
{
  priority_ = priority;
}


uint8_t Message::getPriority() const
{
  return priority_;
}


const amqp_basic_properties_t* Message::getProperties()
{
  props_._flags = 0;

  if (!contentType_.empty()) {
    props_.content_type = amqp_cstring_bytes(contentType_.c_str());
    props_._flags += AMQP_BASIC_CONTENT_TYPE_FLAG;
  }

  if (deliveryMode_ != 0) {
    props_.delivery_mode = static_cast<uint8_t>(deliveryMode_);
    props_._flags += AMQP_BASIC_DELIVERY_MODE_FLAG;
  }

  if (!contentEncoding_.empty()) {
    props_.content_encoding = amqp_cstring_bytes(contentEncoding_.c_str());
    props_._flags += AMQP_BASIC_CONTENT_ENCODING_FLAG;
  }

  if (!messageId_.empty()) {
    props_.message_id = amqp_cstring_bytes(messageId_.c_str());
    props_._flags += AMQP_BASIC_MESSAGE_ID_FLAG;
  }

  if (!userId_.empty()) {
    props_.user_id = amqp_cstring_bytes(userId_.c_str());
    props_._flags += AMQP_BASIC_USER_ID_FLAG;
  }

  if (!appId_.empty()) {
    props_.app_id = amqp_cstring_bytes(appId_.c_str());
    props_._flags += AMQP_BASIC_APP_ID_FLAG;
  }

  if (!clusterId_.empty()) {
    props_.cluster_id = amqp_cstring_bytes(clusterId_.c_str());
    props_._flags += AMQP_BASIC_CLUSTER_ID_FLAG;
  }

  if (!correlationId_.empty()) {
    props_.correlation_id = amqp_cstring_bytes(correlationId_.c_str());
    props_._flags += AMQP_BASIC_CORRELATION_ID_FLAG;
  }

  if (priority_ > 0) {
    props_.priority = priority_;
    props_._flags += AMQP_BASIC_PRIORITY_FLAG;
  }

  if (timestamp_ > 0) {
    props_.timestamp = timestamp_;
    props_._flags += AMQP_BASIC_TIMESTAMP_FLAG;
  }

  if (!expiration_.empty()) {
    props_.expiration = amqp_cstring_bytes(expiration_.c_str());
    props_._flags += AMQP_BASIC_EXPIRATION_FLAG;
  }

  if (!type_.empty()) {
    props_.type = amqp_cstring_bytes(type_.c_str());
    props_._flags += AMQP_BASIC_TYPE_FLAG;
  }

  if (!replyTo_.empty()) {
    props_.reply_to = amqp_cstring_bytes(replyTo_.c_str());
    props_._flags += AMQP_BASIC_REPLY_TO_FLAG;
  }

  return &props_;
}


////////////////////////////////////////////////////////////////////////////////////////////
}}
