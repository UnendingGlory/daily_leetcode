// 给定两个字符串 s 和 t ，如果它们的编辑距离为 1 ，则返回 true ，否则返回 false 。
// 字符串 s 和字符串 t 之间满足编辑距离等于 1 有三种可能的情形：
// 往 s 中插入 恰好一个 字符得到 t
// 从 s 中删除 恰好一个 字符得到 t
// 在 s 中用 一个不同的字符 替换 恰好一个 字符得到 t

// 可以转化为编辑距离问题的子问题。
// dp[i][j] 代表 s[0...i] 和 t[0...j] 之间的编辑距离。

// 也可以直接使用逻辑判断。
// 首先，如果编辑距离为1，那么两个字符串长度之差不会超过1。
// 假设 len(s) <= len(t)。
// 那么有两种情况。
// 1. len(s) == len(t)。
//    指针i, j同步开始遍历，如果 s[i] != s[j]。
//    那么 i+1, j+1 之后的位置的字符都应该相等。 
// 2. len(s) + 1= len(t)
//    指针i, j同步开始遍历，如果 s[i] != s[j]。
//    那么 i, j+1 之后的位置的字符都应该相等。
//    例如 “abcd” 和 "abxcd"
class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        int len_s = s.size(), len_t = t.size();
        if (abs(len_s - len_t) > 1 || s == t) {
            return false;
        }
        if (len_s > len_t) {
            swap(s, t);
            swap(len_s, len_t); // 长度记得交换
        }
        bool flag = false;
        for (int i = 0, j = 0; i < len_s && j < len_t; ++i, ++j) {
            if (s[i] != t[j]) {
                if (!flag) {
                    flag = true;
                } else {
                    return false;
                }
                // 如果长度相同则 i, j指针继续同步前进。
                // 如果长度不同则 i指针慢一步即可。
                if (len_s != len_t) {
                    --i;
                }
            }
        }
        return true;
    }
};
