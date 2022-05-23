# 给定一个字符串s，请你找出其中不含有重复字符的 最长子串 的长度。

# 滑动窗口
# "abcabcbb" --> 答案为 "abc"
# 依次递增地枚举结果子串的起始位置，那么结果子串的结束位置也是递增的
# 以 (a)bcabcbb 开始的最长字符串为 (abc)abcbb
# 以 a(b)cabcbb 开始的最长字符串为 a(bca)bcbb
# 以 ab(c)abcbb 开始的最长字符串为 ab(cab)cbb
# 以 abc(a)bcbb 开始的最长字符串为 abc(abc)bb
# 以 abca(b)cbb 开始的最长字符串为 abca(bc)bb
# 以 abcab(c)bb 开始的最长字符串为 abcab(cb)b
# 以 abcabc(b)b 开始的最长字符串为 abcabc(b)b
# 以 abcabcb(b) 开始的最长字符串为 abcabcb(b)

# 因为窗口内的字母是不重复的，所以结果子串的结束位置也是递增的
# 使用两个指针 l 和 r
# 对于每一轮l内，如果l和r不重复，则r++
# 使用set来记录窗口内的字符
# 无重复字符的最长子串长度即max(ans, r - l + 1)
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        win = set()
        n = len(s)
        r, ans = -1, 0
        for l in range(n):
            if l != 0: # 移除前一个字符
                win.remove(s[l - 1])
            while r + 1 < n and s[r + 1] not in win:
                r = r + 1
                win.add(s[r])
            ans = max(ans, r - l + 1)
        return ans
