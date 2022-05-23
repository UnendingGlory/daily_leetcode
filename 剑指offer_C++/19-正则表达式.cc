#include "../header.h"
// 三种方法

// https://leetcode.cn/problems/regular-expression-matching/solution/liang-chong-si-lu-di-gui-dong-tai-gui-hu-gh69/

// Solution1:
// 递归回溯法
// 主要需要处理的就是a*这种情况
// a*即可以当作0个，也可以当作1个a，也可以当作多个a
// TODO: 修改
class Solution {
    int s_size, p_size;
public:

    // index i for s, index j for p
    bool matchRecur(const string& s, const string& p, int i, int j) {
        if (i == s_size && j == p_size) return true;
        // if pattern end in advance
        if (j == p_size) return false;
        if (p[j + 1] == '*') {
            // next state, 1个匹配 or 多个字符匹配 or 没有匹配
            // 其实这里的1个匹配的情况可以去除，因为1个匹配就是多个匹配后接0个匹配
            // 没有匹配：比如 abb 和 a*abb 也是匹配的
            // s: ab p: .*c
            if (p[j] == s[i] || p[j] == '.' && i < s_size) {
                return matchRecur(s, p, i + 1, j + 2) || matchRecur(s, p, i + 1, j) || matchRecur(s, p, i, j + 2);
            } else {
                // not equal, ignore '*'
                return matchRecur(s, p, i, j + 2);
            }
        }
        if (s[i] == p[j] || p[j] == '.' && i < s_size) {
            return matchRecur(s, p, i + 1, j + 1);
        }
        return false;
    }

    bool isMatch(string s, string p) {
        s_size = s.size(), p_size = p.size();
        return matchRecur(s, p, 0, 0);
    }
};

// 动态规划法，将递归转换为状态转移方程
// dp[i][j]代表s的前i个字符能否和p的前j个字符匹配
// dp[0][0]为空字符，可以匹配，dp[i][j]对应的字符是s[i-1]和p[j-1]
// 当p[j - 1] = '*', 任意次匹配 || 0次匹配 || 1次匹配 
// dp[i][j] = (dp[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.')
// || dp[i][j - 2] || dp[i][j - 1]
// 当p[j-1] = '*', 任意次匹配 || 0次匹配 || 1次匹配 

class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size() + 1, n = p.size() + 1;
        vector<vector<bool>> dp(m, vector<bool>(n, false));
        dp[0][0] = true;
        for(int j = 2; j < n; j += 2)
            dp[0][j] = dp[0][j - 2] && p[j - 1] == '*';
        for(int i = 1; i < m; i++) {
            for(int j = 1; j < n; j++) {
                dp[i][j] = p[j - 1] == '*' ?
                    dp[i][j - 1] || dp[i][j - 2] || dp[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'):
                    dp[i - 1][j - 1] && (p[j - 1] == '.' || s[i - 1] == p[j - 1]);
            }
        }
        return dp[m - 1][n - 1];
    }
};

// 使用编译原理相关知识
// 对于每一个pattern构造一个DFA
// 判断s是否能走到自动机的终点
// 如pattern: ab.*d
//                 / . \  
//     a        b  \   /  $        d
// 0 -----> 1 -----> 2  -----> 3 -----> 4
// 0是开始状态，4是结束状态，$代表空（因为*可以匹配0次）

// 如pattern: aba*c
//                 / a \  
//     a        b  \   /  $         c
// 0 -----> 1 -----> 2  -----> 3 -----> 4

// 构建完成后再通过dfs的方式对s进行判断
// 当然，dfs的方法很慢，C++代码会通过全部测试用例然后超时...（就很迷，明明都通过了）

class Solution {
    // key为当前状态，char为下一字符，int为转移到的状态
    unordered_map<int, unordered_map<char, int>> table;
    int end_state;
public:
    void constructDFA(const string& p) {
        int state = 0;
        for (int i = 0; i < p.size(); ++i) {
            char c = p[i];
            if (c >= 'a' && c <= 'z' || c == '.') {
                table[state].clear();
                table[state][c] = state + 1;
                ++state;
            }
            if (c == '*') {
                table[state - 1][p[i - 1]] = state - 1; // 转移到自己，会覆盖旧值
                table[state - 1]['$'] = state; // 输入为空转移到下一状态，index不自增
            } 
        }
        end_state = state;
        // for (const auto& [fir, sub] : table) {
        //     for (const auto& ss : sub) {
        //         cout << fir << " " << ss.first << " " << ss.second << endl;
        //     }
        // }
    }

    // cur代表当前状态，i为当前字符
    bool dfs(int cur, const string&s, int i) {
        if(i >= s.size() && cur == end_state) return true;

        // 注意三者匹配只要有一个符合就返回true
        if (i < s.size()) {
            if (table[cur].find(s[i]) != table[cur].end()) { // 当前字符
                int cur1 = table[cur][s[i]];
                if(dfs(cur1, s, i + 1)) return true;
            }
            if (table[cur].find('.') != table[cur].end()) { // '.'
                int cur2 = table[cur]['.'];
                if(dfs(cur2, s, i + 1)) return true;
            }
            if (table[cur].find('$') != table[cur].end()) { // '$'
                int cur3 = table[cur]['$'];
                if(dfs(cur3, s, i))     return true; // 注意是空字符这里下标i不变
            }
            return false;
        }
        else { // 如果已经到了字符串末尾，需要判断可以一直为空走到底的情况
            if (table[cur].find('$') != table[cur].end()) { // '$'
                cur = table[cur]['$'];
                return dfs(cur, s, i); // 注意是空字符这里下标i不变
            }
        }
        return false;
    }

    bool isMatch(string s, string p) {
        constructDFA(p);
        return dfs(0, s, 0);
    }
};