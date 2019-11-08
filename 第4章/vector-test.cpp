#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int i;
    vector<int> iv(2,9);
    cout << "size=" << iv.size() << endl;                       // size=2
    cout << "capacity=" << iv.capacity() << endl;               // capacity=2

    iv.push_back(1);
    cout << "size=" << iv.size() << endl;                       // size=3
    cout << "capacity=" << iv.capacity() << endl;               // capacity=4(这里是变成之前size的两倍)

    iv.push_back(2);
    cout << "size=" << iv.size() << endl;                       // size=4
    cout << "capacity=" << iv.capacity() << endl;               // capacity=4

    iv.push_back(3);
    cout << "size=" << iv.size() << endl;                       // size=5
    cout << "capacity=" << iv.capacity() << endl;               // capacity=8(这里是变成之前size的两倍)

    iv.push_back(4);
    cout << "size=" << iv.size() << endl;                       // size=6
    cout << "capacity=" << iv.capacity() << endl;               // capacity=8

    for(i=0; i<iv.size(); ++i)
    {
        cout << iv[i] << " ";                                   // 9 9 1 2 3 4 
    }
    cout << endl;

    iv.push_back(5);
    cout << "size=" << iv.size() << endl;                       // size=7
    cout << "capacity=" << iv.capacity() << endl;               // capacity=8

    for(i=0; i<iv.size(); ++i)
    {
        cout << iv[i] << " ";                                   // 9 9 1 2 3 4 5
    }
    cout << endl;

    iv.pop_back();
    iv.pop_back();
    cout << "size=" << iv.size() << endl;                       // size=5
    cout << "capacity=" << iv.capacity() << endl;               // capacity=8

    iv.pop_back();
    cout << "size=" << iv.size() << endl;                       // size=4
    cout << "capacity=" << iv.capacity() << endl;               // capacity=8

    vector<int>::iterator ivite = find(iv.begin(), iv.end(), 1);
    if(ivite) iv.erase(ivite);
    cout << "size=" << iv.size() << endl;                       // size=3
    cout << "capacity=" << iv.capacity() << endl;               // capacity=8
    for(i=0; i<iv.size(); ++i)
    {
        cout << iv[i] << " ";                                   // 9 9 2 
    }
    cout << endl;

    ivite = find(iv.begin(), iv.end(), 2);
    if(ivite) iv.insert(ivite,3,7);
    cout << "size=" << iv.size() << endl;                       // size=6
    cout << "capacity=" << iv.capacity() << endl;               // capacity=8
    for(i=0; i<iv.size(); ++i)
    {
        cout << iv[i] << " ";                                   // 9 9 7 7 7 2 
    }
    cout << endl;

    iv.clear();
    cout << "size=" << iv.size() << endl;                       // size=0
    cout << "capacity=" << iv.capacity() << endl;               // capacity=8
}
