#include "Connection.hpp"

namespace ideup { namespace amqp {
//////////////////////////////////////////////////////////////////////////////////////

Connection::Connection(string host, int port, string user, string pass, string vhost) :
  host_(host),
  user_(user),
  password_(pass),
  vhost_(vhost),
  port_(port),
  sock_(0),
  channel_next_(0)
{
}

Connection::~Connection()
{
  channels_.clear();
  channel_next_ = 0;
  close();
}


bool Connection::isConnected()
{
  return sock_ > 0;
}


shared_ptr<Channel> Connection::createChannel()
{
  if (!isConnected()) {
    connect();
  }

  ++channel_next_;
  return make_shared<Channel>(this);
}


int Connection::getPort()
{
  return port_;
}


string Connection::getHost()
{
  return host_;
}


amqp_connection_state_t Connection::getConnection() const
{
  return conn_;
}


int Connection::getChannel() const
{
  return channel_next_;
}


void Connection::close()
{
  if (!isConnected()) {
    return;
  }

  amqp_connection_close(conn_, AMQP_REPLY_SUCCESS);
  amqp_destroy_connection(conn_);
  conn_ = 0;

  ::close(sock_);
  sock_ = 0;
}


void Connection::connect()
{
  if (isConnected()) {
    return;
  }

  conn_ = amqp_new_connection();
  sock_ = amqp_open_socket(host_.c_str(), port_);

  int channel_max = 0;
  int frame_max = 131072;
  int heart_beat = 131072;

  if (sock_ < 0) {
    stringstream ss;
    char* errstr = amqp_error_string(-sock_);

    ss << "Cannot create socket: " << errstr;
    free(errstr);

    throw Exception(ss.str(), __FILE__, __LINE__);
  }

  amqp_set_sockfd(conn_, sock_);

  // socket connected, proceed to login
  amqp_rpc_reply_t response = amqp_login(conn_,
                                         vhost_.c_str(),
                                         channel_max,
                                         frame_max,
                                         heart_beat,
                                         AMQP_SASL_METHOD_PLAIN,
                                         user_.c_str(),
                                         password_.c_str());

  if (response.reply_type == AMQP_RESPONSE_NORMAL) {
    return;
  }

  throw Exception("Error while login.", response, __FILE__, __LINE__);
}


void Connection::setHost(string host)
{
  host_ = host;
}


void Connection::setPort(int port)
{
  port_ = port;
}


//////////////////////////////////////////////////////////////////////////////////////
}}
