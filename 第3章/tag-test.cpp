#include <iostream>
using namespace std;

struct B { };
struct D1 : public B { };
struct D2 : public D1 { };

template <class I>
func(I& p, B)
{
    cout << "B version" << endl;
}

template <class I>
func(I& p, D2)
{
    cout << "D2 version" << endl;
}

int main()
{
    int *p;
    func(p, B());         // 参数与参数完全吻合，输出：“B version”
    func(p, D1());        // 参数与参数未能完全吻合：因继承关系而自动传递调用
                          // 输出：“B version”
    func(p, D2());        // 参数与参数完全吻合，输出：“D2 version”
}