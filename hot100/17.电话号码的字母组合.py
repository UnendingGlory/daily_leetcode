# 九键字母组合
# 排列问题，采用递归方法
from typing import List

class Solution:
    def letterCombinations(self, digits: str) -> List[str]:
        n = len(digits)
        letter_map = {'2': 'abc',
                      '3': 'def',
                      '4': 'ghi',
                      '5': 'jkl',
                      '6': 'mno',
                      '7': 'pqrs',
                      '8': 'tuv',
                      '9': 'wxyz'}
        
        combinations = list()  # 存储中间字符
        ans = list()
        def dfs(i):
            if i == n:
                ans.append("".join(combinations))
                return
            digit = digits[i]
            for letter in letter_map[digit]:
                combinations.append(letter)
                dfs(i + 1)
                combinations.pop()

        dfs(0)
        return ans
