#include <utility> // declval
#include <vector>
#include <list>
#include <iostream>
#include <type_traits> // void_t
using namespace std;
// test 4
template <typename C, typename T>
auto append(C& container, T* ptr, size_t size)
  -> decltype(declval<C&>().reserve(1U), void()) 
  // 注意类型推断和auto的配合使用可以达到返回值的自动推导
  // decltype(a, b, c) 的意思是先看a对不对，再看b对不对，再看c对不对, 不对就是substitution fail, 导致该模板函数实例化失败
  // declval<C&>()的意思是假装存在一个C的对象，调用reserve(1U)的返回值
{
  std::cout << "success" << std::endl;
  container.reserve(container.size() + size);
  for (size_t i = 0; i < size; ++i) {
    container.push_back(ptr[i]);
  }
}
// test 5
template <typename T, typename = void_t<>>
struct has_reserve : false_type {}; // false_type是type_traits里面常见的返回值

template <typename T>
struct has_reserve<T, void_t<decltype(declval<T&>().reserve(1U))>> : true_type {}; // 上面模板的偏特化

template <typename C, typename T>
void _append(C& container, T* ptr, size_t size, false_type) {
    std::cout << "append" << endl;
    for(size_t i = 0; i < size; ++ i) {
        container.push_back(ptr[i]);
    }
}
template <typename C, typename T>
void _append(C& container, T* ptr, size_t size, true_type) {
    cout << "reserve append" << endl;
    container.reserve(size);
    for(size_t i = 0; i < size; ++ i) {
        container.push_back(ptr[i]);
    }
}
template <typename C, typename T>
void append2(C& container, T* ptr, size_t size) {
    _append(container, ptr, size, has_reserve<C> {});
}
// test 6
struct MyType {
    void member_function() {
        cout << "member_function" << endl;
    }
};
int main(int argc, char** argv) {
    // test 4
    std::vector<int> a;
    std::list<int> b;
    int array[] = {1,2,3,4};
    append(a, array, 4); // success
    // append(b, array, 4); // compile error
    // test 5
    append2(a, array, 4); // reserve append
    append2(b, array, 4); // append
    _append(a, array, 4, has_reserve<decltype(a)>{}); // reserve append
    // test 6
    auto f = &MyType::member_function;
    cout << typeid(f).name() << endl;
}