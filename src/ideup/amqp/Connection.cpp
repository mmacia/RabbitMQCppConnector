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
  return /* something */;
}


Channel::ptr_t Connection::createChannel()
{
  return make_shared<Channel>();
}


int Connection::getPort()
{
  return /* something */;
}


string Connection::getHost()
{
  return /* something */;
}


void Connection::close()
{
  return /* something */;
}


void Connection::connect()
{
  return /* something */;
}


void Connection::setHost(string host)
{
  return /* something */;
}


void Connection::setPort(int port)
{
  return /* something */;
}


//////////////////////////////////////////////////////////////////////////////////////
}}
