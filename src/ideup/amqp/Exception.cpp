/***********************************************
 * This file is part of RabbitMQ C++ Connector *
 * See LICENSE file for details                *
 *                                             *
 * @author Moisés Maciá <mmacia@gmail.com>     *
 ***********************************************/

#include "Exception.hpp"

namespace ideup { namespace amqp {
////////////////////////////////////////////////////////////////////////////////////////////

Exception::Exception(const string& message, const string& file, int line) :
  message_(message),
  file_(file),
  line_(line)
{
}


Exception::Exception(const string& message, amqp_rpc_reply_t& response, const string& file, int line) :
  message_(message),
  file_(file),
  line_(line)
{
  switch (response.reply_type) {
    case AMQP_RESPONSE_NORMAL:
      return;

    case AMQP_RESPONSE_NONE:
      message_.append(" Missing RPC reply type!");
      break;

    case AMQP_RESPONSE_LIBRARY_EXCEPTION:
      message_.append(amqp_error_string(response.library_error));
      break;

    case AMQP_RESPONSE_SERVER_EXCEPTION:
      switch (response.reply.id) {
          case AMQP_CONNECTION_CLOSE_METHOD: {
            amqp_connection_close_t *m = (amqp_connection_close_t *) response.reply.decoded;

            stringstream ss;
            ss << " Server connection error(" << (int)m->reply_code << "): ";
            message_.append(ss.str().append((char*)m->reply_text.bytes, (int)m->reply_text.len));
            break;
          }
          case AMQP_CHANNEL_CLOSE_METHOD: {
            amqp_channel_close_t *m = (amqp_channel_close_t *) response.reply.decoded;

            stringstream ss;
            ss << " Server channel error(" << (int)m->reply_code << "): ";
            message_.append(ss.str().append((char*)m->reply_text.bytes, (int)m->reply_text.len));
            break;
          }
          default:
            stringstream ss;
            ss << " Unknown server error, method id 0x" << (uint32_t)response.reply.id;
            break;
        }
        break;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
}}
