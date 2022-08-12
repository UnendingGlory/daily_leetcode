#include <bits/stdc++.h>
using namespace std;

// T1
class Solution {
public:
    int minStartValue(vector<int>& nums) {
        int n = nums.size();
		vector<int> sum(n);
		sum[0] = nums[0];
		for(int i = 1; i < n; ++i)
			sum[i] = sum[i - 1] + nums[i];
		auto x = min_element(sum.begin(), sum.end());
		if(*x <= 0) return abs(*x) + 1;
		else return 1;
    }
};

// T2
class Solution {
	vector<int> a;
	int ans;
public:

	void dfs(vector<int> &nums, int remain)
    {
		if(remain == 0) return;
		++ans;
		auto id = upper_bound(nums.begin(), nums.end(), remain);
		if(id == nums.begin()) dfs(nums, 0);
		else dfs(nums, remain - *(--id)); // 访问迭代器指向元素加指针即可
	}

    int findMinFibonacciNumbers(int k) {
        a.push_back(1);
		a.push_back(1);
		int i = 2;
		ans = 0;
		while(i <= k)
		{
			a.push_back(i);
			i = a[a.size() - 1] + a[a.size() - 2];
		}
		dfs(a, k);
		return ans;
    }
};

// T3
class Solution {
	vector<string> ans;
	int n;
	string temp;
public:
	void generate(int index)
	{
		if(index == 0)
		{
			temp.push_back('a');
			generate(index + 1);
			temp.pop_back();
			temp.push_back('b');
			generate(index + 1);
			temp.pop_back();
			temp.push_back('c');
			generate(index + 1);
			temp.pop_back();
			return;
		}
		if(index == n)
		{
			ans.push_back(temp);
			return;
		}
		if(temp[index - 1] == 'a')
		{
			temp.push_back('b');
			generate(index + 1);
			temp.pop_back();
			temp.push_back('c');
			generate(index + 1);
			temp.pop_back();
		}
		else if(temp[index - 1] == 'b')
		{
			temp.push_back('a');
			generate(index + 1);
			temp.pop_back();
			temp.push_back('c');
			generate(index + 1);
			temp.pop_back();
		}
		else if(temp[index - 1] == 'c')
		{
			temp.push_back('a');
			generate(index + 1);
			temp.pop_back();
			temp.push_back('b');
			generate(index + 1);
			temp.pop_back();
		}
	}
	
    string getHappyString(int N, int k) {
		n = N;
		generate(0);
		sort(ans.begin(), ans.end());
		if(k - 1 >= ans.size()) return "";
		else return ans[k - 1];
    }
};

// T4