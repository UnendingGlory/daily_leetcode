#include <bits/stdc++.h>
using namespace std;

// 数组和为k的连续子数组个数
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int count = 0;
        // 枚举[0, start]内所有下标来判断是否满足条件，后缀和思想
        for (int start = 0; start < nums.size(); ++start) {
            int sum = 0;
            for (int end = start; end >= 0; --end) {
                sum += nums[end];
                if (sum == k) {
                    count++;
                }
            }
        }
        return count;
    }
};

int main()
{
    return 0;
}