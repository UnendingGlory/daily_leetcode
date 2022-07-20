#include "../header.h"

// T1
// 能否将pieces链接成arr, 数字各不相同
class Solution {
public:
    bool canFormArray(vector<int>& arr, vector<vector<int>>& pieces) {
		size_t i = 0; // 在pieces中寻找arr[i]
		while(i < arr.size())
		{
			bool flag = false;
			for(auto &each : pieces)
			{
				if(each[0] == arr[i])
				{
					flag = true;
					for(int j = 1; j < each.size(); ++j)
					{
						if(each[j] != arr[++i]) return false;
					}
					++i;
					break;
				}
			}
			if(!flag) return false;
		}
		return true;
    }
};

// T2
// 返回长度为n，按字典序排序的字符串数量, dp
class Solution {
public:
    int countVowelStrings(int n) {
		vector<vector<int>> dp(5, vector<int>(n));
		for(int j = 0; j < 5; ++j) dp[j][0] = 1;
		for(int j = 1; j < n; ++j)
		{
			for(int i = 0; i < 5; ++i)
			{
				for(int k = i; k < 5; ++k)
					dp[i][j] += dp[k][j - 1];
			}
		}
		int ans = 0;
		for(int j = 0; j < 5; ++j)
			ans += dp[j][n - 1];
		return ans;
    }
};

// unsolved
// T3
// 给定砖块和梯子能到达的最远处
// 砖块必须满足高度，梯子可以任意跨越
// 有砖块则用砖块，没砖块则用梯子? no
// 矮的尽量用砖块，高的用梯子
class Solution {
public:
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
		int n = heights.size();
		vector<pair<size_t, int>> diff;
		for(int i = 1; i < n; ++i)
		{
			// 保存差值
			if(heights[i] > heights[i - 1])
				diff.push_back({i, heights[i] - heights[i - 1]}); // initializer_list constructor
		}

    }
};


// T4
// H：向右, V：向下，两个方向
class Solution {
public:
    string kthSmallestPath(vector<int>& destination, int k) {
		int numH = destination[1], numV = destination[0];
		// 先生成全排列排序
		string str;
		for(int i = 0; i < numH; ++i) str.push_back('H');
		for(int i = 0; i < numV; ++i) str.push_back('V');
		vector<string> ans;
		int i = 1;
		do
		{
			ans.push_back(str);
			if(i++ == k) return str;
		} while (next_permutation(str.begin(), str.end()));
		return "";
    }
};