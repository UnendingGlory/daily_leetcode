#include "header.h"


// 给定一个数组 A[0,1,…,n-1]，请构建一个数组 B[0,1,…,n-1]，
// 其中 B[i] 的值是数组 A 中除了下标 i 以外的元素的积, 
// 即 B[i]=A[0]×A[1]×…×A[i-1]×A[i+1]×…×A[n-1]。不能使用除法。

// 直观思路：将所有元素相乘，再除以当前元素，但是对于值为0的元素会失效
// 且题目规定了不能使用除法

// Solution1：左右乘积数组
// B[0] : 1 * A[1] * A[2] ... A[n]
// B[1] : A[0] * 1 * A[2] * ... A[n]
// B[i] = A[0] * A[1] * ... A[i-1] * 1 * A[i+1] * A[n - 1]

// 所以只需要维护两个乘积数组，一个从前往后，一个从后往前即可
// 时间复杂度：O(n)，空间复杂度：O(n)
class Solution {
public:
    vector<int> constructArr(vector<int>& a) {
        int n = a.size();
        if (n == 0) return {};
        vector<int> pre(n), post(n);
        pre[0] = post[n-1] = 1;
        for (int i = 1, j = n - 2; i < n && j >= 0; ++i, --j) {
            pre[i] = pre[i - 1] * a[i - 1];
            post[j] = post[j + 1] * a[j + 1];
        }
        vector<int> ans;
        for (int i = 0; i < n; ++i) { // 想明白下标关系
            ans.emplace_back(pre[i] * post[i]);
        }
        return ans;
    }
};

// 空间复杂度优化：O(1)
// 结果数组用来存储pre遍历的结果，一个变量tmp用来存储post遍历的结果
class Solution {
public:
    vector<int> constructArr(vector<int>& a) {
        int n = a.size();
        if (n == 0) return {};
        vector<int> ans(n);
        ans[0] = 1;
        for (int i = 1; i < n; ++i) {
            ans[i] = ans[i - 1] * a[i - 1];
        }
        int tmp = 1;
        for (int i = n - 2; i >= 0; --i) {
            tmp *= a[i + 1];
            ans[i] = ans[i] * tmp;
        }
        return ans;
    }
};