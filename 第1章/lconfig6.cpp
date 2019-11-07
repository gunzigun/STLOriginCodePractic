// __STL_FUNCTION_TMPL_PARTIAL_ORDER
// 

#include <iostream>
using namespace std;

class alloc {};

template <class T, class Alloc = alloc>
class vector 
{
public:
    void swap(vector<T, Alloc>&) { cout << "swap()" << endl; }
};

//#define __STL_FUNCTION_TMPL_PARTIAL_ORDER

#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER
template <class T, class Alloc>
inline void swap(vector<T, Alloc>& x, vector<T, Alloc>& y)
{
    x.swap(y);
}
#endif

int main()
{
    vector<int> x,y;
    swap(x,y);
}