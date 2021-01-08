#include "header.h"

// 先把前半段翻转，再把后半段翻转
// 再整体翻转
class Solution {
public:
    void rotate_inplace(vector<int>& nums, int l, int r) {
        for (int i = l, j = r; i < j; ++i, --j) {
            swap(nums[i], nums[j]);
        }
    }

    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k %= n; // 注意，这一步是关键，要考虑到k >= n的情况
        rotate_inplace(nums, 0, n - k - 1);
        rotate_inplace(nums, n - k, n - 1);
        rotate_inplace(nums, 0, n - 1);
    }
};