// 测试 __STL_NULL_TMPL_ARGS 的使用
// 实现所谓的 bound  friend templates，也就是说class template 的某个具体实现与其 friend function template 的某个具体实现一对一关系

#include <iostream>
#include <cstddef>          // for size_t
using namespace std;

class alloc {};

template <class T, class Alloc = alloc, size_t BufSiz = 0>
class deque
{
public:
    deque() { cout << "deque" << endl; }
};

template <class T, class Sequence>
class stack;

template <class T, class Sequence>
bool operator== (const stack<T, Sequence>& x, const stack<T, Sequence>& y)
{
    return cout << "operator==" << "\t";
}

template <class T, class Sequence>
bool operator< (const stack<T, Sequence>& x, const stack<T, Sequence>& y)
{
    return cout << "operator<" << "\t";
}

template <class T, class Sequence = deque<T> >
class stack
{
    // 写成这样是可以的
    friend bool operator== <T> (const stack<T>&, const stack<T>&);
    friend bool operator< <T> (const stack<T>&, const stack<T>&);
    // 写成这样是可以的
    friend bool operator== <T> (const stack&, const stack&);
    friend bool operator< <T> (const stack&, const stack&);
    // 写成这样是可以的
    friend bool operator== <> (const stack&, const stack&);
    friend bool operator< <> (const stack&, const stack&);
    // 写成这样就不可以
    //friend bool operator== (const stack&, const stack&);
    //friend bool operator< (const stack&, const stack&);
public:
    stack() { cout << "stack" << endl; }
private:
    Sequence c;
};

int main()
{
    stack<int> x;
    stack<int> y;

    cout << (x == y) << endl;      //    operator== 1    
    cout << (x < y) << endl;       //    operator< 1

    stack<char> y1;
    //cout << (x == y) << endl;       
    //cout << (x < y) << endl;         // 编译错误     
}