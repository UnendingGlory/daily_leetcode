#include "header.h"

// 给定一个整数数组 temperatures，表示每天的温度，返回一个数组 answer，
// 其中 answer[i] 是指对于第 i 天，下一个更高温度出现在几天后。
// 如果气温在这之后都不会升高，请在该位置用 0 来代替。
// 输入：temperatures = [73, 74, 75, 71, 69, 72, 76, 73]。
// 输出：[1, 1, 4, 2, 1, 1, 0, 0]。

// 经典单调栈问题。
// 判别是否需要使用单调栈，如果需要找到左边或者右边第一个比当前位置的数大或者小，则可以考虑使用单调栈。
// 该题目其实就是求某个元素右边第一个比当前位置的数更大的元素。

// 维护一个单调栈，栈中存储下标。
// 从左往右，维护一个栈顶到栈底单调递增的栈。
// 在从栈中弹出元素 num的时候，则 num右边第一个比其大的元素更新为当前元素下标即可。
// 时间复杂度：O(n)，空间复杂度：O(n)。
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        stack<int> s; // 维护下标
        vector<int> ans(n);
        for (int i = 0; i < n; ++i) {
            while (!s.empty() && temperatures[s.top()] < temperatures[i]) {
                int index = s.top();
                ans[index] = i - index;
                s.pop();
            }
            s.push(i);
        }
        return ans;
    }
};
