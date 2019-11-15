#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
using namespace std;

template <class T>
struct display
{
    void operator()(const T& x) const
    {
        cout << x << " ";
    }
};

int main()
{
    int ia[9] = {0,1,2,3,4,5,6,7,8};
    vector<int> iv1(ia,ia+5);
    vector<int> iv2(ia,ia+9);

    // {0,1,2,3,4} v.s {0,1,2,3,4,5,6,7,8}
    cout << *(mismatch(iv1.begin(), iv1.end(), iv2.begin()).first) << endl;             // 0
    cout << *(mismatch(iv1.begin(), iv1.end(), iv2.begin()).second) << endl;            // 5
    // 以上判断两个区间的第一个不匹配点，返回一个由两个迭代器组成的pair.
    // 其中第一个迭代器指向第一区间的不匹配点，第二个迭代器指向第二区间的不匹配点
    // 上述写法很危险，应该先判断，迭代器是否不等于容器的end(),然后才可以做输出操作

    // 如果两个序列在[first,last)区间内相等，equal()返回true
    // 如果第二序列的元素比较多，多出来的元素不予考虑
    cout << equal(iv1.begin(), iv1.end(), iv2.begin()) << endl;                       // 1,true

    cout << equal(iv1.begin(), iv1.end(), &ia[3]) << endl;                            
    // {0,1,2,3,4} 等于 {3,4,5,6,7} ?           // 0,false

    cout << equal(iv1.begin(), iv1.end(), &ia[3], less<int>()) << endl;               
    // {0,1,2,3,4} 小于 {3,4,5,6,7} ?           // 1,true

    fill(iv1.begin(), iv1.end(), 9);                // 区间内全部填9
    for_each(iv1.begin(), iv1.end(), display<int>());           // 9 9 9 9 9
    cout << endl;

    fill_n(iv1.begin(), 3, 7);                // 从迭代器所指位置开始，填3个7
    for_each(iv1.begin(), iv1.end(), display<int>());           // 7 7 7 9 9
    cout << endl;

    vector<int>::iterator ite1 = iv1.begin();           // (指向7)
    vector<int>::iterator ite2 = ite1;                  
    advance(ite2, 3);                                   // (指向9)

    iter_swap(ite1,ite2);                               // 将两个迭代器所指函数元素对调
    cout << *ite1 << " " << *ite2 << endl;              // 9 7
    for_each(iv1.begin(), iv1.end(), display<int>());           // 9 7 7 7 9
    cout << endl;

    // 以下取两者之大值
    cout << max(*ite1, *ite2) << endl;                  // 9
    // 以下取两者之小值
    cout << min(*ite1, *ite2) << endl;                  // 7

    // 千万不要错写成以下那样，那意思是，取两个迭代器（本身）之大者（或小者），
    // 然后再打印其所指之值，注意，迭代器本身的大小，对用户没有意义
    cout << *max(ite1, ite2) << endl;                   // 7
    cout << *min(ite1, ite2) << endl;                   // 9

    // 此刻状态，iv1:{9 7 7 7 9}, iv2:{0 1 2 3 4 5 6 7 8}
    swap(*iv1.begin(), *iv2.begin());            // 将两数值对调
    for_each(iv1.begin(), iv1.end(), display<int>());           // 0 7 7 7 9
    cout << endl;

    for_each(iv1.begin(), iv1.end(), display<int>());           // 9 1 2 3 4 5 6 7 8 
    cout << endl;

    // 准备两个字符串数组
    string stra1[] = {"Jamie", "JJHou", "Jason"};
    string stra2[] = {"Jamie", "JJhou", "Jerry"};

    cout << lexicographical_compare(stra1, stra1+2, stra2, stra2+2) << endl;                        // (stra1 小于 stra2) ？ 1
    cout << lexicographical_compare(stra1, stra1+2, stra2, stra2+2, greater<string>()) << endl;     // (stra1 大于 stra2) ？ 0
}   
