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