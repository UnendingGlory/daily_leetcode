class Solution(object):
    def isMatch(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: bool
        """

        dic = {}
        state = 1
        for idx, i in enumerate(p):
            if 'a' <= i <= "z" or i == '.':
                dic.setdefault(state, {}).update({i: state + 1})
                state += 1
            elif i == '*':
                dic[state - 1][p[idx - 1]] = state - 1
                dic[state - 1]['$'] = state

        def helper(sta, px):
            if px:
                try:
                    tmp1 = dic[sta].get(px[0], False)
                    tmp2 = dic[sta].get('.', False)
                    tmp3 = dic[sta].get('$', False)
                except:
                    return False
                if tmp1:
                    if helper(tmp1, px[1:]):
                        return True
                if tmp2:
                    if helper(tmp2, px[1:]):
                        return True
                if tmp3:
                    if helper(tmp3,px):
                        return True
                return False
            else:
                try:
                    tmp = dic[sta].get('$', False)
                    return helper(tmp, px)
                except:
                    pass
                if sta == state:
                    return True
                return False
        return helper(1, s)


s = Solution()
tests = [
    ("babbcaacbccbbbbbabb","bb*.b*b*a*aba*c"),
    ("aa","a*"),
    ("abbabaaaaaaacaa", "a*.*b.a.*c*b*a*c*"),
    ("aaba", "ab*a*c*a"),
    ("aaa", "a*a"),
    ("abcdede", "ab.*de"),
]

for item in tests:
    res = s.isMatch(*item)
    print(res)