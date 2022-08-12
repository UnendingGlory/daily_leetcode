#include "header.h"

// 给你一个字符串 s，请你去除字符串中重复的字母，使得每个字母只出现一次。
// 需保证 返回结果的字典序最小（要求不能打乱其他字符的相对位置）。
// 输入：s = "bcabc"
// 输出："abc"
// 输入：s = "cbacdcbc"
// 输出："acdb"

// Solution: 与402题类似，贪心 + 单调栈。
// 贪心：想要返回结果字典序最小，重复字母里，应该优先删除前面的。
// 单调栈，栈中元素字典序从栈底到栈顶递增。
// 对于新来的字母 char，如果栈顶元素大于 char，说明需要删除栈顶元素。
// 统计每个字母 c的出现次数 count，取 k = count - 1。
// k即每个字母需要丢弃的个数。
// 从左到右遍历字符，对于每个字符，检查栈顶字符 top是否需要丢弃。
// 每遍历一个字符，该字符数量 -1。
// 如果 top出现的次数 > 1，我们可以选择性的丢弃。
// 如果 top出现的次数 <= 1，则不可以丢弃。
// 但是需要满足两个条件：
// 1. 字母个数至少要 1个。
// 2. 已经加入栈中的字母不能再加入，因此重复的字母在前面。
//    比如对于串 "cdbc"，结果是 "cdb"，第二个 c不能入栈。
// 对于 "bcabc"。
// b入栈，c入栈。
// a，b和c均大于a且不唯一，因此从栈中弹出。
// 此栈直接使用 string模拟。
class Solution {
public:
    string removeDuplicateLetters(string s) {
        string stk;
        // 计数
        unordered_map<char, int> counts, vis;
        for (char c: s) {
            counts[c]++;
        }
        // 遍历 + 单调栈
        for (char c: s) {
            if (!vis[c]) {
                while (!stk.empty() && stk.back() > c && counts[stk.back()] > 0) {
                    // 判断该字符是否重复。
                    // 这里是 > 0，而不是 > 1。
                    // 因为 count[c]--过了，如果 counts > 0，代表有重复的c。
                    if (counts[stk.back()] > 0) {
                        // 由于栈中字母唯一，因此弹出就代表栈中已经不存在该字母。
                        vis[stk.back()] = 0; 
                        stk.pop_back();
                    }
                }
                stk.push_back(c);
                vis[c] = 1;
            }
            counts[c]--; // 该字符遍历过了，数量-1
        }
        return stk;
    }
};
