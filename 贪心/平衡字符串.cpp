#include <bits/stdc++.h>
using namespace std;

// 给出字符串中L和R数目已经相同
// 题目未要求求平衡段，偷懒做法，若要求出平衡段则应用双指针遍历或者栈
class Solution {
public:
    int balancedStringSplit(string s) {
        int ans = 0, cnt = 0;
        for(int i = 0; i < s.size(); ++i)
        {
            if(s[i] == 'L') ++cnt;
            else --cnt;
            if(!cnt) ++ans;
        }
        return ans ? ans : 1;
    }
};