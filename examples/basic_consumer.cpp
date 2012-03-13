#include "AMQP.hpp"
#include "Observer.hpp"

using namespace std;

class MyObserver : public ideup::amqp::Observer
{
  public:
    MyObserver() {};
    ~MyObserver() {};

    void update(const string& message) {
      ideup::amqp::Queue* q = dynamic_cast<ideup::amqp::Queue*>(subject());
      cout << "Observer notified! " << q->name() << " -- ";
      cout << message << endl;
    }

  protected:
  private:
};

int main(int argc, char* argv[])
{
  using namespace ideup::amqp;

  AMQP amqp;

  try {
    amqp.connect();
    Queue* queue = amqp.createQueue("my_sample_queue");

    bitset<numQueueArgs> args;
    args.set(QUEUE_DURABLE);

    queue->declare(args);

    shared_ptr<MyObserver> my_observer(new MyObserver());

    queue->attach(my_observer.get());
    queue->consume();
  }
  catch(Exception& e) {
    cerr << e.message() << " in " << e.file() << ":" << e.line() << endl;
  }

  return 0;
}
