#include <bits/stdc++.h>
using namespace std;

// 括号生成
class Solution {
    vector<string> ans;
public:

    // 递归，递归时记录当前串左括号和右括号数目，若左括号数目大于小于一半，则加左括号
    // 若左括号数目比右括号数多，则加右括号
    // 递归 + 回溯剪枝

    void dfs(string cur, int left, int right, int index, int n)
    {
        if(index == n) 
        {
            ans.push_back(cur);
            return;
        }
        
        // 限制左括号数目
        if(left < n / 2) dfs(cur + '(', left + 1, right, index + 1, n);

        // 限制右括号数目
        if(left > right) dfs(cur + ')', left, right + 1, index + 1, n);

    }

    vector<string> generateParenthesis(int n) {
        dfs("", 0, 0, 0, 2 * n);
        return ans;
    }
};