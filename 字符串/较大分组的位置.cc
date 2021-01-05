#include "header.h"

// 字符串处理注意最后一个位置的判断
class Solution {
public:
    vector<vector<int>> largeGroupPositions(string s) {
        int n = s.size(), i = 1, last = s[0], cnt = 1, start = 0;
        vector<vector<int>> ans;
        while (i < n) {
            if (i == n - 1 && s[i] == last && cnt >= 2) {
                ans.push_back({start, i});
                return ans;
            }
            if (s[i] == last) {
                ++cnt;
            }
            else if (s[i] != last){
                if (cnt >= 3) {
                    ans.push_back({start, i - 1});
                }
                cnt = 1;
                start = i;
                last = s[i];
            }
            ++i;
        }
        return ans;
    }
};