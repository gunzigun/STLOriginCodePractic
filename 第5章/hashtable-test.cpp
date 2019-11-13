// 注意：客户端程序不能直接含入<stl_hashtable.h>,应该含入有用到hashtable的容器头文件
// 例如<hash_set.h>、<hash_map.h>
#include <hash_set>         //for hashtable
#include <iostream>
using namespace std;

int main()
{
    // hash-table
    // <value,key,hash-func,extract-key,equal-key,allocator>
    // note:hash-table has no default ctor

    // 制定保留50个buckets
    hashtable<int,int,hash<int>,identity<int>,equal_to<int>,alloc> iht(50, hash<int>(), equal_to<int>());

    cout << iht.size() << endl;                       // 0
    cout << iht.bucket_count() << endl;               // 53.这是STL提供的第一个质数
    cout << iht.max_bucket_count() << endl;           // 4294967291.这是STL提供的最后一个质数

    iht.insert_unique(59);
    iht.insert_unique(63);
    iht.insert_unique(108);
    iht.insert_unique(2);
    iht.insert_unique(53);
    iht.insert_unique(55);
    cout << iht.size() << endl;                       // 6

    // 以下声明一个hashtable迭代器
    hashtable<int,int,hash<int>,identity<int>,equal_to<int>,alloc>::iterator ite = iht.begin();
    // 以迭代器遍历hashtable，将所有节点的值打印出来
    for(int i=0; i < iht.size(); ++i, ++ite)
    {
        cout << *ite << " ";                        // 53 55 2 108 59 63
    }
    cout << endl;

    // 遍历所有buckets，如果其节点个数不为0，就打印出节点个数
    for(int i=0; i < iht.bucket_count(); ++i)
    {
        int n = iht.elems_in_bucket(i);
        if(n!=0)
        {
            cout << "bucket[" << i << "] has " << n << " elems." << endl;
        }
    }
    // bucket[0] has 1 elems.
    // bucket[2] has 3 elems.
    // bucket[6] has 1 elems.
    // bucket[10] has 1 elems.

    // 为了验证“bucket（list）的容量就是buckets vector的大小”（这是从
    // hashtable<T>::resize()得知的结果），我刻意将元素增加到54个，看看是否发生“表格重建（re-hashing）”
    for (int i = 0; i <= 47; i++)
    {
        iht.insert_equal(i);               
    }
    cout << iht.size() << endl;                      // 54.元素节点个数 
    cout << iht.bucket_count() << endl;              // 97.buckets个数
    // 遍历所有buckets，如果其节点个数不为0，就打印出节点个数
    for (int i = 0; i < iht.bucket_count(); ++i)
    {
        int n = iht.elems_in_bucket(i);
        if(n!=0)
        {
            //cout << "bucket[" << i << "] has " << n << " elems." << endl;
        }
    }
    // 打印结果：bucket[2]和bucket[11]的节点个数为2
    // 其余bucket[0]-bucket[47]的节点个数均为1
    // 此外，bucket[53],bucket[55],bucket[59],bucket[63]的节点个数均为1

    // 以迭代器遍历hashtable，将所有节点的值打印出来
    ite = iht.begin();
    for(int i=0; i < iht.size(); ++i, ++ite)
    {
        cout << *ite << " ";                        
    }
    cout << endl;   

    // 0 1 2 2 3 4 5 6 7 8 9 10 11 108 12-47 53 55 59 63
    cout << *(iht.find(2)) << endl;         // 2
    cout << iht.count(2)  << endl;              //2
}