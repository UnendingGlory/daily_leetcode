# 给你一个字符串 s 、一个字符串 t 。
# 返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 ""。
# 注意，t中的字母可能会重复。
# 输入：s = "ADOBECODEBANC", t = "ABC"
# 输出："BANC"

# Solution：滑动窗口。
# 使用一个指针 r 用来延展窗口 w，使用一个指针 l 用来收缩窗口。
# 如果 w 不包含 t，那么 r一直右移，直到 w 包含 t。
# 可以开始右移指针 l，用来收缩窗口。
# 如果窗口包含所有的字符，则该窗口 w 可以作为一个答案。
# 如果 w 长度恰好和 t 相等，那么该 w 即最小答案串。

# 如何判断窗口 w 是否 包含 t？
# 可以使用两个 map 分别记录 w 和 t 中的字符的个数。
# 判断 w 中字符个数 是否比 t中字符个数小即可。 
# 时间复杂度：O(nk), k为字典集的大小
import collections

class Solution:
    def minWindow(self, s: str, t: str) -> str:
        ori, win = collections.defaultdict(int), collections.defaultdict(int)
        for c in t:
            ori[c] += 1

        def check(): # 检查窗口是否包含串 t
            for key in ori.keys():
                if key not in win or win[key] < ori[key]:
                    return False
            return True

        l, r = 0, 0
        ans = s # 也可以使用 start, len 来记录结果字符串
        while r < len(s):
            while r < len(s) and not check(): # r一直右移
                win[s[r]] += 1
                r += 1
            # 到达了边界check可能返回True，若check失败，且ans未更新过，没有答案
            if r == len(s) and not check() and ans == s: 
                return ""
            # 在这里 [l, r] 子串包含串t，开始收缩窗口
            while check():
                win[s[l]] -= 1
                l += 1
            # 这里 [l, r] 子串不包含串t, [l-1, r]包含串t
            if r - l + 1 == len(t):
                return s[l-1: r]
            if r - l + 1 < len(ans): # 更新答案
                ans = s[l-1: r]
        return ans

# 优化上面方法的滑动窗口写法，但是从效率上分析，和上面是相同的
class Solution:
    def minWindow(self, s: str, t: str) -> str:
        ori, win = collections.defaultdict(int), collections.defaultdict(int)
        for c in t:
            ori[c] += 1

        def check(): # 检查窗口是否包含串 t
            for key in ori.keys():
                if key not in win or win[key] < ori[key]:
                    return False
            return True

        l, r = 0, 0
        ans = s + 'a' # 添加一个字符，以免答案和原字符串相等
        while r < len(s):
            # 滑动窗口题目这里不用再循环右移
            # check() 失败了后，r += 1相等于循环右移
            win[s[r]] += 1
            while check() and l <= r:
                # check()成功便可以收缩窗口
                # [l, r]包含子串 t
                if r - l + 1 < len(ans):
                    ans = s[l: r+1]
                win[s[l]] -= 1
                l += 1
            r += 1
        return '' if ans == s + 'a' else ans
                


# 优化时间和空间复杂度
# https://leetcode.cn/problems/minimum-window-substring/solution/tong-su-qie-xiang-xi-de-miao-shu-hua-dong-chuang-k/
# check每次需要使用 O(k)的时间复杂度，其中 k 为字典集的大小。
# 可以字典改为还需要的元素个数，记为 need，如果某 key 的 value 为负数则代表该 key 足够。
# 使用一个 变量needCnt 来记录t中字母在 need 中的缺失数。
# 时间复杂度：O(n)
class Solution:
    def minWindow(self, s: str, t: str) -> str:
        need = collections.defaultdict(int)
        for c in t:
            need[c] += 1
        needCnt = len(t)
        l = 0
        ans = s+'a' # 添加一个字符，以免答案和原字符串相等
        for r, c in enumerate(s): # r指针一直右移
            if need[c] > 0:
                needCnt -= 1
            need[c] -= 1
            if needCnt == 0:       # 滑动窗口已经包含了所有T元素
                while True:        # 增加l，排除多余元素
                    c = s[l] 
                    if need[c] == 0: # need[c] = 0代表 s[l] 是一个必须包含的字母
                        break
                    need[c] += 1
                    l += 1
                if r - l < len(ans):   #记录结果
                    ans = s[l: r+1]
                need[s[l]] += 1  # 让 l 再增加一个位置，寻找新的满足条件滑动窗口
                needCnt += 1
                l += 1
        return '' if ans == s+'a' else ans    #如果res始终没被更新过，代表无满足条件的结果
