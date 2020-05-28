
#include <chrono>
#include <future>
#include <iostream>
#include <thread>

using namespace std;

void work(promise<void> prom)
{
  // 假装我们计算了很久
  this_thread::sleep_for(2s);
  prom.set_value();
}

int main()
{
  promise<void> prom;
  auto fut = prom.get_future();
  thread th{work, move(prom)};
  // 干一些其他事
  cout << "I am waiting now\n";
  fut.wait();
  cout << "after synchronization\n";
  th.join();
}