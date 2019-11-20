#include <iterator>     // for iterator adapters
#include <deque>
#include <algorithm>           // for copy
#include <iostream>
using namespace std;

int main()
{
    // 将out-ite绑定到cout，每次对out-ite指派一个元素，就后接一个 “ ”
    ostream_iterator<int> outite(cout, " ");

    int ia[] = {0,1,2,3,4,5};
    deque<int> id(ia,ia+6);

    // 将所有元素拷贝到outite（那么也就是拷贝到cout）
    copy(id.begin(), id.end(), outite);             // 输出 0 1 2 3 4 5
    cout << endl;

    // 将ia[]的部分元素拷贝到id内，使用front_insert_iterator
    // 注意，front_insert_iterator会将assign操作改为push_front操作
    // vector不支持push_front(),这就是本例不以vector为示范对象的原因
    copy(ia+1, ia+2, front_inserter(id));
    copy(id.begin(), id.end(), outite);             // 输出 1 0 1 2 3 4 5
    cout << endl;

    // 将ia[]的部分元素拷贝到id内，使用back_insert_iterator
    copy(ia+3, ia+4, back_inserter(id));
    copy(id.begin(), id.end(), outite);             // 输出 1 0 1 2 3 4 5 3
    cout << endl;

    // 搜寻元素5所在位置
    deque<int>::iterator ite = find(id.begin(), id.end(), 5);
    // 将ia[]的部分元素拷贝到id内，使用insert_iterator
    copy(ia+0, ia+3, inserter(id, ite));
    copy(id.begin(), id.end(), outite);             // 输出 1 0 1 2 3 4 (0 1 2) 5 3
    cout << endl;

    // 将所有元素逆向拷贝到outite
    // rbegin()和rend()与reverse_iterator有关，
    copy(id.rbegin(), id.rend(), outite);           // 3 5 2 1 0 4 3 2 1 0 1
    cout << endl;

    deque<int>::reverse_iterator rite2(id.end());
    cout << *(rite2);                 // 3
    cout << *(++++++rite2);           // 1(前进3个位置后取值)
    cout << *(--rite2);               // 2(后退1个位置后取值)
    cout << *(rite2.base());          // 5(恢复正向迭代器后，取值)
    cout << rite2[3];                 // 4(前进3个位置后取值)
    cout << endl;

    // 以下，将inite绑定到cin，将元素拷贝到inite，知道eos出现
    istream_iterator<int> inite(cin), eos;
    copy(inite, eos, inserter(id, id.begin()));
    copy(id.begin(), id.end(), outite);           // 32 26 99 1 0 1 2 3 4 0 1 2 5 3
    cout << endl;

}

