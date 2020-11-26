#include "../header.h"

// 桶排序，迭代遍历
class Solution {
public:
    string sortString(string s) {
        vector<int> vec(26, 0);
		for(auto i : s) ++vec[i - 'a'];
		string ans;
		while(ans.size() < s.size())
		{
			for(int i = 0; i < 26; ++i)
			{
				if(vec[i] > 0)
					ans.push_back('a' + i), --vec[i];
			}
			for(int i = 25; i >= 0; --i)
			{
				if(vec[i] > 0)
					ans.push_back('a' + i), --vec[i];
			}
		}
		return ans;
    }
};