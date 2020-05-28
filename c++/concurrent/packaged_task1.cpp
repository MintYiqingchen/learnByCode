#include <chrono>
#include <future>
#include <iostream>
#include <thread>

using namespace std;


int work()
{
  // 假装我们计算了很久
  this_thread::sleep_for(2s);
  return 42;
}

int main()
{
  packaged_task<int()> task{work};
  auto fut = task.get_future();
  thread th{move(task)};
  // 干一些其他事
  this_thread::sleep_for(1s);
  cout << "I am waiting now\n";
  cout << "Answer: " << fut.get()
       << '\n';
  th.join();
}