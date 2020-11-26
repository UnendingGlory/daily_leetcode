// 由于要求要在线性时间复杂度内实现，所以不能采用传统o(nlogn)的排序算法
// 可以使用时间复杂度为O(dn)的基数排序
// 思路可以见radix_sort.cpp
#include <header.h>

class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int n = nums.size();
		if(!n) return 0;
		vector<vector<int>> bucket(10); // 10个桶
		// 获得最大元素，以此作为循环终止条件
		int maxNum = *max_element(nums.begin(), nums.end());
		int divisor = 1;
		while(divisor <= maxNum)
		{
		// 每一趟重置桶内元素，注意要每一个clear
		// 如果直接bucket.clear则要resize
			for(int i = 0; i < 10; ++i) bucket[i].clear();
			for(int i = 0; i < n; ++i)
			{
				size_t idx = (nums[i] / divisor) % 10;
				bucket[idx].emplace_back(nums[i]);
			}
			// o(n)
			nums.clear();
			for(auto j : bucket)
			{
				for(auto t : j)
				{
					nums.emplace_back(std::move(t));
				}
			}
			divisor *= 10;
		}
		int ans = 0;
		for(int i = 1; i < n; ++i)
			ans = max(ans, nums[i] - nums[i - 1]);
        return ans;
    }
};