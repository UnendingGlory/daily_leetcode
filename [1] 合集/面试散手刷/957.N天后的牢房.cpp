#include "header.h"

// 监狱中 8 间牢房排成一排，每间牢房可能被占用或空置。
// 每天，无论牢房是被占用或空置，都会根据以下规则进行变更：
// 如果一间牢房的两个相邻的房间都被占用或都是空的，那么该牢房就会被占用。
// 否则，它就会被空置。
// 注意：由于监狱中的牢房排成一行，所以行中的第一个和最后一个牢房不存在两个相邻的房间。
// 给你一个整数数组 cells ，用于表示牢房的初始状态：如果第 i 间牢房被占用，则 cell[i]==1，否则 cell[i]==0 。另给你一个整数 n 。
// 请你返回 n 天后监狱的状况（即，按上文描述进行 n 次变更）。

// cells.length == 8
// cells[i] 为 0 或 1
// 1 <= n <= 10^9

// Solution1: 模拟。
// n会长达 10 ^ 9，简单模拟显然会超时。
class Solution {
public:
    void change(vector<int>& cells, vector<int>& ans) {
        for (int i = 1; i < cells.size() - 1; ++i) {
            if (cells[i - 1] == 0 && cells[i + 1] == 0) {
                ans[i] = 1;
            } else if (cells[i - 1] == 1 && cells[i + 1] == 1) {
                ans[i] = 1;
            } else {
                ans[i] = 0;
            }
        }
    }
    vector<int> prisonAfterNDays(vector<int>& cells, int n) {
        vector<int> ans(cells);
        ans[0] = ans[cells.size() - 1] = 0;
        while(n--) {
            change(cells, ans);
            cells = ans;
        }
        return ans;
    }
};

// Solution2: 找周期 + 状态压缩动态规划。
// 由于一共只有 8位，因此最多只有 256种状态。
// 经过变换后，一定会形成一个循环，我们只需要找到循环周期 T即可。
// 注意，初始状态不参与循环，因为初始状态两侧可能为1，而循环内周期的数组两侧均为0。
// 我们要找的答案即 (n - 1) % T时的状态。
// 由于只有8位，因此我们直接用整数的每一位来模拟数组。
// 使用整数 state来模拟数组，state的值如果重复出现了，就说明形成了一个循环。
// 注意数组位下标是从0开始的，是整数位的高位。
// 状态压缩即将状态压缩为一个整数（通常为二进制数）。
class Solution {
public:
    vector<int> prisonAfterNDays(vector<int>& cells, int n) {
        int state = 0;
        // 计算初始状态的 state，数组的左侧在高位，右侧在低位。
        for (int i = 7; i >= 0; --i) {
            if (cells[7 - i] > 0) {
                state |= (1 << i);
            }
        }
        
        unordered_map<int, int> hashtable; // state -> T
        int T = 0;

        int i;
        for (i = 1; i <= n; ++i) {
            state = getState(state);
            if (hashtable.find(state) == hashtable.end()) {
                hashtable[state] = T++;
            } else {
                break;
            }
        }

        // t即周期，初始状态不参与循环。
        // 因此结果的 state整数即为 (n - 1) % t。
        // i > n 代表凑不齐一个周期就结束了。
        if (i <= n) {
            T = (n - 1) % T;
        }

        for (auto kv: hashtable) {
            if (kv.second == T) {
                state = kv.first;
                break;
            }
        }
        // 整数转换为答案。
        vector<int> ans(8);
        for (int i = 6; i >= 1; --i) {
            if ((state >> i) & 1) {
                ans[7 - i] = 1;
            }
        }
        return ans;
    }
    
    // 改变每一天的状态
    int getState(int state) {
        int ans = 0;
        // 位置 0和 7必定是 0。
        // 位运算要搞清楚。
        for (int i = 6; i >= 1; --i) {
            if (((state >> (i + 1)) & 1) == ((state >> (i - 1)) & 1)) {
                ans |= (1 << i);
            }
        }
        return ans;
    }
};
