#include "header.h"


// 0~n-1中缺失的数字
// Solution1: 直接遍历
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size() + 1;
        for (int i = 0; i < n; ++i) {
            if (nums[i] != i) {
                return i;
            }
        }
        return 0;
    }
};


// Solution2: 排序数组，采用二分法
// 若缺失的那个数下标为i，那么i之前的数nums[i] = i，i之后的数nums[i] ≠ i
// 数组按照以下规则划分为两部分：
// 左子数组：nums[i] = i
// 右子数组：nums[i] ≠ i
// 答案即右子数组的第一个数
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int l = 0, r = nums.size() - 1, mid;
        while (l <= r) {
            mid = l + ((r - l) >> 1);
            if (nums[mid] == mid) { // 结果在右边区间 
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return l;
    }
};
