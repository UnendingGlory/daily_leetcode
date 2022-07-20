#include "header.h"

// Solution1 哈希表, O(2n)
class Solution {
public:
    char firstUniqChar(string s) {
        unordered_map<char, int> has;
        for (char c: s) {
            ++has[c];
        }
        for (char c: s) {
            if (has[c] == 1) {
                return c;
            }
        }
    }
};

// Solution2 有序哈希表，O(n+26)
// 使用一个vector存储哈希表的插入顺序
class Solution {
public:
    char firstUniqChar(string s) {
        vector<char> keys;
        unordered_map<char, bool> has; // 是否是第一次出现
        for (char c: s) {
            if (has.find(c) == has.end()) {
                keys.emplace_back(c);
                has[c] = true;
            } else { // 不是第一次出现
                has[c] = false; 
            }
        }
        for (char c: keys) {
            if (has[c] == 1) {
                return c;
            }
        }
        return ' ';
    }
};
