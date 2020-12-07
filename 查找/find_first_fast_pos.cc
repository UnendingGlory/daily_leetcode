#include "header.h"

// 显然应该二分，在[l...r]中二分
// 即查找>=x的第一个位置和>x的第一个位置
// 即对应lower_bound和upper_bound的实现
class Solution {
public:

    int binary_search(vector<int> &nums, int target, bool lower)
    {
        // 在这里ret要初始化，如果只有一个单词的话就直接返回1
        int l = 0, r = nums.size() - 1, ret = nums.size();
        while(l <= r)
        {
            int mid = ((r - l) >> 1) + l;
            // 对应lower和upper
            if(nums[mid] > target || (lower && nums[mid] >= target))
            {
                r = mid - 1;
                ret = mid;
            }
            else l = mid + 1;
        }
        return ret;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        int n = nums.size() - 1;
        int fir = binary_search(nums, target, true);
        int sec = binary_search(nums, target, false) - 1;
        if(fir <= sec && sec <= n && nums[fir] == target && nums[sec] == target)
            return {fir, sec};
        return {-1, -1};
    }
};