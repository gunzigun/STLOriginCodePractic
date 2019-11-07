#include <iostream>
using namespace std;

template <class T>
struct plus
{
    T operator()(const T& x, const T& y) const
    {
        return x+y;
    }
};

template <class T>
class minus
{
public:
    T operator()(const T& x, const T& y) const
    {
        return x-y;  
    }
};

//以上两个类，都变成了仿函数，因为这两个类将operator()重载了

int main()
{
    plus<int> obj1;
    minus<int> obj2;

    // 以下使用仿函数，就像使用一般函数一样
    cout << obj1(3,5) << endl;          // 8 
    cout << obj2(3,5) << endl;          // -2

    // 以下直接产生仿函数的临时对象（第一对小括号），并调用之（第二对小括号）
    cout << plus<int>()(43,50) << endl;         // 93
    cout << minus<int>()(43,50) << endl;        // -7
}