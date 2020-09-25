#include <bits/stdc++.h>
using namespace std;

// 偶数次数的才能对称，奇数次数的要么没有，有则去除对子后必然只剩一个在中间
// 所以统计奇数次数的字符个数即可
class Solution {
public:
    int longestPalindrome(string s) {
        int cnt[26][2]; // 0: Upper , 1: lower
        memset(cnt, 0, sizeof(cnt));
        for(int i = 0; i < s.size(); ++i) 
        {
            if(isupper(s[i])) ++cnt[s[i] - 'A'][0];
            else ++cnt[s[i] - 'a'][1];
        }
        int ans = s.size();
        for(int i = 0; i < 2; ++i)
        {
            for(int j = 0; j < 26; j++)
                if(cnt[j][i] & 1) --ans; // 奇数二进制最后一位为1
        }
        // 若不等则说明有奇数次的字符
        return ans == s.size() ? ans : ans + 1; 
    }
};
int main()
{
    return 0;
}