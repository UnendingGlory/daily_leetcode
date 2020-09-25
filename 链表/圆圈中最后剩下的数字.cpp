#include <bits/stdc++.h>
using namespace std;

// 经典的约瑟夫环问题
// 链表模拟，会超时
struct linkedNode
{
    int val;
    linkedNode* next;
    linkedNode(int v):val(v), next(nullptr){}
};

class Solution {
public:
    int lastRemaining(int n, int m) {
        linkedNode* L = new linkedNode(0);
        linkedNode* p = L, *q;
        for(int i = 1; i < n; ++i) // 插入，尾插法
        {
            q = new linkedNode(i);
            p->next = q;
            p = q;
        }
        p->next = L; // 循环链表
        p = L;
        while(n) // 不是只剩一个元素
        {
            int cnt = m % (n + 1); // 注意，模n要写成n + 1,要结合循环想清楚
            while((--cnt) > 0)
            {
                q = p;
                p = p->next;
            }
            q->next = p->next;
            //printf("\n%d\n", p->val);
            delete(p);
            --n;
            p = q->next; // 重新赋值给下一个
        }
        return p->val;
    }
};

// 数组模拟，数学解法，递归，o(n)
class Solution {
    int f(int n, int m) {
        if (n == 1)
            return 0;
        int x = f(n - 1, m);
        return (m + x) % n;
    }
public:
    int lastRemaining(int n, int m) {
        return f(n, m);
    }
};


int main()
{
    Solution s;
    cout << "ans " << s.lastRemaining(10, 17) << endl;
    return 0;
}