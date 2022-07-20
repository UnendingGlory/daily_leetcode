# 栈匹配即可

class Solution:
    def isValid(self, s: str) -> bool:
        stk = []
        left_bracket = ['(', '[', '{']
        bracket_map = {')': '(', ']': '[', '}': '{'}
        for i in s:
            if i in left_bracket:
                stk.append(i)
            else:
                if len(stk) == 0 or stk[-1] != bracket_map[i]: # 不匹配
                    return False
                stk.pop() # 匹配
                stk.pop()
        return len(stk) == 0
