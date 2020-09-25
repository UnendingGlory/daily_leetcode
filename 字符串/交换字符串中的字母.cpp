#include <bits/stdc++.h>
using namespace std;

// 并查集

class Solution {
    vector<int> father;
public:
    int findFather(int x)
    {
        int a = x;
        while(x != father[x]) x = father[x];
        // 路径压缩，路径上的均指向根节点
        while(a != father[a])
        {
            int b = father[a];
            father[a] = x;
            a = b;
        }
        return x;
    }

    void Union(int x, int y)
    {
        int X = findFather(x), Y = findFather(y);
        if(X != Y) father[X] = Y;
    }

    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        // 用来存储每一类，会造成一定的空间浪费
        int size = s.size();
        vector<vector<char>> v(size);
        father.resize(size);
        for(int i = 0; i < size; ++i) father[i] = i;
        for(auto i : pairs) Union(i[0], i[1]);
        for(int i = 0; i < size; ++i) v[findFather(i)].push_back(s[i]);
        // 从大到小排序
        for(int i = 0; i < size; ++i) sort(v[i].begin(), v[i].end(), greater<char>());
        string ans;
        for(int i = 0; i < size; ++i)
        {
            int x = findFather(i);
            if(v[x].size())
            {
                ans.push_back(v[x].back());
                v[x].pop_back();
            }
        }
        return ans;
    }
};