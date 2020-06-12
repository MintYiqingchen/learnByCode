#include <iostream>
#include <numeric>
#include <vector>
#include <functional>
using namespace std;

template<typename _InIt, typename _Fun>
class filter_view {
public:
    class iterator { // 实现 InputIterator
    public:

        using iterator_category = input_iterator_tag;
        using value_type = typename _InIt::value_type;
        using difference_type = typename _InIt::difference_type;
        using pointer = typename _InIt::pointer;
        using reference = value_type&;

        iterator(_InIt _First, _InIt _Last, _Fun f):_First(_First), _Last(_Last), _fun(f) {
            ++(*this);
        }

        reference operator*() const noexcept { return *_Cur; }

        pointer operator->() const noexcept { return &(*_Cur); }

        iterator& operator++() {
            while (_First != _Last && !_fun(*_First)) {
                _First++;
            }
            _Cur = _First;
            if (_First != _Last) {
                _First++;
            }
            return *this;
        }

        iterator operator++(int) {
            iterator temp(*this);
            ++(*this);
            return temp;
        }

        bool operator==(const iterator& rhs) const noexcept
        {
            return _Cur == rhs._Cur;
        }
        bool operator!=(const iterator& rhs) const noexcept
        {
            return !operator==(rhs);
        }
    private:
        _InIt _First;
        _InIt _Last;
        _InIt _Cur;
        _Fun _fun;

    };

    filter_view(_InIt _First, _InIt _Last, _Fun f) :_First(_First), _Last(_Last), _fun(f) {}

    iterator begin() const noexcept { return iterator(_First, _Last, _fun);}

    iterator end() const noexcept {return iterator(_Last, _Last, _fun);}
private:
    _InIt _First;
    _InIt _Last;
    _Fun _fun;
};

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