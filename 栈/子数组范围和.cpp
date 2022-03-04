#include <header.h>

// 方法一：遍历
class Solution {
public:
    long long subArrayRanges(vector<int>& nums) {
        int n = nums.size(), minValue, maxValue;
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            minValue = maxValue = nums[i];
            for (int j = i; j < n; ++j) {
                minValue = min(minValue, nums[j]);
                maxValue = max(maxValue, nums[j]);
                ans += (maxValue - minValue);
            }
        }
        return ans;
    }
};

// 方法二：单调栈
// 范围和 sum 等于所有子数组的最大值之和 sumMax 减去所有子数组的最小值之和 sumMin
// 假设 nums[i]左侧最近的比它小的数为 nums[j]，右侧最近的比它小的数为 nums[k]
// !! 那么所有以 nums[i] 为最小值的子数组数目为 (k−i)×(i−j)
// 我们可以使用单调递增栈分别预处理数组minLeft和minRight
// 其中minLeft[i]表示nums[i]左侧最近的比它小的数的下标，
// minRight[i] 表示 nums[i] 右侧最近的比它小的数的下标

// 以求解 minLeft 为例，我们从左到右遍历整个数组 nums。
// 处理到 nums[i] 时，我们执行出栈操作直到栈为空或者 nums 中以栈顶元素为下标的数逻辑上小于 nums[i]。
// 如果栈为空，那么 minLeft[i]=−1，否则 minLeft[i] 等于栈顶元素，然后将下标 i 入栈。

// 则所有子数组的最小值之和为 (minRight[i] - i) * (i - minLeft[i]) * nums[i], i从0-n
// [4,-2,-3,4,1]
class Solution {
public:
    long long subArrayRanges(vector<int>& nums) {
        int n = nums.size();
        vector<int> minLeft(n), minRight(n), maxLeft(n), maxRight(n); // 记录下标
        stack <int> minStack, maxStack;

        // 计算左侧的
        for (int i = 0; i < n; ++i) {
            while (!minStack.empty() && nums[minStack.top()] > nums[i]) {
                minStack.pop();
            }

            minLeft[i] = minStack.empty() ? -1 : minStack.top();
            minStack.push(i);

            while (!maxStack.empty() && nums[maxStack.top()] <= nums[i]) {
                maxStack.pop();
            }

            maxLeft[i] = maxStack.empty() ? -1 : maxStack.top();
            maxStack.push(i);
        }

        // 计算右侧的
        minStack = stack<int>(), maxStack = stack<int>();
        for (int i = n - 1; i >= 0; --i) {
            while (!minStack.empty() && nums[minStack.top()] >= nums[i]) {
                minStack.pop();
            }

            minRight[i] = minStack.empty() ? n : minStack.top();
            minStack.push(i);

            while (!maxStack.empty() && nums[maxStack.top()] < nums[i]) {
                maxStack.pop();
            }

            maxRight[i] = maxStack.empty() ? n : maxStack.top();
            maxStack.push(i);
        }

        long long maxSum = 0, minSum = 0;
        for (int i = 0; i < n; ++i) {
            minSum += static_cast<long long>(minRight[i] - i) * (i - minLeft[i]) * nums[i];
            maxSum += static_cast<long long>(maxRight[i] - i) * (i - maxLeft[i]) * nums[i];
        }
        return maxSum - minSum;
    }
};
