#include "header.h"
// 给你一个含 n 个整数的数组 nums ，其中 nums[i] 在区间 [1, n] 内。请你找出所有在 [1, n] 范围内但没有出现在 nums 中的数字，并以数组的形式返回结果。
// 要求时间复杂度为 O(n)，空间复杂度为 O(1)。

// Solution1: 索引排序。
// 由于 nums[i] 位于 [1, n]之间，若无重复数字，排序后，位置 i 应该放置元素 i+1。
// 索引排序：对于数组中每一个元素 nums[i]
// 1. 若 nums[i] == i + 1，则说明 i位置已经放好，++i, 跳过该元素。
// 2. 若 nums[i] != i + 1，说明 i位置没有放好指定元素，我们需要将 nums[i]放置到指定位置。
//    若 nums[i] == nums[nums[i]-1]，说明 nums[i]位置已经放好对应元素，++i, 跳过该元素。
//    若 nums[i] != nums[nums[i]-1] 则将 nums[i] 放置在位置 nums[i] - 1。
//    即 swap(nums[i], nums[nums[i]-1])
// 在索引排序后，再遍历数组，如果 nums[i] != i + 1，则将 i + 1 丢入结果数组。
// 时间复杂度：O(n)，空间复杂度为：O(1)
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int i = 0;
        while (i < nums.size()) {
            if (nums[i] == i + 1) {
                ++i;
                continue;
            }
            if(nums[i] != nums[nums[i] - 1]) {
                swap(nums[i], nums[nums[i] - 1]);
            } else {
                ++i;
            }
        }
        vector<int> ans;
        for (i = 0; i < nums.size(); ++i) {
            if (nums[i] != i + 1) {
                ans.emplace_back(i + 1);
            }
        }
        return ans;
    }
};


// Solution2: 数组原地哈希。
// nums[i] 位于 [1, n]之间。
// 对于每一个元素 nums[i]，我们将 nums[i] - 1位置的元素 nums[nums[i]-1] 加 n。
// 注意，这样操作后，遍历到某位置时，nums[i]可能已经是累加过的值。
// 因此需要采用 nums - 1 对 n取模操作返回 [原来的值 - 1]。
// 累加完后，在 [1, n] 中，除了没有出现的数字，对于其他数字 x。
// nums[x-1] 一定是大于 n的。
// 将小于等于 n的数字对应的下标丢入结果数组即可。
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int n = nums.size(), origin;
        for (int num: nums) {
            origin = (num - 1) % n; // 这样不会越界，保证在 [0, n-1] 内
            nums[origin] += n;
        }
        vector<int> ans;
        for (int i = 0; i < n; ++i) {
            if (nums[i] <= n) {
                ans.emplace_back(i + 1);
            }
        }
        return ans;
    }
};
