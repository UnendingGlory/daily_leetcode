#include "header.h"

// 约瑟夫环问题
// 0...n-1中每隔m个数删除一个数字

// Solution1: 循环链表，使用内置STL。
// std::list双向单链表，只要在遍历到尾部时，
// 将迭代器移到头部，即可变成循环链表。

// 注意处理时要重置迭代器
class Solution {
public:
    int lastRemaining(int n, int m) {
        std::list<int> lst;
        for (int i = 0; i < n; ++i) {
            lst.push_back(i);
        }
        list<int>::iterator it = lst.begin(), next;
        while (lst.size() > 1) {
            for (int i = 0; i < m - 1; ++i) { // 如果是随机迭代器可以直接计算位置
                ++it;
                if (it == lst.end()) {
                    it = lst.begin();
                }
            }
            next = ++it;
            --it;
            lst.erase(it); // 删除it位置对应元素
            it = next;
        }
        return lst.front();
    }
};


// Solution2: 自己实现一个循环链表，尾插法链接到头部即可
// 删除直接在算法中操作，时间复杂度O(mn)，空间复杂度O(n)
struct LNode {
public:
    int val;
    struct LNode *next;
    LNode(int x):val(x), next(nullptr) {}
};

class Solution {
public:
    int lastRemaining(int n, int m) {
        LNode *head = new LNode(0), *p = head, *q;
        for (int i = 1; i < n; ++i) {
            q = new LNode(i);
            p->next = q;
            p = q;
        }
        p->next = head; // 循环链表
        // 当前q是最后一个结点，q接下来是要删除的结点的前一个结点
        p = head;
        while (p->next != p) {
            for (int i = 0; i < m - 1; ++i) {
                q = p; // 记录上一个结点
                p = p->next;
            }
            // 删除当前p结点
            q->next = p->next;
            delete p;
            p = q->next; // 指向下一个节点
        }
        return p->val;
    }
};


// 以上两种方法易写，但是在n和m过大时会超时
// 接下来通过数学分析的方法，使用动态规划解决
// 输入n, m，记该[n, m]问题的解为f(n)
// 则[n, m]：环为0, 1, 2, .. n - 1，解为f(n)
// [n-1, m]：环为0, 1, 2, .. n - 2,解为f(n-1)

// 对于[n, m]问题，由于m可能大于n，因此首轮删除的数为(m - 1) % n 
// 从下一个数t = m % n开始，可得环记为 Ring
// t, t + 1, t + 2 ... 0, 1, ... t - 2

// 观察 Ring 环和[n-1, m]问题，发现位置是一一对应的
// [n-1, m]问题中某数x，对应 Ring 中元素为(x + t) % n

// 又因为[n, m]问题的解是由 Ring 的解得来的
// 所以如果知道了[n-1, m]问题的解为f(n-1)，根据对应关系
// Ring的解为 (f(n - 1) + t) % n，即[n, m]问题的解f(n)
// 所以f(n) = (f(n - 1) + t) % n = (f(n - 1 + m % n)) % n
//         = (f(n - 1) + m) % n

// 所以递推公式为：
// f(1) = 0, i = 1
// f(i) = (f(i - 1) + m) % i, i >= 2
class Solution {
public:
    int lastRemaining(int n, int m) {
        int ans = 0; // f(1) = 0
        for (int i = 2; i <= n; ++i) {
            ans = (ans + m) % i;
        }
        return ans;
    }
};
