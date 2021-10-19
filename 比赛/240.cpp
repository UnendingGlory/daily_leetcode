#include "header.h"

// T1, birthdate [1950, 2050]
class Solution {
public:
    int maximumPopulation(vector<vector<int>>& logs) {
        vector<int> cnt(101, 0); // 做了一个offset
        for (int i = 0; i < logs.size(); ++i) {
            int birth = logs[i][0], death = logs[i][1];
            for (int j = birth; j <= death - 1; ++j) {
                ++cnt[j - 1950];
            }
        }
        // 找到最大的
        return max_element(cnt.begin(), cnt.end()) - cnt.begin() + 1950;
    }
};

// T2, 下标对中的最大距离
// max(j - i) s.t: nums1[i] <= nums2[j] && i <=j
// nums1 = [55,30,5,4,2], nums2 = [100,20,10,10,5]
// ans: 2
// nums1 和 nums2 都是 非递增 数组

// 10^5, 10^5
// 纯双循环会超时，应该利用非递增数组的性质
// 由于两个非递增数组的性质，因此第二个数组的指针不需要回溯
class Solution {
public:
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {
        int ans = 0, m = nums1.size(), n = nums2.size();
        int j = -1;
        for (int i = 0; i < m; ++i) {
            while (j + 1 < n && nums1[i] <= nums2[j + 1]) {
                j++;
            }
            ans = max(ans, j - i);
        }
        return ans;
    }
};

// 