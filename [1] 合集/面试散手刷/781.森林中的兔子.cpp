#include "header.h"
// 森林中有未知数量的兔子。提问其中若干只兔子 "还有多少只兔子与你（指被提问的兔子）颜色相同?" ，
// 将答案收集到一个整数数组 answers中，其中 answers[i]是第 i只兔子的回答。
// 给你数组 answers，返回森林中兔子的最少数量。

// 输入：answers = [1,1,2]
// 输出：5
// 解释：两只回答了 "1"的兔子可能有相同的颜色，设为红色。 
// 之后回答了 "2"的兔子不会是红色，否则他们的回答会相互矛盾。
// 设回答了 "2"的兔子为蓝色。 
// 此外，森林中还应有另外 2只蓝色兔子的回答没有包含在数组中。 
// 因此森林中兔子的最少数量是 5只：3只回答的和 2只没有回答的。

// Solution: 贪心。
// 对于数字 10，最多有 11只兔子可以回答 10，超过了 11，那么就要分为第二组。
// 一般地，如果有 x只兔子都回答了 y， 那么每一组最多有 y+1只兔子。
// 所以共有 ceil[x / (y+1)] 种颜色，且每种颜色都有 y+1只兔子。
// 该映射最多就有 ceil[x /(y+1)] * (y + 1)只兔子。
class Solution {
public:
    int numRabbits(vector<int>& answers) {
        unordered_map<int, int> cnt;
        for (auto &ans: answers) {
            cnt[ans]++;
        }
        int ans = 0;
        for (auto &kv: cnt) {
            int x = kv.second, y = kv.first;
            // 整数(x + y) / (y + 1)等同于 x / (y + 1)向上取整
            ans += ((x + y) / (y + 1)) * (y + 1);
        }
        return ans;
    }
};
