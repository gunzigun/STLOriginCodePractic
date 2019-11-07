// __STL_LIMITED_DEFAULT_TEMPLATES
// 测试 template 参数可否根据前一个 template 参数而设定默认值

#include <iostream>
#include <cstddef>   // for size_t
using namespace std;

class alloc {};

template <class T, class Alloc = alloc, size_t BufSiz = 0>
class deque
{
public:
    deque() { cout << "deque" << endl; }
};

// 根据前一个参数值T，设定下一个参数Sequence 的默认值为deque<T>
template <class T, class Sequence = deque<T> >
class stack
{
public:
    stack() { cout << "stack" << endl; }
private:
    Sequence c;
};

int main()
{
    stack<int> x;    // deque
                    // stack
}