// 此文件只能在VS的VC环境下编译，使用cl命令执行编译

#include "jjalloc.h"
#include <vector>
#include <iostream>
using namespace std;

int main()
{
    int ia[5] = {0,1,2,3,4};
    unsigned int i;

    vector<int, JJ::allocator<int> > iv(ia, ia+5);
    //vector<int> iv(ia, ia+5);

    for(i=0; i<iv.size(); ++i)
    {
        cout << iv[i] << " ";
    }
    cout << endl;
}