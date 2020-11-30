#include "header.h"

// 首先统计一遍字符串，如果最多的字符数小于(n + 1) / 2，则无解
// 对于有解的情况，使用贪心+最大堆
// 堆中存储的是每个字符的出现次数以及每个字符
// 只要堆中元素大于 > 1，就从堆中拿出堆顶的两个元素加入结果
// 然后将这两个元素的次数-1，再加入堆中

class Solution {
public:
    string reorganizeString(string S) {
        int n = S.size(), cnt[26] = {0}, max_count = 0;
        string ans = "";
        // 由于题目规定了是小写字母，因此没必要用map
        for(const auto &i : S)
        {
            ++cnt[i - 'a'];
            max_count = max(max_count, cnt[i - 'a']);
        }
        if(max_count > ((n + 1) >> 1)) return ans;
        // pair先比较第一元素，且在此题下保证第二类型char各不相同
        // 也可以存char，然后自定义char的比较按照cnt来进行
        priority_queue<pair<int, char>, vector<pair<int, char>>> pq;
        for (char c = 'a'; c <= 'z'; ++c)
        {
            if(cnt[c - 'a'] > 0)
                pq.push({cnt[c - 'a'], c});
        }
        while (pq.size() > 1)
        {
            auto top_c1 = pq.top().second; pq.pop();
            auto top_c2 = pq.top().second; pq.pop();
            ans.push_back(top_c1); ans.push_back(top_c2);
            if(--cnt[top_c1 - 'a'] > 0) pq.push({cnt[top_c1 - 'a'], top_c1});
            if(--cnt[top_c2 - 'a'] > 0) pq.push({cnt[top_c2 - 'a'], top_c2});
        }
        if (!pq.empty())
        {
            char end = pq.top().second;
            ans.push_back(end);
        }
        return ans;
    }
};

class Solution {
public:
    string reorganizeString(string S) {
        int n = S.size(), cnt[26] = {0}, max_count = 0;
        string ans = "";
        // 由于题目规定了是小写字母，因此没必要用map
        for(const auto &i : S)
        {
            ++cnt[i - 'a'];
            max_count = max(max_count, cnt[i - 'a']);
        }
        if(max_count > ((n + 1) >> 1)) return ans;
        // pq存char，然后自定义char的比较按照cnt来进行
        // 由于pq里需要修改cnt，所以捕捉应该用引用的方式捕获
        auto cmp = [&cnt](const char &a, const char &b){
            // 大的放前面，需要值捕获，且如果想要是大顶堆，应该是<
            return cnt[a - 'a'] < cnt[b - 'a'];
        };
        priority_queue<char, vector<char>, decltype(cmp)> pq{cmp};
        for (char c = 'a'; c <= 'z'; ++c)
        {
            if(cnt[c - 'a'] > 0)
                pq.push(c);
        }
        while (pq.size() > 1)
        {
            char top_c1 = pq.top(); pq.pop();
            char top_c2 = pq.top(); pq.pop();
            ans.push_back(top_c1); ans.push_back(top_c2);
            if(--cnt[top_c1 - 'a'] > 0) pq.push(top_c1);
            if(--cnt[top_c2 - 'a'] > 0) pq.push(top_c2);
        }
        if (!pq.empty())
        {
            char end = pq.top();
            ans.push_back(end);
        }
        return ans;
    }
};