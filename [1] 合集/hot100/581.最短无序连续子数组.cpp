#include "header.h"

// 给你一个整数数组 nums ，你需要找出一个 最短连续子数组 ，如果对这个子数组进行升序排序，那么整个数组都会变为升序排序。
// 输出该数组的长度。(注意，该数组需要是连续的。)
// 输入：nums = [2,6,4,8,10,9,15]。输出：5。
// 解释：对 [6, 4, 8, 10, 9] 升序排序，整个数组均会升序。

// Solution1: 将整个数组分成三段，左段和右段均有序，中段无序。
// 如果原数组已经有序，直接返回 0。
// 只需要对原数组进行升序排序，排序后，双指针找到第一个和最后一个不同的元素的位置即可。
// 时间复杂度：O(nlogn)，空间复杂度：O(n)。
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        if(is_sorted(nums.begin(), nums.end())) { // is_sorted判断是否有序。
            return 0;
        }
        vector<int> sorted_nums(nums);
        sort(sorted_nums.begin(), sorted_nums.end());
        int left = 0, right = nums.size() - 1;
        while (nums[left] == sorted_nums[left]) { // 原数组不完全有序，则不会越界。
            ++left; 
        }
        while (nums[right] == sorted_nums[right]) {
            --right;
        }
        return right - left + 1;
    }
};

// Solution2: 分成三端后，保证中段的最小值 mmin比 [左段的右端点] 大，最大值 mmax比 [右段的左端点] 小即可。
// 我们的目标即找到中段的左右边界 left 和 right。

// 从左到右维护一个最大值 mmax，进入右段之前，遍历到的元素 nums[i] 均小于 mmax。
// 从右到左维护一个最小值 mmin，进入左段之前，遍历到的元素 nums[i] 均大于 mmin。
// 以 [2, 6, 4, 8, 10, 9, 15] 为例，无序数组 [6, 4, 8, 10, 9]，mmax = 10， mmin = 4。
// [2] [6, 4, 8, 10, 9] 中的元素均小于 mmax = 10。
// [6, 4, 8, 10, 9] [15] 中的元素均大于 mmin = 4。
// 时间复杂度：O(n)，空间复杂度：O(1)。
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int n = nums.size();
        int mmax = nums[0], mmin = nums[n - 1];
        // right初始为 -1，如果数组本身就有序，返回的就是 -1 + 1 = 0，也是正确的。
        int left = 0, right = -1;
        for (int i = 0; i < n; ++i) {
            if (nums[i] < mmax) {
                right = i; // 更新中段右边界。
            } else {
                mmax = nums[i];
            }

            if (nums[n - i - 1] > mmin) {
                left = n - i - 1;
            } else {
                mmin = nums[n - i - 1];
            }
        }
        return right - left + 1;
    }
};
