# 数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。
# 递归 + 回溯
# 用 left 记录左括号剩余的数量， right记录右括号剩余的数量
# 如果 left >= right，就填充左括号
# 如果 left < right，即可以填充左括号又可以填充右括号
# 如果 left == right = 0，退出递归

class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        ans = list()
        def dfs(s, left, right):
            if left < 0:  # 递归边界
                return
            if left == right == 0:
                ans.append(s)
                return
            if left >= right:
                dfs(s + '(', left - 1, right)
            else:
                dfs(s + '(', left - 1, right)
                dfs(s + ')', left, right - 1)
        dfs('', n, n)
        return ans
