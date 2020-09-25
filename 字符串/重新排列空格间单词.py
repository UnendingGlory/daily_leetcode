# 如果用C++，则需要先统计好空格数量，并且存好单词
# 然后计算每个单词间需要插多少个空格，并安排好
# 然后拼接好最后的空格

class Solution:
    def reorderSpaces(self, text: str) -> str:
        cnt = 0
        # 统计空格个数
        for ch in text:
            if ch == ' ':
                cnt += 1

        words = text.split()
        n = len(words)
        
        if n == 1:
            return words[0] + ' ' * cnt

        else:
            s = ''
            for w in words[:-1]:
                s += w + ' ' * (cnt // (n-1))
            s += words[-1] + ' ' * (cnt % (n-1))

            return s
