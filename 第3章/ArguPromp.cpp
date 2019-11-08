#include <iostream>
using namespace std;

template <class I, class T>
void func_impl(I iter, T t)
{
    T temp;
    cout << sizeof(temp) << endl; 
}

template <class I>
inline
void func(I iter)
{
    func_impl(iter, *iter);
}

int main()
{
    int a;
    func(&a);

    long long b;
    func(&b); 
}