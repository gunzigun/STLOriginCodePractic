#include <tree.h>
#include <iostream>
using namespace std;

int main()
{
    rb_tree<int, int, identity<int>, less<int> > itree;
    cout << itree.size() << endl;           // 0

    // 以下注释中所标示的函数名称，是我修改<stl_tree.h>,打印函数名而来
    itree.insert_unique(10);            //__rb_tree_rebalance
    itree.insert_unique(7);             //__rb_tree_rebalance
    itree.insert_unique(8);             //__rb_tree_rebalance
                                            //__rb_tree_rotate_left
                                            //__rb_tree_rotate_right
    itree.insert_unique(15);            //__rb_tree_rebalance
    itree.insert_unique(5);             //__rb_tree_rebalance
    itree.insert_unique(6);             //__rb_tree_rebalance
                                            //__rb_tree_rotate_left
                                            //__rb_tree_rotate_right
    itree.insert_unique(11);            //__rb_tree_rebalance
                                            //__rb_tree_rotate_right
                                            //__rb_tree_rotate_left
    itree.insert_unique(13);            //__rb_tree_rebalance
    itree.insert_unique(12);            //__rb_tree_rebalance
    
    cout << itree.size() << endl;       // 9
    rb_tree<int, int, identity<int>, less<int> >::iterator iter1 = itree.begin();
    rb_tree<int, int, identity<int>, less<int> >::iterator iter2 = itree.end();
    __rb_tree_base_iterator rbtite;

    for (; iter1 != iter2; ++iter1)
    {
        rbtite = __rb_tree_base_iterator(iter1);

        cout << *iter1 << "(" << rbtite.node->color << ") ";                  // 5 6 7 8 10 11 12 13 15
    }
    cout << endl;

}