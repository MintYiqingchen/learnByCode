#include <array>
#include <vector>
#include <iostream>
#include <list>
using namespace std;
// test 1
int square(int n) {return n * n;}
constexpr int square1(int n) {return n * n;}
// test 2
struct magic {
    static const int number = 42;
};
struct magic1 {
    static const int number;
    static inline const int number1 = 42; // -std=c++17 inline variable
    static constexpr int number2 = 42;

};
const int magic1::number = 42;
// test 4
template <typename T>
struct has_reserve {
  struct good { char dummy; };
  struct bad { char dummy[2]; };
  
  template <class U, void (U::*)(size_t)> // second parameter is a function signature, U::* means member function pointer
  struct SFINAE {};
  
  template <class U>
  static good reserve(SFINAE<U, &U::reserve>*);
  
  template <class U>
  static bad reserve(...);
  
  static const bool value = sizeof(reserve<T>(nullptr)) == sizeof(good);
};
template <typename C, typename T>
void append(C& container, T* ptr, size_t size)
{
  if constexpr (has_reserve<C>::value) { // c++17 if constexpr 表达式
    container.reserve(container.size() + size);
  }
  for (size_t i = 0; i < size;++i) {
    container.push_back(ptr[i]);
  }
}

int main(int argc, char** argv) {
    // test 1
    int a[square(3)] = {1,2,3,4};
    // array<int, square(3)> b; // compile error
    array<int, square1(3)> b;
    // test 2
    cout << magic::number << endl;
    vector<int> c;
    // c.push_back(magic::number); // link error: constworld.cpp:(.text+0xf6): undefined reference to `magic::number'
    c.push_back(magic1::number);
    c.push_back(magic1::number1);
    c.push_back(magic1::number2);
    // test 3
    constexpr string_view sv{"hi"};  
    constexpr pair pr{sv[0], sv[1]}; // 自动模板参数推导 -std=c++17
    constexpr array d{pr.first, pr.second};  
    constexpr int n1 = d[0];  
    constexpr int n2 = d[1];  
    cout << n1 << ' ' << n2 << '\n';
    // test 4
    list<int> e;
    append(e, a, 4);
    return 0;
}