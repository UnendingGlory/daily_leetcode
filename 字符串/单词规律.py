# 290
# 双射问题
class Solution:
    # 建立双射即可，双map，复杂度o(m + n)
    def wordPattern(self, pattern: str, s: str) -> bool:
        words = s.split()
        ch2word = dict()
        word2ch = dict()
        if len(words) != len(pattern):
            return False
        for ch, word in zip(pattern, words):
            if (word in word2ch and word2ch[word] != ch) or\
                (ch in ch2word and ch2word[ch] != word):
                return False
            word2ch[word] = ch
            ch2word[ch] = word
        return True

# 205
class Solution1:
    def isIsomorphic(self, s: str, t: str) -> bool:
        s2t = dict()
        t2s = dict()
        for i in range(len(s)):
            x, y = s[i], t[i]
            if (x in s2t and s2t[x] != y) or (y in t2s and t2s[y]) != x):
                return False
            s2t[x] = y
            t2s[y] = x
        return True