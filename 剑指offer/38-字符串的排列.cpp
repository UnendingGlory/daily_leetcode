#include "header.h"

// 全排列算法

// Solution 1：回溯 (会产生重复结果版本)
// 我们考虑n个空格，往这n个空格里从第一个位置到最后一个位置填值
// 如果不考虑重复，我们可以枚举每一个位置，进行递归，使用vis数组记录该位置是否已被填入

class Solution {
    int n;
    vector<bool> vis;
    vector<string> ans;
    string tmp;
public:
    void permu(string s, int idx) {
        if (idx == n) { // 递归边界
            ans.emplace_back(tmp);
            return;
        }
        for (int i = 0; i < n; ++i) {
            if (!vis[i]) {
                tmp.push_back(s[i]);
                vis[i] = true;
                permu(s, idx + 1);
                vis[i] = false; // 这趟走完了记得还原该元素给下一趟可填充
                tmp.pop_back();
            }
        }
    }

    vector<string> permutation(string s) {
        n = s.size();
        vis.resize(n);
    }
};

// Solution 2：回溯 (改进，不会产生重复结果)
// 具体的，先对原字符串进行从小到大的排序，在选取重复元素的时候
// 选取从左到右第一个未被访问过的元素即可

class Solution {
    int n;
    vector<bool> vis;
    vector<string> ans;
    string tmp;
public:
    void permu(string s, int idx) {
        if (idx == n) { // 递归边界
            ans.emplace_back(tmp);
            return;
        }
        for (int i = 0; i < n; ++i) {
            // 一直到与之前不重复且未被访问过的位置i
            if (vis[i] || (i > 0 && s[i] == s[i - 1] && !vis[i - 1])) { 
                continue;
            }
            tmp.push_back(s[i]);
            vis[i] = true;
            permu(s, idx + 1);
            vis[i] = false; // 这趟走完了记得还原该元素给下一趟可填充
            tmp.pop_back();
        }
    }

    vector<string> permutation(string s) {
        n = s.size();
        vis.resize(n);
        std::sort(s.begin(), s.end());
        permu(s, 0);
        return ans;
    }
};


// Solution 3：回溯 (交换版本)
// 我们考虑n个空格，往这n个空格里从第一个位置到最后一个位置填值
// 如果不考虑重复，我们可以枚举每一个位置，进行递归，使用vis数组记录该位置是否已被填入
