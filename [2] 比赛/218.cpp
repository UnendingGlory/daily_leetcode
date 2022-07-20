#include "header.h"

// T1 字符串处理
class Solution {
public:
    string interpret(string command) {
        string ans;
        for (int i = 0; i < command.size();) {
            if(command[i] == 'G') ans.push_back('G'), ++i;
            if(command[i] == '(')
            {
                if(i < command.size() - 1 && command[i + 1] == 'a')
                {
                    ans += "al";
                    i += 4;
                }
                else {
                    ans.push_back('o');
                    i += 2;
                }
            }
        }
        return ans;
    }
};

// T2 每次移除和为k的一对数
// 最多有多少对数的和为k
// 哈希
class Solution {
public:
    int maxOperations(vector<int>& nums, int k) {
        unordered_map<int, int> um;
        unordered_map<int, bool> is_vis;
        int n = nums.size(), ans = 0;
        for (const auto &i : nums) ++um[i];
        for (const auto &i : um) {
            if (um.find(k - i.first) != um.end()) {
                if(!is_vis[i.first] && !is_vis[k - i.first]){
                if(i.first * 2 == k) {
                    ans += i.second / 2;
                    is_vis[i.first] = is_vis[k - i.first] = true;
                    continue;
                }
                ans += min(i.second, um[k - i.first]);
                is_vis[i.first] = is_vis[k - i.first] = true;
                }
            }
        }
        return ans;
    }
};

// T3 模拟
class Solution {
public:
    int concatenatedBinary(int n) {
        string res;
        for (int i = n; i >= 1; --i) {
            int j = i;
            while(j) {
                res.push_back(j & 1 ? '1' : '0');
                j >>= 1;
            }
        }
        reverse(res.begin(), res.end());
        // cout << res << '\n';
        long long ans = 0;
        int r = 0;
        for (int i = res.size() - 1; i >= 0; --i) {
            ans += (res[i] - '0') * (long long)pow(2, r++);
        }
        return ans % (1000000000 + 7);
    }
};