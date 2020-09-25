// 先统计连续交叉0，1的个数
#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;

class Solution 
{
public:
    int countBinarySubstrings(string s) 
    {
        vector<int> ans;
        int ptr = 0, n = s.size();
        while(ptr < n)
        {
            char c = s[ptr];
            int count = 0;
            while(ptr < n && s[ptr] == c)
            {
                ++count;
                ++ptr;
            }
            ans.push_back(count);
        }
        int res = 0;
        for(int i = 1; i < ans.size(); ++i)
        {
            res += min(ans[i], ans[i - 1]);
        }
        return res;
    }
};