#include "header.h"

// Solution 1：先使用栈，得出匹配的括号的位置下标。
// 对下标进行排序，再找出其中的最长连续子序列的长度即是答案。
// 对于 "()((())"，使用栈，得出匹配的括号的位置下标为
// [0, 1, 4, 5, 3, 6]  --> [0, 1, 3, 4, 5, 6]
// 最长连续子序列为 [3, 4, 5, 6]，答案即 4
// 时间复杂度：O(nlog(n))
class Solution {
public:
    int longestValidParentheses(string s) {
        std::stack<int> st;
        vector<int> idx;

        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                st.push(i);
            } else if (!st.empty() && s[i] == ')') {
                idx.emplace_back(st.top());
                idx.emplace_back(i);
                st.pop();
            }
        }
        if (idx.size() == 0) {
            return 0;
        }
        std::sort(idx.begin(), idx.end());

        // 找出最长连续子序列
        int cnt = 1, ans = 0;
        for (int i = 1; i < idx.size(); i++) {
            if (idx[i] == idx[i-1] + 1) {
                ++cnt;
            } else {
                cnt = 1;
            }
            ans = max(cnt, ans);
        }
        return ans;
    }
};

// Solution 2：省略排序的过程，在弹栈的时候进行操作。
// https://leetcode.cn/problems/longest-valid-parentheses/solution/shou-hua-tu-jie-zhan-de-xiang-xi-si-lu-by-hyj8/
// 对于 s "( ) ( ( ( ) )"，遍历每一个位置
// 每当遍历到 ')'时，若下标为i，且栈不为空，则当前最长有效括号的长度为
// cnt = 当前位置i - 栈顶元素位置j + 1
// 遍历到 s[1], cnt = 1 - 0 + 1 = 2
// 遍历到 s[5], cnt = 5 - 4 + 1 = 2
// 遍历到 s[6], cnt = 6 - 3 + 1 = 4
// ans = max(cnt) = 4，看似正确

// 问题：上面只考虑了嵌套的情况，对于连续的情况
// 考虑串 "( ) ( ( ) ) ) ( )"
// s[1]: cnt = 2, s[4]: cnt = 2
// s[5]: cnt = 4, s[6]栈为空不计算，s[8]: cnt = 2
// ans = max(cnt) = 4
// 但是正确的答案应该为 6
// 解决办法：初始栈的预设值为 -1
// 并且改变计算方式为： cnt = 当前位置i - 先出栈后下一个栈顶元素位置 new_j
// 如果栈为空，放入上一个右括号的下标，充当这个预设值的作用

// 初始，栈：[-1]
// 遍历到 s[0]，栈：[-1, 0]
// 遍历到 s[1], 0出栈，cnt = 1 - (-1) = 2
// 遍历到 s[4], 栈：[-1, 2, 3]，3出栈，cnt = 4 - 2 = 2
// 遍历到 s[5], 2出栈，cnt = 5 - (-1) = 6
// 遍历到 s[6], 6入栈，充当之前的-1的预设值的作用
// 遍历到 s[8], 栈：[-1, 6, 7]，7出栈，cnt = 8 - 6 = 2
// ans = max(cnt) = 6
class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> st;
        st.push(-1); // 放入一个预设值，但是作用相当于一个左括号
        int ans = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                st.push(i);
            } else {
                st.pop(); // 先弹出
                if (st.empty()) { // 弹出后栈为空，放入预设值
                    st.push(i);
                } else { // 栈不空才可以计算，否则例如对于 输入 ")"，会计算出答案 2
                    ans = max(ans, i - st.top());
                }
            }
        }
        return ans;
    }
};

// Solution3: 最值型动态规划。
// dp[i]：以s[i]为结尾的子串中，所形成的最长有效子串的长度，且有效子串是以s[i]为结尾
// 对于 s[i] = '('，以其结尾的子串，必定不是有效子串
// 对于 s[i] = ')'，每两个字符检查一次
// 1. 对于形如连续括号 "....()"，即 s[i] = ')' and s[i-1] = '('
//    则 dp[i] = dp[i-2] + 2
// 2. 对于形如嵌套括号 "... ))"，即 s[i] = ')' and s[i-1] = ')'
//    以 s[i-1] 结尾的最长有效子串长度为 dp[i-1]
//    翻过这个长度，考察字符 s[i - dp[i-1] - 1]
//    I.  若该字符不存在 或者 为 ')'，则不匹配，dp[i] = 0
//    II. 若该字符为 '('，有效长度为 dp[i - dp[i-1] - 2] + dp[i-1] + 2
//        即 "... (( ... ))"
//        注意，需要保证 s[i - dp[i-1] - 2]存在
//        若不存在，则 dp[i] = dp[i-1] + 2

// 转移方程：
// if s[i] = ')' and s[i-1] = '(':
//     dp[i] = dp[i-2] + 2
// if s[i] = ')' and s[i-1] = ')':
//     if i - dp[i-1] - 1 < 0 or s[i-dp[i-1]-1] = ')':
//         dp[i] = 0
//     else:
//         dp[i] = dp[i-1] + 2, if i - dp[i-1] - 2 < 0
//         dp[i] = dp[i - dp[i-1] - 2] + dp[i-1] + 2, if i - dp[i-1] - 2 >= 0
// 边界条件：对于 s[i] = '('，dp[i] = 0 (需要有效子串以 i 结尾)
// dp[0] 必定为 0，从 位置1开始往后递推，中间更新答案

class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size(), j, ans = 0;
        vector<int> dp(n, 0);
        for (int i = 1; i < s.size(); ++i) {
            if (s[i] == ')') {
                if (s[i-1] == '(') {
                    dp[i] = (i >= 2 ? dp[i-2] : 0) + 2;
                } else {
                    // 跨过 '( (...) )' 中间的 ' (...) '
                    if (i - dp[i-1] - 1 >= 0 && s[i - dp[i-1] - 1] == '(') {
                        j = i - dp[i-1] - 2; // '... ((...))'
                        dp[i] = (j >= 0 ? dp[j]: 0) + dp[i-1] + 2;
                    }
                }
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};
