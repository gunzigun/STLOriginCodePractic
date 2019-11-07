// const static integral members 可以再类内初始化

#include <iostream>
using namespace std;

template <typename T>
class testClass
{
public:
    const static int _datai = 5;
    const static long long _datall = 3L;
    static const char _datac = 'c';
};

int main()
{
    cout << testClass<int>::_datai << endl;     // 5
    cout << testClass<int>::_datall << endl;      // 3
    cout << testClass<int>::_datac << endl;         // c
}