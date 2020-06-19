
#include <chrono>
#include <thread>
#include "easylogging++.h"
INITIALIZE_EASYLOGGINGPP

void foo()
{
  TIMED_FUNC(timer);
  LOG(WARNING) << "A warning message";
}

void bar()
{
  using namespace std::literals;
  TIMED_SCOPE(timer1, "void bar()");
  foo();
  foo();
  TIMED_BLOCK(timer2, "a block") {
    foo();
    std::this_thread::sleep_for(100us);
  }
}

int main()
{
  el::Configurations conf{"elpp.config"};
  el::Loggers::reconfigureAllLoggers(conf);
  bar();
} // g++ -std=c++17 -DELPP_FEATURE_PERFORMANCE_TRACKING -DELPP_PERFORMANCE_MICROSECONDS elppExample1.cpp easylogging++.cc 