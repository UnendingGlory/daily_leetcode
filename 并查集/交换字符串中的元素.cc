#include "../header.h"

// 给定一个字符串和能交换的下标
// 输出最小字典序的字符串
// 并查集
// 对于每一个联通子图，塞到一个vector中sort
// 最后根据father节点写入结果

class UnionSet {
private:
    vector<int> father;

public:
    UnionSet(int n) {
        father.resize(n);
        for (int i = 0; i < n; ++i) {
            father[i] = i;
        }
    }

    int find(int x) {
        int z = x;
        while (x != father[x]) x = father[x];
        // 路径压缩
        while (z != father[z]) {
            int father_z = father[z];
            father[z] = x;
            z = father_z;
        }
        return x;
    }

    void union_ab(int a, int b) {
        int father_a = find(a), father_b = find(b);
        if (father_a != father_b) {
            father[father_a] = father_b;
        }
    }
};

class Solution {
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int n = s.size();
        UnionSet us(n);
        for (const auto& pair : pairs) {
            us.union_ab(pair[0], pair[1]);
        }
        vector<string> graph(n);
        for (int i = 0; i < n; ++i) {
            graph[us.find(i)].push_back(s[i]);
        }
        for (int i = 0; i < n; ++i) {
            // 从大到小排序，方便后面写入结果
            sort(graph[i].begin(), graph[i].end(), greater<char>());
        }
        string ans;
        for (int i = 0; i < n; ++i) {
            int root = us.find(i);
            ans.push_back(graph[root].back());
            graph[root].pop_back();
        }
        return ans;
    }
};