#include "AMQP.hpp"
#include "Observer.hpp"

using namespace std;

class MyObserver : public ideup::amqp::Observer
{
  public:
  protected:
  private:
};

int main(int argc, char* argv[])
{
  ideup::amqp::AMQP* amqp = new ideup::amqp::AMQP();
  return 0;
}
