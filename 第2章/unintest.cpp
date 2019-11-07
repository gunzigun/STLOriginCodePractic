#include <iostream>
using namespace std;

union obj
{   
    union obj *free_list_link;  
    char client_data[1]; 
};

int main() 
{     
    //假设这两个是要分配出去的内存。
    char mem[100] = { 'c' };  
    char mem1[100] = { 'a' }; 

    //现在是每一块内存的开始均是一个union node结构    
    //----------------------------------    
    //| union obj | ....................  
    //----------------------------------  
    
    obj *p1 = (obj *)mem;  // p1指向mem所在位置，并转换成union obj类型指针   
    obj *p2 = (obj *)mem1; // p2指向mem1所在位置，并转换成union obj类型指针
    p1->free_list_link = p2;
 
    //可以看到mem和client_data 两个指针值是一致的
    cout << "mem                  = " << (void*)mem << endl;
    cout << "p1->client_data      = " << (void *)p1->client_data << endl;

    //可以看到mem1和free_list_link 两个指针值是一致的
    cout << "mem1                 = " << (void *)mem1 << endl;
    cout << "p1->free_list_link   = " << (void *)p1->free_list_link << endl;

    mem1[1] = 'f';
    cout << "mem1[1]                      = " << mem1[1] << endl;
    //p1->free_list_link为mem1[0]的地址，传化为char*后+1,则指向mem1[1]
    cout << "(char*)p1->free_list_link+1  = " << (char*)p1->free_list_link+1 << endl;

    return 0;
}
