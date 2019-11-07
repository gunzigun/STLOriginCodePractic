// __STL_CLASS_PARTIAL_SPECIALIZATION
// 一般设计之外，特比针对某些template参数做特殊设计

#include <iostream>
using namespace std;

// 一般化设计
template <class I, class O>
struct testClass
{
    testClass() { cout << "I,O" << endl; }
};

// 特殊化设计
template <class T>
struct testClass<T*, T*>
{
    testClass() { cout << "T*,T*" << endl; }
};

// 特殊化设计
template <class T>
struct testClass<const T*, T*>
{
    testClass() { cout << "const T*,T*" << endl; }
};

int main()
{
    testClass<int, char> obj1;
    testClass<int*, int*> obj2;
    testClass<const int*, int*> obj3;
}

/*
I,O
T*,T*
const T*,T*
*/