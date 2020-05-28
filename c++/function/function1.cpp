#include <iostream>
#include <chrono>
#include <sstream>
#include <string>
#include <thread> // g++ -std=c++17 -pthread function1.cpp
#include <functional>
using namespace std;
// test 1
int add_2(int a) {return 2 + a;}
template <typename T>
auto test1(T fn) { return fn(2);}

template <typename T>
auto test2(T& fn) { return fn(2);}

template <typename T>
auto test3(T* fn) {return fn(2);}

// test 2
int get_count()
{
  static int count = 0;
  return ++count;
}

class task {
public:
  task(int data) : data_(data) {}
  auto lazy_launch()
  {
    return
    //   [this, count = get_count()]() mutable { // this 按引用捕获
      [*this, count = get_count()]() mutable { // *this 按值捕获
        ostringstream oss;
        oss << "Done work " << data_
            << " (No. " << count
            << ") in thread "
            << this_thread::get_id()
            << '\n';
        msg_ = oss.str();
        calculate();
      };
  }
  void calculate()
  {
    this_thread::sleep_for(100ms);
    cout << msg_;
  }

private:
  int data_;
  string msg_;
};

// test 4
struct A {
    void set(int n) {
        data_ = n;
    }
private:
    int data_;
};
int main(int argc, char** argv) {
    // test 1
    cout << test1(add_2) << " " << test2(add_2) << " " << test3(add_2) << endl;
    // test 2
    auto t = task{37};
    thread t1{t.lazy_launch()};
    thread t2{t.lazy_launch()};
    t1.join();
    t2.join();
    // test 3
    using namespace std::placeholders;
    cout << bind(plus<>(), _1, _3)(1, 2, 3) << endl;
    // test 4
    A a;
    auto func = &A::set;
    (a.*func)(2);
}