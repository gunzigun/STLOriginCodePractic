#include <algorithm> 
#include <vector> 
#include <functional>   
#include <iostream>  
using namespace std;  
  
// 本文件用cl.exe编译

struct even   
{  
    bool operator() (int x) const  
    {  
        return x%2 ? false : true;   
    }   
};   

template<class T>   
struct display  
{  
    void operator()(T &x)const  
    {  
        cout << x << " ";   
    }      
}; 
  
int main()  
{  
    int ia[] = {12,17,20,22,23,30,33,40};  
    vector<int> iv(ia,ia+sizeof(ia)/sizeof(int));  

    // 在不破坏排序状态的原则下，可插入value的第一个位置    
    cout << *lower_bound(iv.begin(),iv.end(), 21) << endl; //22
    // 在不破坏排序状态的原则下，可插入value的最后一个位置     
    cout << *upper_bound(iv.begin(),iv.end(), 21) << endl; //22    
    cout << *lower_bound(iv.begin(),iv.end(), 22) << endl; //22   
    cout << *upper_bound(iv.begin(),iv.end(), 22) << endl; //23  
      
    // 面对有序区间，可以二分查找法寻找某个元素
    cout << binary_search(iv.begin(),iv.end(),33) << endl; //1  
    cout << binary_search(iv.begin(),iv.end(),34) << endl; //0   
       
    //下一个排列组合
    next_permutation(iv.begin(), iv.end());   
    for_each(iv.begin(),iv.end(),display<int>());
    cout << endl;
    // 12 17 20 22 23 30 40 33 

    //上一个排列组合 
    prev_permutation(iv.begin(), iv.end());   
    for_each(iv.begin(),iv.end(),display<int>());    
    cout << endl;  
    // 12 17 20 22 23 30 33 40 
      
    //随机重排 
    random_shuffle(iv.begin(), iv.end());   
    for_each(iv.begin(),iv.end(),display<int>());    
    cout << endl;
    // 23 17 33 20 12 30 40 22
      
    //将iv.begin()+4 - iv.begin()个元素排序，放进
    //[iv.begin(), iv.begin()+4)区间内，剩余元素不保证维持原相对次序
    //[first,middle)建立大根堆，然后[middle,last)遍历，如果比根值小，这替换根，大根堆重新排列
    partial_sort(iv.begin(), iv.begin()+4, iv.end());   
    for_each(iv.begin(),iv.end(),display<int>());      
    cout << endl;
    // 12 17 20 22 33 30 40 23
      
    //排序（缺省为递增排序）   
    sort(iv.begin(), iv.end());  
    for_each(iv.begin(),iv.end(),display<int>());     
    cout << endl; 
    // 12 17 20 22 23 30 33 40
      
    //排序（设置为递减）   
    sort(iv.begin(), iv.end(), greater<int>());  
    for_each(iv.begin(),iv.end(),display<int>());     
    cout << endl;
    // 40 33 30 23 22 20 17 12 
    
    //在iv尾端附加新元素，使成为 40 33 30 23 22 20 17 12 22 30 17
    iv.push_back(22);  
    iv.push_back(30);  
    iv.push_back(17);  
      
    //排序并保持原相对位置   
    stable_sort(iv.begin(), iv.end());   
    for_each(iv.begin(),iv.end(),display<int>());   
    cout << endl; 
    // 12 17 17 20 22 22 23 30 30 33 40

    //面对一个有序空间，找出其中的一个子空间，其内每个元素都与特定元素值相同
    //返回该子区间的头尾迭代器
    //如果没有这样的子空间，返回的头尾迭代器均指向该特定元素可插入
    //(并仍保持排序)的地点
    pair<vector<int>::iterator,vector<int>::iterator> pairIte;  
    pairIte = equal_range(iv.begin(), iv.end(), 22);   
    cout << *(pairIte.first) << endl;      //lowerbound 22   
    cout << *(pairIte.second) << endl;     //upperbound 23  
    pairIte = equal_range(iv.begin(), iv.end(), 25);   
    cout << *(pairIte.first) << endl;      //lowerbound 30   
    cout << *(pairIte.second) << endl;     //upperbound 30  
       
    //打乱顺序   
    random_shuffle(iv.begin(),iv.end());   
    for_each(iv.begin(),iv.end(),display<int>());      
    cout << endl; 
    // 22 33 12 40 20 22 23 30 17 17 30
      
    //将小于iv.begin+5的放到左边  (22)
    nth_element(iv.begin(), iv.begin()+5, iv.end());   
    for_each(iv.begin(),iv.end(),display<int>());      
    cout << endl; 
    // 12 17 17 20 22 22 23 30 30 33 40  
      
    //将大于iv.begin+5的放到左边  (22) 
    nth_element(iv.begin(), iv.begin()+5, iv.end(), greater<int>());   
    for_each(iv.begin(),iv.end(),display<int>());      
    cout << endl; 
    // 40 33 30 30 23 22 22 20 17 17 12
      
    //以“是否符合even()条件”为依据，将符合者置于左段，不符合者置于右段
    //保证维持原有的相对位置，如不需要“维持原有的相对位置”，可改用partition();
    stable_partition(iv.begin(), iv.end(), even());  
    for_each(iv.begin(),iv.end(),display<int>());     
    cout << endl; 
    // 40 30 30 22 22 20 12 33 23 17 17
}