// 测试 <stl_config.h>
#include <vector>     // <vector>包含<sti_algobase.h>，<sti_algobase.h>包含<stl_config.h>
#include <iostream>
using namespace std;

int main()
{

#ifdef __sgi
 cout<<"__sgi"<<endl;                 
#endif
#ifdef __GNUC__
 cout<<"__GNUC__"<<endl;
 cout<<__GNUC__<<' '<<__GNUC_MINOR__<<endl;
#endif
#ifdef __STL_NO_DRAND48
 cout<<"I have defined __STL_NO_DRAND48 !"<<endl;
#else
 cout<<"It is a pity that I have not defined __STL_NO_DRAND48 !"<<endl;
#endif
#ifdef __STL__CLASS_PARTIAL_SPECIALIZATION
 cout<<"I have defined __STL_CLASS_PARTIAL_SPECIALIZATION !"<<endl;
#else
 cout<<"It is a pity that __STL_CLASS_PARTIAL_SPECIALIZATION !"<<endl;
#endif

}

/*
__GNUC__
2 91
It is a pity that I have not defined __STL_NO_DRAND48 !
It is a pity that __STL_CLASS_PARTIAL_SPECIALIZATION !
*/

