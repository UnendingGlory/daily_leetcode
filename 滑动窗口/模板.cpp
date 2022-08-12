#include "header.h"

// 逻辑的嵌入位置需要根据题目而定
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int l = 0, r = 0, ans = 0;
        while (r < s.size()) {
            while (xxx) { // 不满足某条件
                //
                ++l;
            }
            ans = max(ans, r - l + 1); // 更新答案
            // hashtable.insert(s[r]);
            ++r;
        }
        return ans;
    }
};
