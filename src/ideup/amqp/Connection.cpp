#include "Connection.hpp"

namespace ideup { namespace amqp {
//////////////////////////////////////////////////////////////////////////////////////

Connection::Connection(string host, int port, string user, string pass, string vhost)
{
}

Connection::~Connection()
{
}


bool Connection::isConnected()
{
  return is_connected_;
}


Channel::ptr_t Connection::createChannel()
{
  return make_shared<Channel>();
}


int Connection::getPort()
{
  return port_;
}


string Connection::getHost()
{
  return host_;
}


void Connection::close()
{
  // TODO implement me!
}


void Connection::connect()
{
  // TODO implement me!
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
