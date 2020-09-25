#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // 先整个反转字符串，再操作，逐单词反转
    string reverseWords(string s) {
        reverse(s.begin(), s.end());
        string ans, temp;
        int i = 0;
        while(i < s.size())
        {
            while(i < s.size() && s[i] == ' ') ++i; // 寻找不是空格

            while(i < s.size() && s[i] != ' ')
            {
                temp.push_back(s[i]);
                ++i;
            }// 遍历到单词末尾

            while(i < s.size() && s[i] == ' ') ++i; // 寻找不是空格

            reverse(temp.begin(), temp.end());
            ans += temp;
            if(i != s.size()) ans.push_back(' ');
            temp.clear();
        }
        return ans;
    }
};