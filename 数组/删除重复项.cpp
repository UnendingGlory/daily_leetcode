#include "header.h"

/**
 * sorted array
 * two pointers
 */
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        int fast = 1, slow = -1;
        while (fast < n) {
            if (nums[fast - 1] != nums[fast]) {
                nums[slow] = nums[fast];
                ++slow;
            }
            ++fast;
        }
        return slow;
    }
};