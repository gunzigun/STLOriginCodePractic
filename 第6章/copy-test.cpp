#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <list>
using namespace std;

class C
{
public:
    C() : _data(3) { }
    // there is a trivial assignment operator
private:
    int _data;
};

int main()
{
    // 测试1
    const char ccs[5] = {'a','b','c','d','e'};  // 数据来源
    char ccd[5];                                // 数据去处
    copy(ccs, ccs+5, ccd);                      // 调用的版本是copy(const char*)
    cout << "-----------------------------------------" << endl;

    // 测试2
    const wchar_t cwcs[5] = {'a','b','c','d','e'};  // 数据来源
    wchar_t cwcd[5];                                   // 数据去处
    copy(cwcs, cwcs+5, cwcd);                       // 调用的版本是copy(const wchar_t*)
    cout << "-----------------------------------------" << endl;

    // 测试3
    int ia[5] = {0,1,2,3,4};
    copy(ia, ia+5, ia);             // 注意，数据来源和数据去除相同，这是允许的
    cout << "-----------------------------------------" << endl;
    //copy()
    //__copy_dispatch(T*, T*)
    //__copy_t(true_type)

    // 测试4
    // 注：list 迭代器被归类为InputIterator
    list<int> ilists(ia, ia+5);         // 数据来源
    list<int> ilistd(5);                // 数据取出
    copy(ilists.begin(), ilists.end(), ilistd.begin());
    cout << "-----------------------------------------" << endl;
    //copy()
    //__copy_dispatch()
    //__copy(InputIterator)

    // 测试5
    // 注：vector迭代器被归类为原生指针（native pointer）
    vector<int> ivecs(ia, ia+5);       // 数据来源
    // 以上会产生输出信息，原因见稍后正文说明，此处对输出信息咱不显
    vector<int> ivecd(5);              // 数据去处
    copy(ivecs.begin(), ivecs.end(), ivecd.begin());
    cout << "-----------------------------------------" << endl;
    //copy()
    //__copy_dispatch(T*, T*)
    //__copy_t(true_type)

    // 测试6
    // class C 具备 trivial operator=
    C c[5];
    vector<C> Cvs(c, c+5);              // 数据来源
    // 以上会产生输出信息，原因见稍后正文说明，此处对输出信息暂略不显
    vector<C> Cvd(5);                   // 数据去处 
    copy(Cvs.begin(), Cvs.end(), Cvd.begin());
    cout << "-----------------------------------------" << endl;
    //copy()
    //__copy_dispatch(T*, T*)
    //__copy_t(false_type)
    //__copy_d

    // 测试7
    // 注：deque迭代器被归类为random access iterator
    deque<C> Cds(c, c+5);
    deque<C> Cdd(5);
    copy(Cds.begin(), Cds.end(), Cdd.begin());
    //copy()
    //__copy_dispatch()
    //__copy(RandomAccessIterator)
    //__copy_d
}