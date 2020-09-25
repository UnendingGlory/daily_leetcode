#include<cstdio>

class Solution {
public:
    // 递归 + 逻辑运算符短路性质
    int sumNums(int n) {
        // 与运算符性质，如果n是0就不执行后面的递归语句
        n && (n += sumNums(n - 1));
        return n;
    }
};