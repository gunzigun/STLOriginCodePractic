// 特意的零时对象
// 测试仿函数用于for_each()的情形

#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

template <typename T>
class print
{
public:
    void operator()(const T& elem)
    {
        cout << elem << " ";        
    }   
};

int main()
{
    int ia[6] = {0,1,2,3,4,5};
    vector<int> iv(ia, ia+6);

    // print<int>() 是一个临时对象，不是一个函数调用操作, 仿函数
    for_each(iv.begin(), iv.end(), print<int>());
    
}