#include <bits/stdc++.h>
using namespace std;

// T1
class Solution {
public:
    vector<int> minSubsequence(vector<int>& nums) {
		vector<int> ans, sum(nums.size());
		sort(nums.begin(), nums.end()); // 从大到小排序
		sum[0] = nums[0]; // sum保存和
		for(int i = 1; i < nums.size(); ++i)
		{
			sum[i] = sum[i - 1] + nums[i];
		}
		int rev_sum = 0; // 反向遍历和
		for(int i = nums.size() - 1; i >= 0; --i) // 反向遍历
		{	
			rev_sum += nums[i];
			ans.push_back(nums[i]);
			if(i >= 1 && rev_sum > sum[i - 1])
				break;
		}
		return ans;
    }
};

// T2
class Solution {
public:
    int numSteps(string s) {
		int n = 0;
		while(s != "1")
		{
			int c = s.size();
			if(s[c - 1] == '0') // 偶数
				s.pop_back();
			else // 奇数
			{
				auto it = s.rfind('0');
				if(it == string::npos) // 找不到则1后接s.size个0
				{	
					s.clear();
					s.push_back('1');
					for(int i = 1; i <= c; ++i) s.push_back('0');
				}
				else
					for(int i = it; i <= c - 1; ++i)
					{
						if(s[i] == '0') s[i] = '1';
						else s[i] = '0';
					}
			}
			++n;
		}
		return n;
    }
};

// T3

// T4