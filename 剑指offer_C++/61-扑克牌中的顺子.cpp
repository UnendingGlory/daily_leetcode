#include <header.h>


// 抽到5张牌是顺子的充分条件（同时满足这两个条件）
// 比如 12345，00345
// 除大小王（0）之外，其他牌均无重复
// 最大牌 max - 最小牌 min < 5 （这一点很难想到）

// Solution1: 使用set判断是否有重复牌
// 使用两个变量max和min记录最大和最小牌
// 时间复杂度：O(5)
class Solution {
public:
    bool isStraight(vector<int>& nums) {
        std::unordered_set<int> ss;
        int imax = INT_MIN, imin = INT_MAX;
        for (int &i: nums) {
            if (i == 0) continue; // 跳过大小王
            if (ss.find(i) != ss.end()) return false;

            imax = max(i, imax);
            imin = min(i, imin);
            ss.insert(i);
        }
        return imax - imin < 5;
    }
};


// Solution2：排序 + 判重
// 排序后，判断nums[i] ≠ nums[i+1]
// nums[4]是最大值，找到最小值即可
// 时间复杂度：O(5log5)
class Solution {
public:
    bool isStraight(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        int min_idx = 0;
        for (int i = 0; i < 4; ++i) {
            if (nums[i] == 0) {
                ++min_idx;
                continue;
            }
            if (nums[i] == nums[i + 1]) {
                return false;
            }
        }
        return nums[4] - nums[min_idx] < 5;
    }
};
