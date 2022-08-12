#include <bits/stdc++.h>
using namespace std;

// T1
class Solution {
public:
    int maxDepth(string s) {
        stack<char> st;
        size_t ans = 0;
        for(int i = 0; i < s.size(); ++i)
        {
            if(s[i] == '(') st.push(s[i]);
            if(s[i] == ')')
            {
                ans = max(ans, st.size());
                st.pop();
            }
        }
        return ans;
    }
};

// T2
class Solution {
public:
    int maximalNetworkRank(int n, vector<vector<int>>& roads) 
    {
        vector<int> g(n, 0);
        vector<vector<bool>> graph(n, vector<bool>(n, false));
        int ans = 0;
        for(auto i : roads)
        {
            int s = i[0], e = i[1];
            graph[s][e] = graph[e][s] = true;
            ++g[s], ++g[e];
        }
        for(int i = 0; i < n; ++i)
        {
            for(int j = i + 1; j < n; ++j)
            {
                int temp = g[i] + g[j];
                if(graph[i][j] == true) --temp;
                ans = max(temp, ans);
            }
        }
        return ans;
    }
};

// T3
// 分割两个字符串，判断分割完后两个部分拼接是否能构成回文， 可以分割成空串

class Solution {
public:
    // 如果两者中有一个回文，则必然可以
    bool is_P(const string &s)
    {
        for(int i = 0, j = s.size() - 1; i < j; ++i, --j)
        {
            if(s[i] != s[j]) return false;
        }
        return true;
    }

    bool checkPalindromeFormation(string a, string b) {
        if(is_P(a) || is_P(b)) return true;
        // 接下来进行分割
        return a[0] == b.back() || a.back() == b[0]; 
    }
};

// T4
// 最大距离即每棵子树中节点的最远距离，树形动态规划
// 先统计树的高度以及每一层高度对应的节点数目
// 1 = 1
// 2 = 1 + 1 = 2 + 0
// 3 = 1 + 2 = 3 + 0
// 先建树，选择一个入度为0的节点作为根节点
// 假设给的数据很好，第一个数是根节点
// Nope，不对
class Solution {
    vector<int> height;
public:
    vector<int> countSubgraphsForEachDiameter(int n, vector<vector<int>>& edges) {
        // 统计入度
        int root = edges[0][0];
        vector<int> ans;
        vector<vector<int>> g(n, vector<int>(n, 0));
        for(auto i : edges)
        {
            int s = i[0], e = i[1];
            g[s][e] = g[e][s] = 1;
        }
        // 遍历这棵树，得到每一层高度对应的数目
        bfs(root, n, g);
        for(int i = 1; i <= n - 1; ++i)
        {

        }
    }

    void bfs(int s, int n, vector<vector<int>> g)
    {
        vector<bool> vis(n, false);
        queue<int> q;
        vis[s] = true;
        q.push(s);
        while(!q.empty())
        {   
            int cSize = q.size(); // 每一层
            height.emplace_back(cSize);
            for(int j = 0; j < cSize; ++j)
            {
                int temp = q.front();
                q.pop();
                for(int i = 0; i < g[temp].size(); ++i)
                {
                    if(vis[g[temp][i]] == false)
                    {
                        q.push(g[temp][i]);
                        vis[g[temp][i]] = true;
                    }
                }
            }  
        }
    }
};