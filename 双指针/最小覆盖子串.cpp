#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    unordered_map<char, int> m, temp;
    // slide window
    bool check()
    {
        for(auto i : m)
        {
            // 注意，相同的不算重复（题意不明）
            if(temp[i.first] < i.second) return false;
        }
        return true;
    }

    string minWindow(string s, string t) {
        int left = 0, right = 0;
        int n = s.size(), start = 0, end = 0;
        int ans = INT_MAX;
        for(auto i : t) ++m[i];
        ++temp[s[0]];
        while(right < n)
        {
            // if not contain, ++right
            if(!check())
            {
                ++right;
                ++temp[s[right]];
            }
            // if contain, ++left
            else
            {
                if(right - left + 1 < ans)
                {
                    start = left, end = right;
                    ans = right - left + 1;
                }
                //printf("%d %d\n", left, right);
                --temp[s[left]];
                ++left;
            }
        }
        return ans == INT_MAX? string() : s.substr(start, ans);
    }
};