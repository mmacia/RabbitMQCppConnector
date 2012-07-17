#include <iostream>
#include "../src/ideup/amqp/ConnectionFactory.hpp"
#include "../src/ideup/amqp/Connection.hpp"
#include "../src/ideup/amqp/Channel.hpp"
#include "../src/ideup/amqp/Queue.hpp"
#include "../src/ideup/amqp/Message.hpp"
#include "../src/ideup/amqp/Exception.hpp"

using namespace ideup::amqp;


int main(int argc, char* argv[])
{
  try {
    shared_ptr<Connection> conn = ConnectionFactory::newConnection();
    shared_ptr<Channel> channel = conn->createChannel();

    channel->declareExchange("my-exchange", "direct");
    channel->declareQueue("my-first-queue");
    channel->bindQueue("my-first-queue", "my-exchange");

    Message::ptr_t msg = make_shared<Message>("This is my first message");
    channel->basicPublish(msg, "my-exchange");

    conn->close();
  }
  catch (Exception& e) {
    cerr << "AMQP Exception: " << e.what() << endl;
  }
  catch (exception& e) {
    cerr << "Standard Exception: " << e.what() << endl;
  }
}
