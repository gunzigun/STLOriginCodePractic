#include <iostream>
#include <cstdlib>
using namespace std;

int fcmp(const void* elem1, const void* elem2)
{
    const int* i1 = (const int*)elem1;
    const int* i2 = (const int*)elem2;

    if(*i1 < *i2)
    {
        return -1;
    }
    else if(*i1 == *i2)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void main()
{
    int ia[10] = {32,92,67,58,10,4,25,52,59,54};
    for (int i = 0; i < 10; ++i)
    { 
       cout << ia[i] << " ";               //32,92,67,58,10,4,25,52,59,54
    }
    cout << endl; 

    qsort(ia, sizeof(ia)/sizeof(int), sizeof(int), fcmp);

    for (int i = 0; i < 10; ++i)
    {
        cout << ia[i] << " ";           //4,10,25,32,52,54,58,59,67,92
    }
    cout << endl;
}