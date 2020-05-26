#include <iostream>
#include <vector>
#include <type_traits> // enable_if_t
#include <list>
// ---------- test 1
struct Dummy {
    typedef int foo;
};
template<typename T>
void test(typename T::foo a) {
    std::cout << "1"<<std::endl;
}

template<typename T>
void test(T a) {
    std::cout << "2" << std::endl;
}
// --------- test 2
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
// test 3
template <typename C, typename T>
std::enable_if_t<has_reserve<C>::value, void> append(C& container, T* ptr, size_t size) // enable_if_t<true, void> 如果第一个参数为true则开启该重载
{
  std::cout << "reserve append" << std::endl;
  container.reserve(container.size() + size);
  for (size_t i = 0; i < size; ++i) {
    container.push_back(ptr[i]);
  }
}

template <typename C, typename T>
std::enable_if_t<!has_reserve<C>::value, void> append(C& container, T* ptr, size_t size)
{
  std::cout << "append" << std::endl;
  for (size_t i = 0; i < size; ++i) {
    container.push_back(ptr[i]);
  }
}


int main(int argv, char** argc) {
    // test 1
    test<Dummy>(10);
    test(10);
    // test 2
    std::cout << "has_reserve: " << has_reserve<std::vector<int>>::value << std::endl; // 1
    // test 3
    std::vector<int> a;
    std::list<int> b;
    int array[] = {1,2,3,4};
    append(a, array, 4); // reserve append
    append(b, array, 4); // append
}