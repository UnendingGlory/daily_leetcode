# include "header.h"


// T1: 赢得比赛的最少训练时长
// 贪心。
// 假设 初始精力为 A， 初始经验为 B，如果能严格击败第 i个对手
// 那么 A - a0 - a1 - a2 ...  >= ai + 1 -> A >= a0 + a1 + a2 + .. + ai + 1
//     B + b0 + b1 + b2.. >= bi + 1 -> B >= -b0 -b1 -b2 ... + bi + 1
class Solution {
public:
    int minNumberOfHours(int initialEnergy, int initialExperience, vector<int>& energy, vector<int>& experience) {
        int a = 0, b = 0;
        int a_needed = -1, b_needed = -1;
        for (int i = 0; i < energy.size(); ++i) {
            a_needed = max(a_needed, a + energy[i] + 1);
            b_needed = max(b_needed, b + experience[i] + 1);
            a += energy[i];
            b -= experience[i];
        }
        // 大于的话不需要额外训练
        return max(0, a_needed - initialEnergy) + max(0, b_needed - initialExperience;)
    }
};

// T2: 最大回文数字
// 统计数字个数 cnt，如果数字 cnt >= 2，就可以放置。
// 不允许有前导 0，先预处理第一位数字。
// 如果 cnt <= 1，那么最多放置 1位。
// 先放大的，所以从 9到 0进行遍历。
class Solution {
public:
    string largestPalindromic(string num) {
        int cnt[10] = {0};
        for (char c: num) {
            cnt[c - '0']++;
        }
        string prefix;
        // 预处理最高位，最高位不能放置 0
        for (int i = 9; i >= 1; --i) {
            if (cnt[i] >= 2) {
                prefix.push_back(i + '0');
                cnt[i] -= 2;
                break;
            }
        }

        // 处理回文数只有一位的情况
        if (prefix == "") {
            for (int i = 9; i >= 0; --i) {
                if (cnt[i] >= 1) {
                    prefix.push_back(i + '0');
                    return prefix;
                }
            }
        } 

        // 填中间的数
        for (int i = 9; i >= 0; --i) {
            while (cnt[i] >= 2) {
                prefix.push_back(i + '0');
                cnt[i] -= 2;
            }
        }

        // 填完之后，中间的数可以填一位
        string suffix = prefix;
        reverse(suffix.begin(), suffix.end());
        for (int i = 9; i >= 0; --i) {
            if (cnt[i] >= 1) {
                prefix.push_back(i + '0');
                break;
            }
        }
        return prefix + suffix;
    }
};

// T3: 感染二叉树需要的总时间。
// 对整棵树建图，建图后进行最短路算法（宽搜）即可。
// 返回所有结点最短路中的最大值。
class Solution {
public:
    int amountOfTime(TreeNode* root, int start) {
        
    }
};

// DFS
// 如果某个结点是根结点，且是起始结点，那么感染整棵树要的最短时间就是树高
// 如果某个结点是