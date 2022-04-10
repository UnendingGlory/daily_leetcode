#include "header.h"


// Solution1: 披着老虎外衣的dp题。
// dp前缀最值 + dp后缀最值问题。
// 对于某个位置i，其能接到的最多的雨水为 min(preMax[i], postMax[i]) - num[i]。
// 最后将ans相加即可。
// 时间复杂度：O(n)，空间复杂度：O(n)
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        vector<int> preMax(n), postMax(n);
        preMax[0] = height[0];
        postMax[n - 1] = height[n - 1]; // 要赋值为自己，这样才能保证结果正确
        for (int i = 1; i < n; ++i) {
            preMax[i] = max(preMax[i - 1], height[i]);
        }
        for (int i = n - 2; i >= 0; --i) {
            postMax[i] = max(postMax[i + 1], height[i]);
        }

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans += min(preMax[i], postMax[i]) - height[i];
        }
        return ans;
    }
};

// Solution2: 双指针
// 用双指针优化掉Soltuion1中的空间，空间复杂度降为O(1)。
// 由于是取第i个位置前缀最值和后缀最值中较小的那个，
// 所以可以定义两个指针left和right，两个变量leftMax和rightMax。
// leftMax和rightMax由left和right位置所在的元素维护。
// 如果leftMax >= rightMax, 那么leftMax >= rightMax，
//                      ans += rightMax - height[right], --right
// 如果如果leftMax < rightMax, 那么leftMax < rightMax，
//                      ans += leftMax - height[left], ++left
class Solution {
public:
    int trap(vector<int>& height) {
        int left = 0, right = height.size() - 1;
        int leftMax = height[left], rightMax = height[right];
        int ans = 0;
        while (left < right) { // left和right相等时终止
            leftMax = max(leftMax, height[left]);
            rightMax = max(rightMax, height[right]);
            if (leftMax >= rightMax) {  // 相当于左右挡板高度
                ans += (rightMax - height[right]);
                --right;
            } else {
                ans += (leftMax - height[left]);
                ++left;
            }
        }
        return ans;
    }
};

// Solution3：单调栈
// 维护一个单调栈，单调栈存储的是下标，满足从栈顶到栈底的下标对应的数组 height 中的元素递增。
// 思想：相邻的三个元素height[left] height[top] height[i]
// 若top < left，且top < height[i]，则是一个接雨水的区域
// 因此维护一个单调地递增栈，从左到右处理数据
// 如果栈内元素不少于两个且 height[top] < height[i]，则有一个接雨水的区域
// 宽度是 i - left - 1，高度是min(height[i], height[left]) - height[top]
class Solution {
public:
    int trap(vector<int>& height) {
        int ans = 0, i = 0;
        stack<int> s;
        while (i < height.size()) {
            while (!s.empty() && height[i] > height[s.top()]) {
                // 得到一个接雨水的区域
                int top = s.top();
                s.pop();
                if (s.empty()) {  // 判空
                    break;
                }
                // 现在栈顶的是left
                int w = i - s.top() - 1;
                int h = min(height[s.top()], height[i]) - height[top];
                ans += w * h; 
            }
            // 记得i入栈
            s.push(i);
            ++i;
        }
        return ans;
    }
};
