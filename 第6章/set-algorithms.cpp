#include <set>              // multiset
#include <iostream>
#include <algorithm>
#include <iterator>         // ostream_iterator
using namespace std;

template <class T>
struct display
{
    void operator()(const T& x)
    {
        cout << x << " ";
    }
};

int main()
{
    int ia1[6] = {1,3,5,7,9,11};
    int ia2[7] = {1,1,2,3,5,8,13};

    multiset<int> S1(ia1, ia1+6);
    multiset<int> S2(ia2, ia2+7);

    for_each(S1.begin(), S1.end(), display<int>());
    cout << endl;
    for_each(S2.begin(), S2.end(), display<int>());
    cout << endl;

    multiset<int>::iterator first1 = S1.begin();
    multiset<int>::iterator last1 = S1.end();
    multiset<int>::iterator first2 = S2.begin();
    multiset<int>::iterator last2 = S2.end();

    cout << "Union of S1 and S2: ";
    set_union(first1, last1, first2, last2, ostream_iterator<int>(cout, " "));
    cout << endl;

    first1 = S1.begin();
    first2 = S2.begin();
    cout << "Intersection of S1 and S2: ";
    set_intersection(first1, last1, first2, last2, ostream_iterator<int>(cout, " "));
    cout << endl;

    first1 = S1.begin();
    first2 = S2.begin();
    cout << "Difference of S1 and S2 (S1-S2): ";
    set_difference(first1, last1, first2, last2, ostream_iterator<int>(cout, " "));
    cout << endl;

    first1 = S1.begin();
    first2 = S2.begin();
    cout << "Symmetric difference of S1 and S2 ( (S1-S2)并(S2-S1) ) : ";
    set_symmetric_difference(first1, last1, first2, last2, ostream_iterator<int>(cout, " "));
    cout << endl;

    first1 = S2.begin();
    first2 = S1.begin();
    last1 = S2.end();
    last2 = S1.end();
    cout << "Difference of S2 and S1 (S2-S1): ";
    set_difference(first1, last1, first2, last2, ostream_iterator<int>(cout, " "));
    cout << endl;

}