// 可以先用一个例子模拟过程
// 为何会无限步？
// 应该想到是陷入了循环
// 如116
#include <bits/stdc++.h>
using namespace std;

// 如何判断是否会陷入循环？可以用快慢指针法
// 一个指针一次走两步，一个指针一次走一步
// 如果有循环，两个指针最终会在同一个位置相遇
// 如果没有循环，则快指针会先到达数字1
class Solution {
public:
    // 当前数字getnext
    int getnext(int x)
    {
        int sum = 0;
        while(x != 0)
        {
            int rem = x % 10;
            sum += rem * rem;
            x = x / 10;
        }
        return sum;
    }

    bool isHappy(int n) {
        int fast = n, slow = n; // 快慢指针
        while(fast != 1)
        {
            fast = getnext(getnext(fast));
            slow = getnext(slow);
            if(slow != 1 && fast == slow) return false;
        }
        return true;
    }
};

// 实际上，只会进入一个数字循环