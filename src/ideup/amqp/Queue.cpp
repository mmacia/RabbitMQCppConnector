/***********************************************
 * This file is part of RabbitMQ C++ Connector *
 * See LICENSE file for details                *
 *                                             *
 * @author Moisés Maciá <mmacia@gmail.com>     *
 ***********************************************/

#include "Queue.hpp"

namespace ideup { namespace amqp {
////////////////////////////////////////////////////////////////////////////////////////////

Queue::Queue(amqp_connection_state_t conn, int channel_number, const string& name) :
  name_(name),
  channel_number_(channel_number),
  conn_(conn)
{
  openChannel();
}


Queue::~Queue()
{
  closeChannel();
}


void Queue::closeChannel()
{
  amqp_rpc_reply_t ret = amqp_channel_close(conn_, channel_number_, AMQP_REPLY_SUCCESS);

  if (ret.reply_type != AMQP_RESPONSE_NORMAL) {
    throw Exception("Error closing channel.", ret, __FILE__, __LINE__);
  }
}


void Queue::openChannel()
{
  amqp_channel_open(conn_, channel_number_);
}

////////////////////////////////////////////////////////////////////////////////////////////
}}
