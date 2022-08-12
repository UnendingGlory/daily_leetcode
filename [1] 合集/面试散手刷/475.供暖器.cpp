#include "header.h"

// 你的任务是设计一个有固定加热半径的供暖器向所有房屋供暖。
// 在加热器的加热半径范围内的每个房屋都可以获得供暖。
// 现在，给出位于一条水平线上的房屋 houses 和供暖器 heaters 的位置。
// 请你找出并返回可以覆盖所有房屋的最小加热半径。

// 输入: houses = [1,2,3], heaters = [2]
// 输出: 1
// 解释: 仅在位置2上有一个供暖器。如果我们将加热半径设为1，那么所有房屋就都能得到供暖。

// 输入: houses = [1,2,3,4], heaters = [1,4]
// 输出: 1
// 解释: 在位置1, 4上有两个供暖器。我们需要将加热半径设为1，这样所有房屋就都能得到供暖。

// Solution1: 排序 + 二分查找。
// 对于每一个房屋，我们都安排一个距离最近的供暖器并记录距离。
// 最终的取暖半径即所有距离的最大值，即可以供暖到所有房屋。
// 对 heaters进行排序后，对每一个房屋，二分查找最近的供暖器。
// 即对 house, 二分查找第一个 > house的位置，然后 -1即可。
// 得到该位置 j之后，比较 house和 j以及 j-1之间的距离，取较近的。
// 对于越界情况要特殊处理。
// 时间复杂度：O(nlogn + mlogn)，排序 + 每个下标二分。
// 空间复杂度：O(logn)，排序所用空间。
class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        sort(heaters.begin(), heaters.end());
        int ans = 0, j, distance;
        for (int i = 0; i < houses.size(); ++i) {
            j = binarySearch(heaters, houses[i]);
            if (j == -1) { // houses[i]比 heaters均大，取最后一个最近
                distance = houses[i] - heaters.back();
            }
            else if (j == 0) { // 有可能返回最后一个
                distance = heaters[j] - houses[i];
            } else {
                distance = min(heaters[j] - houses[i], houses[i] - heaters[j-1]);
            }
            ans = max(ans, distance);
        }
        return ans;
    }

    // 在 heaters中查找第一个 > target的位置
    // 如果找不到就返回 -1
    int binarySearch(vector<int>& heaters, int target) {
        int l = 0, mid, r = heaters.size() - 1, ans = -1;
        while (l <= r) {
            mid = l + ((r - l) >> 1);
            if (heaters[mid] > target) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return ans;
    }
};

// Solution2: 排序 + 双指针。
// 对 houses 和 heaters均进行排序。
// 问题转换为，对于 houses中的 每一个下标i。
// 需要找到 heaters中的 j，使得 |houses[i] - heaters[j]|最小。

// 初始 i = j = 0
// 对于初始位置 i，只要 heaters[j] 和当前房屋的距离大于等于 heaters[j+1] 和当前房屋的距离，
// 则将 j 加 1，直到 j=n−1 或者 heaters[j] 和当前房屋的距离小于 heaters[j+1] 和当前房屋的距离。

// 对于下一个位置 i，由于 houses[i] >= houses[i+1]，沿着之前的 j继续向前寻找即可。
// 时间复杂度：O(mlogm + nlogn)，空间复杂度：O(logm + logn)
class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        int m = houses.size(), n = heaters.size();
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());
        int i = 0, j = 0, ans = 0, distance;
        while (i < m) {
            while (j < n - 1 && 
                   abs(houses[i] - heaters[j]) >= abs(houses[i] - heaters[j + 1])) {
                ++j;
            }
            distance = abs(houses[i] - heaters[j]);
            ans = max(ans, distance);
            ++i;
        }
        return ans;
    }
};
