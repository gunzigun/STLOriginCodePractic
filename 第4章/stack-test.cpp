#include <stack>
#include <list>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    stack<int, list<int> > istack;
    istack.push(1);
    istack.push(3);
    istack.push(5);
    istack.push(7);

    cout << istack.size() << endl;           // 4
    cout << istack.top() << endl;            // 7

    istack.pop(); cout << istack.top() << endl;         // 5
    istack.pop(); cout << istack.top() << endl;         // 3
    istack.pop(); cout << istack.top() << endl;         // 1

    cout << istack.size() << endl;           // 1
}