#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;

template <class T>
struct display
{
    void operator()(const T& x)
    {
        cout << x << " ";
    }
};

int main()
{
    {
        int ia[] = {0,1,2,3,4,5,6,7,8};

        // 以下，输出区间的终点与输入区间重叠，没问题
        copy_backward(ia+2, ia+7, ia+9);
        for_each(ia, ia+9, display<int>());         // 0 1 2 3 2 3 4 5 6
        cout << endl;
    }

    cout << "-----------------------------------------" << endl;

    {
        int ia[] = {0,1,2,3,4,5,6,7,8};

        // 以下，输出区间的起点与输入区间重叠，可能会有问题
        copy_backward(ia+2, ia+7, ia+5);
        for_each(ia, ia+9, display<int>());         // 2 3 4 5 6 5 6 7 8
        cout << endl;
        // 本例结果正确，因为调用的copy算法使用memmove()执行实际复制操作
    }

    cout << "-----------------------------------------" << endl;

    {
        int ia[] = {0,1,2,3,4,5,6,7,8};
        deque<int> id(ia, ia+9);
        
        deque<int>::iterator first = id.begin();
        deque<int>::iterator last = id.end();
        ++++first;                  // advance(first, 2);
        cout << *first << endl;     // 2
        ----last;                   // advance(last, -2);
        cout << *last << endl;      // 7

        deque<int>::iterator result = id.end();

        // 以下，输出区间的终点与输入区间重叠，没问题
        copy_backward(first, last, result);
        for_each(id.begin(), id.end(), display<int>());         // 0 1 2 3 2 3 4 5 6
        cout << endl;
    }

    cout << "-----------------------------------------" << endl;

    {
        int ia[] = {0,1,2,3,4,5,6,7,8};
        deque<int> id(ia, ia+9);
        
        deque<int>::iterator first = id.begin();
        deque<int>::iterator last = id.end();
        ++++first;                  // advance(first, 2);
        cout << *first << endl;     // 2
        ----last;                   // advance(last, -2);
        cout << *last << endl;      // 7

        deque<int>::iterator result = id.begin();
        advance(result, 5);
        cout << *result << endl;    // 5

        // 以下，输出区间的起点与输入区间重叠，可能会有问题
        copy_backward(first, last, result);
        for_each(id.begin(), id.end(), display<int>());         // 6 5 6 5 6 5 6 7 8
        cout << endl;
        // 本例结果错误，因为调用的copy算法不再使用memmove()执行实际复制操作
    }
}