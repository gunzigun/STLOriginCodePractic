#include <queue>
#include <list>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    queue<int, list<int> > iqueue;
    iqueue.push(1);
    iqueue.push(3);
    iqueue.push(5);
    iqueue.push(7);

    cout << iqueue.size() << endl;           // 4
    cout << iqueue.front() << endl;            // 1

    iqueue.pop(); cout << iqueue.front() << endl;         // 3
    iqueue.pop(); cout << iqueue.front() << endl;         // 5
    iqueue.pop(); cout << iqueue.front() << endl;         // 7

    cout << iqueue.size() << endl;           // 1
}