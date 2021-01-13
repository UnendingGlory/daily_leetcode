#include "../header.h"
// 三种方法

// 回溯法
class Solution {
public:
    bool isMatch(string s, string p) {

    }
};

// 动态规划法


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