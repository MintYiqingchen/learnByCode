#include <memory>
#include <vector>
#include <iostream>
#include <numeric>
#include <utility>
using namespace std;
// test 1
namespace test {
    template <typename T, typename... Args>
    inline unique_ptr<T> make_unique(Args&&... args)
    {
        return unique_ptr<T>(new T(forward<Args>(args)...));
    }
}
// test 2
template <typename T>
constexpr auto sum(T x)
{
  return x;
}

template <typename T1, typename T2, typename... Targ>
constexpr auto sum(T1 x, T2 y, Targ... args)
{
  return sum(x + y, args...);
}

// test 3
template <typename... Args>
auto compose() {
    return [](auto&&... x) {return compose<Args...>();};
}

template <typename F>
auto compose(F f)
{
  return [f](auto&&... x) {
    return f(forward<decltype(x)>(x)...);
  };
}
template <typename F, typename... Args>
auto compose(F f, Args... other)
{
  return [f, other...](auto&&... x) {
    return f(compose(other...)(forward<decltype(x)>(x)...));
  };
}

template <template <typename, typename> class OutContainer = vector, typename F, class R>
auto fmap(F&& f, R&& inputs)
{
  typedef decay_t<decltype(f(*inputs.begin()))> result_type;
  OutContainer<result_type, allocator<result_type>> result;
  for (auto&& item : inputs) {
    result.push_back(f(item));
  }
  return result;
}

// test 4
constexpr int count_bits(unsigned char value)
{
  if (value == 0) {
    return 0;
  } else {
    return (value & 1) + count_bits(value >> 1);
  }
}

template <size_t... V>
struct bit_count_t { 
  unsigned char count[sizeof...(V)] = {static_cast<unsigned char>(count_bits(V))...};
};


template <size_t... V>
bit_count_t<V...> get_bit_count(index_sequence<V...>)
{
  return bit_count_t<V...>();
}

auto bit_count = get_bit_count(
  make_index_sequence<256>());
int main(int argc, char** argv) {
    auto a = test::make_unique<vector<int>>(100, 1);
    auto b = sum(1,1.2, 1.3,10, -2);
    cout << b << endl;
    // test 3
    auto square_list = [](auto&& container) {
        return fmap([](int x) { return x * x; }, container);};
    auto sum_list = [](auto&& container) {
        return accumulate(container.begin(),container.end(), 0);};
    auto square_sum = compose(sum_list, square_list);
    auto c = vector<int>{1,2,3,4};
    cout << square_sum(c) << endl;
    // test 4
    auto bitStruct = get_bit_count(make_index_sequence<256>());
    cout << sizeof(bitStruct.count) << endl;
}