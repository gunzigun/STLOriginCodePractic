#include <iostream>
using namespace std;

template <class T>
struct MyIter
{
    typedef T value_type;       //内嵌声明类型（nested type）
    T* ptr;
    MyIter(T* p = 0) : ptr(p) {}
    T& operator*() const { return *ptr; }
};

template <class I>
typename I::value_type
// 必须加上typename，因为T是一个template参数，在具现化之前，编译器对T一无所知
// 编译器此时并不知道MyIter<T>::value_type代表型别，还是成员函数，还是数据成员
func(I ite)
{ return *ite; }

int main()
{
    MyIter<int> ite(new int(8));
    cout << func(ite) << " " << sizeof(func(ite)) << endl;

    MyIter<long long> ite2(new long long(8));
    cout << func(ite2) << " " << sizeof(func(ite2)) << endl;

    return 0;
}