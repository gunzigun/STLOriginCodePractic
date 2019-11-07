// __STL_TEMPLATE_NULL
// 测试 class template explicit specialization

#include <iostream>
using namespace std;

// 将__STL_TEMPLATE_NULL定义为template<>, 可以
// 若定义为空，则只适用于GCC编译器
#define __STL_TEMPLATE_NULL template<> 

template <class Key> 
struct  hash
{
    void operator() () { cout << "hash<T>" << endl; }
};

__STL_TEMPLATE_NULL
struct hash<char>
{
    void operator() () { cout << "hash<char>" << endl; }
};

__STL_TEMPLATE_NULL
struct hash<unsigned char>
{
    void operator() () { cout << "hash<unsigned char>" << endl; }
};

int main()
{
    hash<long> t1;
    hash<char> t2;
    hash<unsigned char> t3;
    t1();       //hash<T>
    t2();       //hash<char>
    t3();       //hash<unsigned char>
}