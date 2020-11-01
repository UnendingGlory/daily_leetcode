#include "../header.h"

/**
 *  @note Solution 1
 *  Dynamic Programming
 */
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
		size_t n = s.size();
		vector<bool> dp(n + 1);
		dp[0] = true;
		for(int i = 0; i < n; ++i)
		{
			if(dp[i] == false) continue;
			for(auto &word : wordDict)
			{
				// 对于每一个word如果和i开始的子串相等中则dp[j] = true
				if(word.size() + i <= s.size() && s.substr(i, word.size()) == word)
					dp[i + word.size()] = true;
			}
		}
		return dp[s.size()];
    }
};

/**
 *  @note Solution 2
 *  记忆化搜索
 */



