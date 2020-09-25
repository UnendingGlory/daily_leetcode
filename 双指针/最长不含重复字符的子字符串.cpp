#include <bits/stdc++.h>
using namespace std;

/** 最长不含重复字符的子字符串
 *  滑动窗口，用一个set记录，right++，若不重复，则right继续++
 *  若重复，则left++，中间动态维护set即可
 */ 

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int left = 0, right = 0, ans = 0;
        set<char> ss;
        while(right < s.size())
        {
            while(right < s.size() && ss.find(s[right]) == ss.end()) ss.insert(s[right++]);
            ans = max(ans, right - left);
            // 到这里[left..right]范围内都是不重复的，因此可以直接删除left
            ss.erase(s[left++]);
        }
        return ans;
    }
};