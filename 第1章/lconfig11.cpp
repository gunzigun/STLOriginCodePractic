// __STL_NON_TYPE_TMPL_PARAM_BUG
// 测试 class template 可否拥有non-type template 参数

#include <iostream>
#include <cstddef>      // for size_t
using namespace std;

class alloc {};

inline size_t __deque_buf_size(size_t n, size_t sz)
{
    return n != 0 ? n : (sz < 521 ? size_t(512/sz) : size_t(1));
}

template <class T, class Ref, class Ptr, size_t BufSiz>   // 此处的BufSiz就是个non-type
struct __deque_iterator
{
    typedef __deque_iterator<T, T&, T*, BufSiz> iterator;
    typedef __deque_iterator<T, const T&, const T*, BufSiz> const_iterator;
    static size_t buffer_size() { return __deque_buf_size(BufSiz, sizeof(T)); }
};

template <class T, class Alloc = alloc, size_t BufSiz = 0>
class deque
{
public:
    typedef __deque_iterator<T, T&, T*, BufSiz> iterator;
};

int main()
{
    cout << deque<int>::iterator::buffer_size() << endl;                           // 128
    cout << deque<int, alloc, 64>::iterator::buffer_size() << endl;                // 64
}

