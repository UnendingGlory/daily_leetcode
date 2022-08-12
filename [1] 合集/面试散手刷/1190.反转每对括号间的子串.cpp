#include "header.h"

//请你按照从括号内到外的顺序，逐层反转每对匹配括号中的字符串，并返回最终的结果。
// 输入：s = "(abcd)"
// 输出："dcba"
// 输入：s = "(u(love)i)"
// 输出："iloveu"
// 解释：先反转子字符串 "love" ，然后反转整个字符串。

// Solution1: 栈。
// 从左到右遍历，使用 str记录当前层字符串。
// 遇到左括号，将 str插入到栈中。
// 遇到右括号，将 str进行反转，将结果返回给上一层。
// 遇到字符则放入 str中。
// 字符入栈，遇到右括号将字符出栈。
// 时间复杂度：O(n)，空间复杂度：O(n)
class Solution {
public:
    string reverseParentheses(string s) {
        stack<string> stk;
        string str;
        for (auto &ch: s) {
            if (ch == '(') {
                stk.push(str);
                str = "";
            } else if (ch == ')') {
                reverse(str.begin(), str.end());
                str = stk.top() + str; // 和上一层结果合并
                stk.pop();
            } else {
                str.push_back(ch);
            }
        }
        return str;
    }
};

// Solution2: 递归。与 394题 字符串解码递归思路类似。
// ic(u(love)i)bd
// 递归，从内层向外层反转，函数 dfs返回翻转后的字符串。
// 过程中需要不断建立新字符串 cur。
// 递归边界：到字符串尾部或者右括号，直接返回空串。
// 遇到左括号后，需要对内部字符串进行处理，拿到结果后进行反转。
// 遇到字符则将其打入 cur。
// 过程中只需要建立一个全局指针即可。
// 时间复杂度：O(n)，空间复杂度：递归栈 O(n)
class Solution {
public:
    string dfs(string &s, int &i) {
        if (i == s.size()) { // 遇到尾部
            return "";
        }
        if (s[i] == ')') { // 遇到右括号
            ++i;
            return "";
        }
        string cur;
        if (s[i] == '(') {
            ++i;
            cur += dfs(s, i);
            reverse(cur.begin(), cur.end());
        } else {
            cur.push_back(s[i]);
            ++i;
        }
        return cur + dfs(s, i); // 后序dfs
    }

    string reverseParentheses(string s) {
        int i = 0;
        return dfs(s, i);
    }
};

// Solution3: 预处理 + 方向遍历。
// 可以将括号的反转理解为逆序地遍历括号。
// ic(u(love)i)bd -> iciloveubd
// 正向：i -> c -> (，遇到左括号后跳入该左括号对应的右括号，并改变方向
// 反向：i -> )，     遇到右括号后跳入该右括号对应的左括号，并改变方向
// 正向：l -> o -> v -> e -> ), 遇到右括号后跳入该右括号对应的左括号，并改变方向
// 反向：u -> (，     遇到左括号后跳入该左括号对应的右括号，并改变方向
// 正向：b -> d
// 结果：iciloveubd
// 由于需要知道括号的配对位置信息，因此需要预处理。
// 时间复杂度：O(n)，空间复杂度：O(n)
class Solution {
public:
    string reverseParentheses(string s) {
        int n = s.size();
        // 预处理
        vector<int> pos(n);
        stack<int> stk;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '(') {
                stk.push(i);
            }
            if (s[i] == ')') {
                pos[stk.top()] = i;
                pos[i] = stk.top();
                stk.pop();
            }
        }
        // 计算结果。
        string ans;
        int i = 0, dir = 1; // 正向
        while (i < n) {
            if (s[i] == '(' || s[i] == ')') {
                i = pos[i];
                dir = -dir;
            } else {
                ans.push_back(s[i]);
            }
            i += dir;
        }
        return ans;
    }
};
