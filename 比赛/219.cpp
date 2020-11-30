#include "../header.h"

// T1
class Solution {
public:
    int maximumWealth(vector<vector<int>>& accounts) {
        int ans = -1;
        for(auto i : accounts)
        {
            int temp = 0;
            for(auto j : i) temp += j;
            ans = max(ans, temp);
        }
        return ans;
    }
};

// T2   
class Solution {
public:
    vector<int> mostCompetitive(vector<int>& nums, int k) {
        // 从倒数第k个位置向前找到最小的数字
        int n = nums.size();
        vector<int> ans;
        auto last = nums.begin();
        for(int i = k; i >= 1; )
        {
            auto min_it = min_element(last, nums.end() - i + 1);
            // cout << *min_it << '\n';
            if(nums.end() - min_it < k)
            {
                // 只能在last和min_it中选小的了，不能往后找
                min_it = min_element(last, min_it);
            }
            ans.push_back(*min_it), --i;
            last = min_it + 1;
        }
        return ans;
    }
};