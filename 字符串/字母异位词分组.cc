#include "../header.h"

// Solution 1
// 排序
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;
        for (const auto &str : strs) {
            string key = str;
            sort(key.begin(), key.end());
            groups[key].emplace_back(str);
        }
        vector<vector<string>> ans;
        for (const auto &str : groups) {
            ans.push_back(str.second);
        }
        return ans;
    }
};

// Solution 2
// 复杂设计
// 将计数数组作为键，vector<string>作为值
// 如果用unordered_map，键值不是兼容类型则需要自己设计hash函数
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // 奇奇怪怪的hash函数设计
        auto my_hash = [fn = hash<int>{}] (const array<int, 26> &a)->size_t {
            return std::accumulate(a.begin(), a.end(), 0, [&](size_t acc, int num) {
                return (acc << 1) ^ fn(num);
            });
        };
        unordered_map<array<int, 26>, vector<string>, decltype(my_hash)> groups(0, my_hash);
        for (const auto & str : strs) {
            array<int, 26> counts{0};
            for (char i : str) {
                ++counts[i - 'a'];
            }
            groups[counts].emplace_back(str);
        }
        vector<vector<string>> ans;
        for (const auto &g : groups) {
            ans.push_back(g.second);
        }
        return ans;
    }
};