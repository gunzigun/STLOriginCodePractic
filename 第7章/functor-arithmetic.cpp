#include <iostream>
#include <functional>
using namespace std;

int main()
{
    // 以下产生一些仿函数的实体（对象）
    plus<int> plusobj;
    minus<int> minusobj;
    multiplies<int> multipliesobj;
    divides<int> dividesobj;
    modulus<int> modulusobj;
    negate<int> negateobj;

    // 以下运用上述函数，履行函数功能
    cout << plusobj(3, 5) << endl;                 // 8
    cout << minusobj(3, 5) << endl;                // -2
    cout << multipliesobj(3, 5) << endl;           // 15
    cout << dividesobj(3, 5) << endl;              // 0
    cout << modulusobj(3, 5) << endl;              // 3
    cout << negateobj(3) << endl;                  // -3

    // 以下直接以仿函数的临时对象履行函数功能
    // 语法分析：functor<T>()是一个临时对象，后面接一对小括号
    // 意指调用function call operator
    cout << plus<int>()(3, 5) << endl;                // 8
    cout << minus<int>()(3, 5) << endl;               // -2
    cout << multiplies<int>()(3, 5) << endl;          // 15
    cout << divides<int>()(3, 5) << endl;             // 0
    cout << modulus<int>()(3, 5) << endl;             // 3
    cout << negate<int>()(3) << endl;                 // -3
}