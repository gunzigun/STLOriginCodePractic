#include <algorithm>  
#include <vector>  
#include <functional>  
#include <iostream>
using namespace std;  
  
template <class T>  
struct display  
{  
    void operator()(const T &x) const  
    {  
        cout<< x <<" ";   
    }       
};   
  
struct even  
{  
    bool operator()(int x)const  
    {  
        return x % 2 ? false : true;   
    }   
};  
  
class even_by_two  
{  
private:  
    static int _x; //注意静态变量   
public:  
    int operator()() const  
    {  
        return _x += 2; 
    }       
};  
int even_by_two::_x=0;   
  
int main()  
{  
    int ia[] = {0,1,2,3,4,5,6,6,6,7,8};  
    vector<int> iv(ia, ia+sizeof(ia)/sizeof(int));  
      
    //找出iv之中相邻元素值相等的第一个元素   
    cout<< *adjacent_find(iv.begin(),iv.end()) << endl;  // 6

    cout<< *adjacent_find(iv.begin(),iv.end(),equal_to<int>()) << endl; //仿函数   // 6
      
    cout<< count(iv.begin(),iv.end(),6) << endl;//统计6的个数   
    
    cout<< count_if(iv.begin(),iv.end(),bind2nd(less<int>(),7)) << endl;  //统计小于7的元素的个数 :9个  
      
    cout<< *find(iv.begin(),iv.end(),4) << endl; //返回元素为4的元素的下标位置  
      
    cout<< *find_if(iv.begin(),iv.end(),bind2nd(greater<int>(),2)) << endl; //返回大于2的第一个元素的位置：3  


    vector<int> iv2(ia+6,ia+8);    
    for(int i=0;i<iv2.size();++i)  
      cout << iv2[i] << " ";     //6 6
    cout << endl; 

    //返回iv序列中 iv2序列 出现的最后一个位置（再往后三个位置的值）：8   
    cout << "find_end:" << *(find_end(iv.begin(),iv.end(),iv2.begin(),iv2.end())+3) << endl;   
    //返回iv序列中 iv2序列 出现的第一个位置（再往后三个位置的值）：7  
    cout << "find_first_of:" << *(find_first_of(iv.begin(),iv.end(),iv2.begin(),iv2.end())+3) << endl; 
      
    for_each(iv.begin(),iv.end(),display<int>());   
    cout<<endl;                         // iv:0 1 2 3 4 5 6 6 6 7 8
       
    //以下错误：generate的第三个参数（仿函数）本身不得有任何参数
    //generate(iv.begin(),iv.end(),bind2nd(plus<int>(),3)); //error
    //遍历整个iv2区间并执行 even_by_two操作(得改变元素内容)   
    generate(iv2.begin(),iv2.end(),even_by_two());  
    for_each(iv2.begin(),iv2.end(),display<int>());   // 2 4 
    cout<<endl;  
       
    //遍历区间（给出起点和长度），对每个遍历元素执行even_by_two操作   
    generate_n(iv.begin(),3,even_by_two());  
    for_each(iv.begin(),iv.end(),display<int>()); //由于_X是static 所以接着 增长   6 8 10 3 4 5 6 6 6 7 8
    cout<<endl;                 
       
    // 6 8 10 3 4 5 6 6 6 7 8
    //删除（但不删除）元素6，尾端可能有残余数据（可另以容器之erase函数去除之）
    remove(iv.begin(),iv.end(),6);        // 6 [8 10 3 4 5 6 | 6 6 7 8] -> [8 10 3 4 5 7 8] (6 6 7 8)
    for_each(iv.begin(),iv.end(),display<int>());  
    cout<<endl; // 8 10 3 4 5 7 8 6 6 7 8 (最后四个是残留数据)   
           
    vector<int> iv3(12);//重新申请空间  
    //遍历所有元素，把不等于6的元素，拷贝到iv3
    remove_copy(iv.begin(),iv.end(),iv3.begin(),6);  
    for_each(iv3.begin(),iv3.end(),display<int>());   
    cout<<endl; //8 10 3 4 5 7 8 7 8 (0 0 0)（最后三个是残留元素）   
        
    //将小于6的元素 "删除" iv 此时为 8 10 3 4 5 7 8 6 6 7 8  =  8 10 (3 4 5) [7 8 6 | 6 7 8]
    remove_if(iv.begin(),iv.end(),bind2nd(less<int>(),6));   // 8 10 [7 8 6 6 7 8] (6 7 8) (最后三个是残留元素) 
    for_each(iv.begin(),iv.end(),display<int>());    
    cout<<endl;  
        
    //将小于7的元素 "删除" ,此时iv： 8 10 7 8 6 6 7 8 6 7 8 -> [8 10 7 8 7 8 7 8]
    // iv3: [8 10 3 4 5 7 8 7] (8 0 0 0) 
    remove_copy_if(iv.begin(),iv.end(),iv3.begin(),bind2nd(less<int>(),7));  
    for_each(iv3.begin(),iv3.end(),display<int>());   //  [8 10 7 8 7 8 7 8] (8 0 0 0) (最后4个是残余数据)
    cout<<endl;
        
    cout << "---------------------------------------------------------------------------" << endl;

    //将容器中6 替换为 3   
    replace(iv.begin(),iv.end(),6,3);  
    for_each(iv.begin(),iv.end(),display<int>());  
    cout<<endl; //iv:8 10 7 8 3 3 7 8 3 7 8   
      
     
    //将容器中3 替换为 5 放入另一个容器   
    replace_copy(iv.begin(),iv.end(),iv3.begin(),3,5);  
    for_each(iv3.begin(),iv3.end(),display<int>());  
    cout<<endl; //iv3:8 10 7 8 5 5 7 8 5 7 8 (0)（最后y一个残留元素）   
        
    //将容器中小于 5 替换为 2   
    replace_if(iv.begin(),iv.end(),bind2nd(less<int>(),5),2);  
    for_each(iv.begin(),iv.end(),display<int>());   
    cout<<endl; //iv:8 10 7 8 2 2 7 8 2 7 8   
  
    //将容器中小于 5 替换为 2   
    replace_copy_if(iv.begin(),iv.end(),iv3.begin(),bind2nd(equal_to<int>(),8),9);  
    for_each(iv3.begin(),iv3.end(),display<int>());   
    cout<<endl; //iv3:9 10 7 9 2 2 7 9 2 7 9 (0) (最后一个残留元素)   
      
    //逆向重排每一个元素 (倒置)   
    reverse(iv.begin(),iv.end());   
    for_each(iv.begin(),iv.end(),display<int>());  
    cout<<endl; //iv:8 7 2 8 7 2 2 8 7 10 8  
      
    //逆向重排每一个元素 (倒置)   
    reverse_copy(iv.begin(),iv.end(),iv3.begin());   
    for_each(iv3.begin(),iv3.end(),display<int>());  
    cout<<endl; //iv3:8 10 7 8 2 2 7 8 2 7 8 (0) (最后一个残留元素)    
     
    // 互换元素  [bigin,middle)  [middle,end)   
    rotate(iv.begin(),iv.begin()+4,iv.end());  
    for_each(iv.begin(),iv.end(),display<int>());  
    cout<<endl; //iv: [8 7 2 8] 7 2 2 8 7 10 8  -> [7 2 2 8 7 10 8] 8 7 2 8   
         
    // 互换元素  [bigin,middle)  [middle,end)   
    rotate_copy(iv.begin(),iv.begin()+5,iv.end(),iv3.begin());  
    for_each(iv3.begin(),iv3.end(),display<int>());  
    cout<<endl;//iv3:[10 8 8 7 2 8] [7 2 2 8 7] (0) (最后一个是残留元素)   
      
    //在iv中查找 子序列 2 8 第一次出现的位置的元素   
    int ia2[3]={2,8};  
    vector<int> iv4(ia2,ia2+2);     // iv4:{2,8}  
    cout<< *search(iv.begin(),iv.end(),iv4.begin(),iv4.end()) << endl; //2   
      
    //在iv中查找 2个8 出现的第一个位置的元素   
    cout<< *search_n(iv.begin(),iv.end(),2,8) << endl; //8   
      
    //在iv中查找 3个小于8 出现的第一个位置的元素   
    cout<< *search_n(iv.begin(),iv.end(),3,8,less<int>()) << endl; //7  
    
    //将两个区间内的元素互换，第二区间的元素个数不应小于第一区间的元素个数
    swap_ranges(iv4.begin(),iv4.end(),iv.begin());  
    cout<<"iv:";   
    for_each(iv.begin(),iv.end(),display<int>()); //iv:2 8 2 8 7 10 8 8 7 2 8   
    cout<<endl;  
    cout<<"iv3:";   
    for_each(iv4.begin(),iv4.end(),display<int>()); //iv4: 7 2   
    cout<<endl;  
        
    //全部减2   
    transform(iv.begin(),iv.end(),iv.begin(),bind2nd(minus<int>(),2));  
    for_each(iv.begin(),iv.end(),display<int>()); //0 6 0 6 5 8 6 6 5 0 6   
    cout<<endl;   
      
    //两个区间元素相加然后放到 iv上   
    //第二区间的元素个数不应小于第一区间的元素个数
    transform(iv.begin(),iv.end(),iv.begin(),iv.begin(),plus<int>());  
    for_each(iv.begin(),iv.end(),display<int>());  
    cout<<endl; //0 12 0 12 10 16 12 12 10 0 12 

    cout << "---------------------------------------------------------------------------" << endl;

    vector<int> iv5(ia,ia+sizeof(ia)/sizeof(int));  
    vector<int> iv6(ia+4,ia+8);  
    vector<int> iv7(15);  
    for_each(iv5.begin(),iv5.end(),display<int>());  
    cout<<endl; //0 1 2 3 4 5 6 6 6 7 8; 
    for_each(iv6.begin(),iv6.end(),display<int>());  
    cout<<endl; //4 5 6 6

    cout<< *max_element(iv5.begin(),iv5.end()) << endl;  // 8
    cout<< *min_element(iv5.begin(),iv5.end()) << endl;  // 0
  
    //判断iv6中元素是否都出现在 iv5 中   
    cout << includes(iv5.begin(),iv5.end(),iv6.begin(),iv6.end()) << endl; // 1 (true)   
       
    //iv5 和 iv6 合并到 iv7 中   
    //注意，两个序列都是sort range，结果也是sort range
    merge(iv5.begin(),iv5.end(),iv6.begin(),iv6.end(),iv7.begin());   
    for_each(iv7.begin(),iv7.end(),display<int>());  
    cout<<endl;             // iv7:0 1 2 3 4 4 5 5 6 6 6 6 6 7 8 
      
    //符合条件的 放到前面，不符合条件的放到后面   
    partition(iv7.begin(),iv7.end(),even());  
    for_each(iv7.begin(),iv7.end(),display<int>());  
    cout<<endl;         // iv7:0 8 2 6 4 4 6 6 6 6 5 5 3 7 1
      
    //去除连续并且重复的元素   
    //注意：获得的结果可能有残余数据
    unique(iv5.begin(),iv5.end());   
    for_each(iv5.begin(),iv5.end(),display<int>());  
    cout<<endl;   // iv5:0 1 2 3 4 5 6 7 8 (7 8)残余数据
      
    //去除连续并且重复的元素，将结果置于另一处
    //注意：获得的结果可能有残余数据
    unique_copy(iv5.begin(),iv5.end(),iv7.begin());   
    for_each(iv7.begin(),iv7.end(),display<int>());  
    cout<<endl;      // iv7:0 1 2 3 4 5 6 7 8 (7 8) (5 3 7 1)  残余数据

    return 0;   
}

