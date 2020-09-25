#include <bits/stdc++.h>
using namespace std;

/** 判断子序列
 *  基础办法：双指针法，遍历t，若t[i] = s[j]，则++i, ++j,遍历到t的末尾时，若 j 是s的末尾，则是子串
*/
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int j = 0;
        for(int i = 0; i < t.size(); ++i)
        {
            if(t[i] == s[j]) ++j, ++i;
        }
        return j == s.size();
    }
};