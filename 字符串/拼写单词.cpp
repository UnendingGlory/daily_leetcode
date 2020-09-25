#include <bits/stdc++.h>
using namespace std;


// 仔细读题，每次拼写某个单词时时，chars中的每个字母只能用一次
// 多个单词的拼写其实是在重复使用chars
class Solution {
public:
    int countCharacters(vector<string>& words, string chars) {
        int p[26];
        memset(p, 0, sizeof(p));
        int ans = 0;
        for(char c : chars) ++p[c - 'a'];
        for(string w : words)
        {
            int temp[26];
            memset(temp, 0, sizeof(temp));
            bool flag = true;
            for(char c : w)
            {
                ++temp[c - 'a'];
                if(p[c - 'a'] < temp[c - 'a'])
                {
                    flag = false;
                    break;
                }
            }
            if(flag) ans += w.size();
        }
        //delete []temp, p;
        return ans;
    }
};

int main()
{
    return 0;
}