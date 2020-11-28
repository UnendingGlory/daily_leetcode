#include "header.h"

// 分组 + 哈希表
// 由于只需要种类，所以可以先将A+B的和存在哈希表中
// 再对每一对C、D求和，如果-(Ci + Di)也在哈希表中
// 则答案加一
class Solution {
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
		// key: key, value: how many times
		unordered_map<int, int> ss;
		for(const auto &i : A)
			for(const auto &j : B)
				++ss[i + j];
		int ans = 0;
		for(const auto &i : C)
			for(const auto &j : D)
			{
				int k = i + j;
				if(ss.count(-k)) ans += ss[-k];
			}
		return ans;
    }
};
