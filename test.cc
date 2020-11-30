#include "header.h"

class A
{
public:
    virtual void display() = 0;
};

int main()
{
    // for_each(vec.begin(), vec.end(), [](int &x){
    //     x = 1;
    // });

    // 单向链表的iterator是forwardIterator
    // 而reverse函数至少要BidirectionalIterator
    // forward_list<int> ls{1, 2, 3, 4};
    // std::reverse(ls.begin(), ls.end());
    // for(auto i : ls) cout << i;

    // 标准规定空类大小是1字节
    // cout << sizeof(A);

    // unique操作并不会擦除，而只是将重复的调整到尾端
    // 且unique只对重复元素有效，所以需要去重
    // 一般采用sort + unique + erase
    vector<int> a{1, 2, 3, 4, 5};
    for(auto i : a) i = 1;
    for(auto &i : a) cout << i;
    cout << '\n';
    for(auto &i : a) i = 1;
    for(auto &i : a) cout << i;
    // cout << (-5 << 1) << '\n';
    // cout << *it << ' ' << *(++it);
    return 0;
}