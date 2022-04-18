#include "header.h"


// Solution1：哈希表, 时间复杂度O(N)，空间复杂度O(N)
class Solution {
public:
    int majorityElement(vector<int>& nums) {
      int cnt = (nums.size() + 1) / 2;
      unordered_map<int, int> um;
      for (auto &num: nums) {
        ++um[num];
        if (um[num] >= cnt) {
          return num;
        }
      }
      return 0;
    }
};


// Solution2：排序后取中位数，即众数
class Solution {

    void quick_sort(vector<int> &nums, int l, int r) {
      if (l >= r) return;
      int x = l, y = r, pivot = nums[l];
      while (x < y) {
        while (x < y && nums[y] >= pivot) --y;
        std::swap(nums[x], nums[y]);
        while (x < y && nums[x] <= pivot) ++x;
        std::swap(nums[x], nums[y]);
      }

      quick_sort(nums, l, x - 1);
      quick_sort(nums, x + 1, r);
    }

public:
    int majorityElement(vector<int>& nums) {
      quick_sort(nums, 0, nums.size() - 1);
      return nums[nums.size() / 2];
    }
};
