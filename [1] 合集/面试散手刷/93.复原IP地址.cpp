#include "header.h"

// 有效 IP地址正好由四个整数（每个整数位于 0 到 255 之间组成，且不能含有前导 0），整数之间用 '.' 分隔。
// 例如："0.1.2.201" 和 "192.168.1.1" 是 有效 IP 地址，
// 但是 "0.011.255.245"、"192.168.1.312" 和 "192.168@1.1" 是 无效 IP 地址。
// 给定一个只包含数字的字符串 s ，用以表示一个 IP 地址，返回所有可能的有效 IP 地址，这些地址可以通过在 s 中插入 '.' 来形成。
// 你不能重新排序或删除 s中的任何数字。你可以按 任何 顺序返回答案。

// 即分割字符串成 4等分，但是数字中不能有前导 0。
// 等分的字符串的范围为 "0" -> "255"。

// Solution1: 暴力循环，枚举每一段的中点。
// 枚举 i, j, k，将 s分割成四段。
// s[: i], s[i+1: j], s[j+1: k], s[k+1: ]。
// 每一段的长度在 1到 3之间，所以各个数的范围：
// 因此 0 <= i < 3, i < j <= i + 3, j < k <= j + 3。
// 且如果起始数字是 0，那么该段就是0，直接进入下一段
// 时间复杂度：O(3^3) = O(1)，空间复杂度：O(4) = O(1)
class Solution {
public:
    // 判断字符串 <= "255"
    bool check(string s) {
        if (s.size() < 3) {
            return true;
        }
        return s <= "255";
    }

    vector<string> restoreIpAddresses(string s) {
        int n = s.size();
        if (n < 4 || n > 12) {
            return {};
        }
        vector<string> ans;
        string a, b, c, d;
        for (int i = 0; i < 3; ++i) {
            a = s.substr(0, i + 1);
            if (a[0] == '0' && a.size() > 1 || !check(a)) {
                break;
            }
            for (int j = i + 1; j <= i + 3 && j < n; ++j) {
                b = s.substr(i + 1, j - i);
                if (b[0] == '0' && b.size() > 1 || !check(b)) {
                    break;
                }
                for (int k = j + 1; k <= j + 3 && k < n; ++k) {
                    c = s.substr(j + 1, k - j);
                    d = s.substr(k + 1);
                    if ((c[0] == '0' && c.size() > 1) || !check(c) || d.size() <= 0) {
                        break;
                    }
                    // d这里是 continue，因为 k的移动会使 d的前缀0消失，d的大小变小。
                    if ((d[0] == '0' && d.size() > 1) || !check(d) || d.size() > 3) {
                        continue;
                    }
                    ans.push_back(a + "." + b + "." + c + "." + d);
                }
            }
        }
        return ans;
    }
};

// Solution2: 递归回溯，枚举每一段。
// 从本质上讲，充分的递归回溯和暴力循环是等价的，复杂度相同。
// dfs(segId, segStart)，代表当前在枚举第 segId段，枚举的起点下标为 segStart。
// 只有在 segId = 4且 segStart == s.size()时加入答案即可。
// 递归其实没有暴力快。
class Solution {
public:
    vector<string> path;
    vector<string> ans;
    vector<string> restoreIpAddresses(string s) {
        dfs(s, 0, 0);
        return ans;
    }

    // s是否 <= "255"
    bool check(string &s) {
        if (s.size() < 3) {
            return true;
        }
        return s <= "255";
    }

    void dfs(string &s, int segId, int segStart) {
        if (segId == 4 && segStart == s.size()) {
            string tmp;
            tmp += path[0];
            for (int i = 1; i < path.size(); ++i) {
                tmp.push_back('.');
                tmp += path[i];
            }
            ans.push_back(tmp);
            return;
        }
        for (int i = segStart; i <= segStart + 2 && i < s.size(); ++i) {
            string cur = s.substr(segStart, i - segStart + 1);
            if ((cur[0] == '0' && cur.size() > 1) || !check(cur)) { // 进入下一段
                return; // 返回上一层
            }
            path.push_back(cur);
            dfs(s, segId + 1, i + 1);
            path.pop_back();
        }
    }
};
