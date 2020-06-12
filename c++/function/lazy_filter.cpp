
#include <iostream>
#include <numeric>
#include <vector>
#include <functional>
using namespace std;

// filter_view 的定义

template<typename InputIt, typename Pred>
auto filter_view(InputIt a, InputIt b, Pred pred) {
    struct {
        InputIt _begin, _end;
        function<bool(decltype(*_begin))> _pred;
        struct iterator {
            InputIt _it, _end;
            function<bool(decltype(*_it))> _pred;
            iterator(InputIt it, InputIt e, decltype(_pred) p):_it(it), _end(e), _pred(p){}
            bool operator != (const iterator& other) {return _it != other._it;}
            bool operator == (const iterator& other) {return _it == other._it;}

            auto operator*() {return *_it;}
            auto operator->() {return &(*_it);}

            iterator& operator ++ () {
                do {
                    if(_it == _end) break;
                    ++ _it;
                    if(_it == _end || _pred(*_it)) break;
                } while(true);
                return *this;
            }
        };
        
        iterator begin() {
            while(_begin != _end && !_pred(*_begin))
                ++ _begin;
            return iterator(_begin, _end, _pred);
        }
        iterator end() {
            return iterator(_end, _end, _pred);
        }
    } object;
    object._begin = a;
    object._end = b;
    object._pred = [pred](decltype(*a) x){return pred(x);};
    return object;
}
// 一个惰性的过滤器应当让下面的代码通过编译，并且不会占用跟数据集大小相关的额外空间
int main()
{
  vector v{1, 2, 3, 4, 5};
  auto&& fv = filter_view(v.begin(), v.end(), [](int x) {
      return x % 2 == 0;
    });
  // cout << *fv.begin() << endl;
  // auto a = fv.begin();
  // ++ a;
  // cout << *a << endl;
  cout << accumulate(fv.begin(), fv.end(), 0) << endl;
}