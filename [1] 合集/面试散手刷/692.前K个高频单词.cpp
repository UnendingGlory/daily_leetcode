#include "header.h"
// 给定一个单词列表 words 和一个整数 k ，返回前 k 个出现次数最多的单词。
// 返回的答案应该按单词出现频率由高到低排序。如果不同的单词有相同出现频率， 按字典顺序 排序。
// 尝试以 O(n log k) 时间复杂度和 O(n) 空间复杂度解决。

// 该题类似于前 K个数，不同的是将数字变成了字符串。
// 因此需要按照字符串出现的次数进行排序，统计次数后直接遍历哈希表。
// 对于C++中的优先级队列，需要自定义比较函数。
// 声明一个小根堆，堆顶的出现次数最少。
// 排序相反，因此字典序小的放在后面，出现次数大的也放在后面。
class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> hashtable;
        for (string &s: words) {
            hashtable[s]++;
        }

        // 按照出现次数从大到小排序，自定义匿名比较函数，自定义比较函数的大小次序是相反的。
        // 使用传入捕获的方式不行，无法捕获到 hashtable对象。
        // function<return type(args ...)>;
        using Compare = function<bool(const pair<string, int> &, const pair<string, int> &)>;
        Compare cmp = [](const pair<string, int> &a, const pair<string, int> &b) {
            return a.second == b.second ? a.first < b.first : a.second > b.second;
        };
        priority_queue<pair<string, int>, vector<pair<string, int>>, Compare> pq(cmp);
        // 直接遍历哈希表
        for (auto &kv: hashtable) {
            pq.emplace(kv);
            if (pq.size() > k) {
                pq.pop();
            }
        }
        // 反向输出答案。
        vector<string> ans(k);
        for (int i = k - 1; i >= 0; --i) {
            ans[i] = pq.top().first;
            pq.pop();
        }
        return ans;
    }
};

int main() {
    vector<string> vec {"i", "love", "leetcode", "i", "love", "coding"};
    int k = 2;
    Solution s;
    s.topKFrequent(vec, k);
    return 0;
}