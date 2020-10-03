#include <bits/stdc++.h>
using namespace std;

/*
 * 即在字符串S中找寻字符串J出现的所有字母
 */

class Solution {
public:
    int numJewelsInStones(string J, string S) {
        int ans = 0;
        unordered_map<char, bool> m;
        for(const char &i : J) m[i] = true;
        for(const char &i : S)
        {
            if(m[i]) ++ans;
        }
        return ans;
    }
};