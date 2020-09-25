#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string compressString(string S) {
        string ans;
        char pre = S[0];
        int cnt = 0;
        S.push_back('#');
        for(int i = 0; i < S.size(); i++)
        {
            if(S[i] == pre) cnt++;
            if(S[i] != pre) 
            {
                ans.push_back(pre);
                ans += to_string(cnt);
                cnt = 1;
            }
            pre = S[i];
        }
        return ans.size() < S.size() ? ans : (S.pop_back(), S);
    }
};