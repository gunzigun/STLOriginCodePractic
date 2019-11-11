#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    // test priority queue
    int ia[9] = {0,1,2,3,4,8,9,3,5};
    priority_queue<int> ipq(ia, ia+9);
    cout << "size=" << ipq.size() << endl;              // size=9

    for(int i=0; i < ipq.size(); ++i)
    {
        cout << ipq.top() << " ";              // 9 9 9 9 9 9 9 9 9 
    }
    cout << endl;

    while(!ipq.empty())
    {
        cout << ipq.top() << " ";              // 9 8 5 4 3 3 2 1 0
        ipq.pop();                  
    }
    cout << endl;
}