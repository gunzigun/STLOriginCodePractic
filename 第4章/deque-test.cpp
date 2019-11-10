#include <deque>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    deque<int,alloc,32> ideq(20,9);               // 注意：alloc只适用于G++
    cout << "size=" << ideq.size() << endl;       // size=20
    // 现在，应该已经构造了一个deque，有20个int元素，初值皆为9
    // 缓冲区大小为32bytes

    // 为每一个元素设定新值
    for(int i = 0; i < ideq.size(); ++i)
    {
        ideq[i] = i;
    }

    for(int i = 0; i < ideq.size(); ++i)
    {
        cout << ideq[i] << " ";                   // 0 1 2 3 4 5 6 ... 19    
    }
    cout << endl;

    // 在最尾端增加3个元素，其值为0，1，2
    for (int i = 0; i < 3; ++i)
    {
        ideq.push_back(i);
    }

    // 在最尾端增加1个元素，其值为3
    ideq.push_back(3);

    for(int i = 0; i < ideq.size(); ++i)
    {
        cout << ideq[i] << " ";                   // 0 1 2 3 4 5 6 ... 19 0 1 2 3    
    }
    cout << endl;
    cout << "size=" << ideq.size() << endl;       // size=24

    // 在最前端增加一个元素
    ideq.push_front(99);
    for(int i = 0; i < ideq.size(); ++i)
    {
        cout << ideq[i] << " ";                   // 99 0 1 2 3 4 5 6 ... 19 0 1 2 3   
    }
    cout << endl;
    cout << "size=" << ideq.size() << endl;       // size=25

    // 在最前端增加2个元素,98 97
    ideq.push_front(98);
    ideq.push_front(97);
    for(int i = 0; i < ideq.size(); ++i)
    {
        cout << ideq[i] << " ";                   // 97 98 99 0 1 2 3 4 5 6 ... 19 0 1 2 3   
    }
    cout << endl;
    cout << "size=" << ideq.size() << endl;       // size=27

    // 搜寻数值为99的元素，并打印出来
    deque<int, alloc, 32>::iterator itr;
    itr = find(ideq.begin(), ideq.end(), 99);
    cout << *itr << endl;                         // 99
    cout << *(itr.cur) << endl;                   // 99
}