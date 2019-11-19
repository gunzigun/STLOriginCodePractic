#include <iostream>
#include <functional>
using namespace std;

int main()
{
    // 以下产生一些仿函数实体（对象）
    equal_to<int> equal_to_obj;
    not_equal_to<int> not_equal_to_obj;
    greater<int> greater_obj;
    greater_equal<int> greater_equal_obj;
    less<int> less_obj;
    less_equal<int> less_equal_obj;

    // 以下运用上述函数，履行函数功能
    cout << equal_to_obj(3, 5) << endl;                 // 0
    cout << not_equal_to_obj(3, 5) << endl;             // 1
    cout << greater_obj(3, 5) << endl;                  // 0
    cout << greater_equal_obj(3, 5) << endl;            // 0
    cout << less_obj(3, 5) << endl;                     // 1
    cout << less_equal_obj(3, 5) << endl;               // 1

    // 以下直接以仿函数的临时对象履行函数功能
    // 语法分析：functor<T>()是一个临时对象，后面接一对小括号
    // 意指调用function call operator
    cout << equal_to<int>()(3, 5) << endl;                 // 0
    cout << not_equal_to<int>()(3, 5) << endl;             // 1
    cout << greater<int>()(3, 5) << endl;                  // 0
    cout << greater_equal<int>()(3, 5) << endl;            // 0
    cout << less<int>()(3, 5) << endl;                     // 1
    cout << less_equal<int>()(3, 5) << endl;               // 1

}