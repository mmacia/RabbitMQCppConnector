#include <iostream>
#include "../src/ideup/amqp/ConnectionFactory.hpp"
#include "../src/ideup/amqp/Connection.hpp"
#include "../src/ideup/amqp/Channel.hpp"
#include "../src/ideup/amqp/Queue.hpp"
#include "../src/ideup/amqp/Message.hpp"

using namespace ideup::amqp;


class MyConsumer : public Observer
{
  public:
    void update(Message& message) {
      cout << message.getBody() << endl;
    }
};


int main(int argc, char* argv[])
{
  Connection::ptr_t conn = ConnectionFactory::newConnection();
  Channel::ptr_t channel = conn->createChannel();

  Queue::ptr_t queue = channel->declareQueue("my-first-queue");

  queue->attach(new MyConsumer());
  queue->basicConsume();

  channel->close();
  conn->close();
}
