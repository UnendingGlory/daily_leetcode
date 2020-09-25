#include <bits/stdc++.h>
using namespace std;

/** 不重复的最长子串。
依次递增地枚举子串的起始位置，那么子串的结束位置也是递增的。
滑动窗口算法。我们使用两个指针表示字符串中的某个子串（的左右边界）。
其中左指针代表着上文中「枚举子串的起始位置」， 
在每一步的操作中，我们会将左指针向右移动一格，表示我们开始枚举下一个字符作为起始位置，
然后我们可以不断地向右移动右指针，但需要保证这两个指针对应的子串中没有重复的字符。
在移动结束后，这个子串就对应着 以左指针开始的，不包含重复字符的最长子串。
我们记录下这个子串的长度；在枚举结束后，我们找到的最长的子串的长度即为答案。
 */

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, bool> ss;
        int left = 0, right = 1, max = 0;
        while(left < s.size())
        {
            ss[s[left]] = true;
            // 若左右指针相遇，则右指针右走一格
            if(left == right) right = left + 1;
            while(right < s.size() && !ss[s[right]])
            {
                ss[s[right]] = true;
                ++right;
            }
            if(right - left > max) max = right - left;
            ss.erase(s[left]);
            ++left;
        }
        return max;
    }
};