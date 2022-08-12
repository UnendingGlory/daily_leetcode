#include "header.h"

// 给定一个含有 n 个正整数的数组和一个正整数 target 。
// 找出该数组中满足其和 ≥ target 的长度最小的 连续子数组 [numsl, numsl+1, ..., numsr-1, numsr] ，并返回其长度。
// 如果不存在符合条件的子数组，返回 0 。


// Solution1：暴力双指针
// 对于每个 i，遍历[i+1, n-1] 范围内的j
// 如果和大于等于 target，更新答案，并遍历下一个 i。
// 时间复杂度：O(n^2)，空间复杂度：O(1)。
// 会超时
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int ans = INT_MAX, n = nums.size();
        for (int i = 0; i < n; ++i) {
            int sum = 0;
            for (int j = i; j < n; ++j) {
                sum += nums[j];
                if (sum >= target) {
                    ans = min(ans, j - i + 1);
                    break;
                }
            }
        }
        return ans == INT_MAX ? 0 : ans;
    }
};

// Solution2: 前缀和 + 二分查找优化。
// 方法 1中两层循环，第二层循环可采用前缀和 + 二分优化为 O(logn)。
// 由于数组元素皆为正数，所以前缀和数组递增，可以使用二分查找。
// sum[i] 为 nums[0]...nums[i] 之和。
// sum[0] = nums[0], sum[1] = nums[0] + nums[1] ...
// 遍历时，对于每一个i，二分查找 [i, n-1]范围内的 j，
// sum[j] - sum[i-1]即为 [i, j]范围内的 sum和，
// 即二分查找第一个满足条件 sum[j] >= target + sum[i-1] 的 j的位置。
// 然后再更新答案。
// 时间复杂度：O(nlogn)，空间复杂度：O(n)
class Solution {
public:
    int binarySearch(vector<int> &sum, int l, int r, int target) {
        while (l < r) {
            int mid = l + ((r - l) >> 1);
            if (sum[mid] >= target) { // 这里是 >=
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        // l == r
        return sum[l] >= target ? l : -1;
    }

    int minSubArrayLen(int target, vector<int>& nums) {
        int ans = INT_MAX, n = nums.size();
        vector<int> sum(n);
        sum[0] = nums[0];
        for (int i = 1; i < n; ++i) {
            sum[i] = sum[i - 1] + nums[i];
        }
        int new_target;
        for (int i = 0; i < n; ++i) {
            if (i == 0) {
                new_target = target;
            } else {
                new_target = target + sum[i - 1];
            }
            int j = binarySearch(sum, i, n - 1, new_target);
            if (j != -1) {
                ans = min(ans, j - i + 1);
            }
        }
        return ans == INT_MAX ? 0 : ans;
    }
};

// Solution3：滑动窗口 [left, right]
// 如果窗口内的值之和 < target，那么 ++right
// 如果窗口内的值之和 >= target，那么更新 ans，++left
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int l = 0, r = 0, sum = 0, ans = INT_MAX;
        while (r < n) {
            sum += nums[r];
            while (sum >= target) {
                ans = min(ans, r - l + 1);
                sum -= nums[l];
                ++l;
            }
            ++r;
        }
        return ans == INT_MAX ? 0 : ans;
    }
};
