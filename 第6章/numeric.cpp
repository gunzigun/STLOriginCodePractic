#include <numeric>
#include <vector>
#include <functional>
#include <iostream>
#include <iterator>         // ostream_iterator
using namespace std;

int main()
{
    int ia[5] = {1, 2, 3, 4, 5};
    vector<int> iv(ia, ia+5);

    cout << accumulate(iv.begin(), iv.end(), 0) << endl;
    // 15, i.e. 0 + 1 + 2 + 3 + 4 + 5

    cout << accumulate(iv.begin(), iv.end(), 0, minus<int>()) << endl;
    // -15, i.e. 0 - 1 - 2 - 3 - 4 - 5

    cout << inner_product(iv.begin(), iv.end(), iv.begin(), 10) << endl;
    // 65, i.e. 10 + 1*1 + 2*2 + 3*3 + 4*4 + 5*5

    cout << inner_product(iv.begin(), iv.end(), iv.begin(), 10, minus<int>(), plus<int>()) << endl;
    // -20 i.e. 10 - 1+1 - 2+2 - 3+3 - 4+4 - 5+5

    // 以下这个迭代器将绑定到cout，作为输出用
    ostream_iterator<int> oite(cout, " ");

    partial_sum(iv.begin(), iv.end(), oite);
    cout << endl;
    // 1 3(1+2) 6(3+3) 10(6+4) 15(10+5) (第n个新元素是前n个旧元素的相加总计)

    partial_sum(iv.begin(), iv.end(), oite, minus<int>());
    cout << endl;
    // 1 -1(1-2) -4(-1-3) -8(-4-4) -13(-8-5) (第n个新元素是前n个旧元素的运算总计)

    adjacent_difference(iv.begin(), iv.end(), oite);
    cout << endl;
    // 1 1(2-1) 1(3-2) 1(4-3) 1(5-4) (#1元素照录，#n新元素，等于#n旧元素-#n-1旧元素)

    adjacent_difference(iv.begin(), iv.end(), oite, plus<int>());
    cout << endl;
    // 1 3(2+1) 5(3+2) 7(4+3) 9(5+4) (#1元素照录，#n新元素，等于 op(#n旧元素, #n-1旧元素))

    cout << power(10, 3) << endl;       // 1000, i.e. 10*10*10
    cout << power(10, 3, plus<int>()) << endl;   // 30, i.e. 10+10+10

    int n = 3;
    iota(iv.begin(), iv.end(), n);          // 在指定区间内填入n，n+1，n+2...
    for (int i = 0; i < iv.size(); ++i)
        cout << iv[i] << " ";               // 3 4 5 6 7
}