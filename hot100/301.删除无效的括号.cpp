// 给你一个由若干括号和字母组成的字符串 s ，删除最小数量的无效括号，使得输入的字符串有效。
// 返回所有可能的结果。
// 输入：s = "()())()"
// 输出：["(())()","()()()"]

// Solution: 递归 + 回溯。
// 先通过一次遍历统计所有多余的左括号数 lremain 和多余的右括号书 rremain。
// 当遍历到左括号时，左括号数目 + 1, lremain++。
// 当遍历到右括号时，如果此时左括号不为0，则该右括号可以与之前的左括号匹配 lremain--，否则 rremain++。

// 再通过递归回溯，来尝试所有去掉 lremain个左括号和 rremain个右括号的方案。
// 递归边界（剪枝技巧）：
// 1. 如果 lremain = rremain = 0，那么检查当前字符串是否匹配。
// 2. 如果当前 lremain + rremain > 剩余尝试的字符串长度，退出。

// 此外，结果有可能重复，去重的方法有两种可以选择：
// 1. 哈希表去重。
// 2. 如果遇到连续的字符，只需要去除一次即可，比如 '((()'，前三个连续的左括号只需要去除一次。
class Solution {
public:
    vector<string> ans;
    vector<string> removeInvalidParentheses(string s) {
        int lremain = 0, rremain = 0;
        for (char c: s) {
            if (c == '(') {
                lremain++;
            } else if (c == ')') {
                if (lremain == 0) {
                    rremain++;
                } else {
                    lremain--; // 这里只有 lremain需要自减。
                }
            }
        }
        dfs(s, 0, lremain, rremain);
        return ans;
    }

    void dfs(string s, int start, int lremain, int rremain) {
        if (lremain == 0 && rremain == 0) {
            if (check(s)) {
                ans.emplace_back(s);
            }
            return;
        }
        if (lremain + rremain > s.size()) {
            return;
        }
        // 尝试对后面位置的字符串进行去除括号，需要字符串拼接
        for (int i = start; i < s.size(); ++i) {
            if (i != start && s[i] == s[i-1]) { // 遇到连续字符只需要去除一次
                continue;
            }
            if (lremain > 0 && s[i] == '(') { // 去除一个左括号
                dfs(s.substr(0, i) + s.substr(i+1), i, lremain - 1, rremain);
            }
            if (rremain > 0 && s[i] == ')') { // 去除一个右括号
                dfs(s.substr(0, i) + s.substr(i+1), i, lremain, rremain - 1);
            }
        }
    }

    // 检查当前字符串是否有效（完全匹配）。
    bool check(string s) {
        int cnt = 0;
        for (char c: s) {
            if (c == '(') {
                cnt++;
            } else if (c == ')') {
                cnt--;
                if (cnt < 0) {
                    return false;
                }
            }
        }
        return cnt == 0;
    }
};
