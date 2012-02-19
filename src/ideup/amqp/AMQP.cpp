/***********************************************
 * This file is part of RabbitMQ C++ Connector *
 * See LICENSE file for details                *
 *                                             *
 * @author Moisés Maciá <mmacia@gmail.com>     *
 ***********************************************/

#include "AMQP.hpp"

namespace ideup { namespace amqp {
////////////////////////////////////////////////////////////////////////////////////////////

AMQP::AMQP()
{
  is_connected_ = false;
  host("localhost");
  port(5672);
  user("guest");
  password("guest");
  vhost("/");
}


AMQP::AMQP(const string& h, int p, const string& u, const string& pass, const string& vh)
{
  is_connected_ = false;
  host(h);
  port(p);
  user(u);
  password(pass);
  vhost(vh);

  connect();
}


AMQP::~AMQP()
{
  // free queues
  if (channels_.size() > 0) {
    vector<Queue*>::iterator it;

    for (it = channels_.begin(); it != channels_.end(); it++) {
      delete *it;
    }

    channels_.erase(channels_.begin(), channels_.end());
  }

  amqp_destroy_connection(conn_);
  close(sock_);
}


void AMQP::connect()
{
  if (is_connected_) {
    return;
  }

  cout << "Connecting to " << host_ << ": " << port_ << endl;
  conn_ = amqp_new_connection();
  sock_ = amqp_open_socket(host_.c_str(), port_);

  if (sock_ < 0) {
    throw Exception("Cannot create socket!", __FILE__, __LINE__);
  }

  amqp_set_sockfd(conn_, sock_);
  is_connected_ = true;

  // socket connected, proceed to login
  amqp_rpc_reply_t response = amqp_login(conn_,
                                         vhost_.c_str(),
                                         0,
                                         131072,
                                         0,
                                         AMQP_SASL_METHOD_PLAIN,
                                         user_.c_str(),
                                         password_.c_str());

  if (response.reply_type == AMQP_RESPONSE_NORMAL) {
    return;
  }

  throw Exception("Error while login.", response, __FILE__, __LINE__);
}


Queue* AMQP::createQueue(const string& name)
{
  int channel_number = channels_.size() + 1;
  Queue *q = new Queue(conn_, channel_number, name);

  channels_.push_back(q);
  return q;
}
////////////////////////////////////////////////////////////////////////////////////////////
}}
