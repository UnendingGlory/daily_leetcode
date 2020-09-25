#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int ans = INT_MIN;
        for(int i = 0; i < nums.size(); ++i)
            for(int j = i + 1; j < nums.size(); ++j)
                ans = max(ans, (nums[i] - 1) * (nums[j] - 1));
        return ans;
    }
};

class Solution {
public:
    int maxArea(int h, int w, vector<int>& a, vector<int>& v) {
        const int mod = 1e9 + 7;
        vector<long long> hd, wd; // 高差，宽差
        a.push_back(0), v.push_back(0);
        a.push_back(h), v.push_back(w);
        sort(a.begin(), a.end());
        sort(v.begin(), v.end());
        for(int i = 1; i < a.size(); ++i) hd.push_back(a[i] - a[i - 1]);
        for(int i = 1; i < v.size(); ++i) wd.push_back(v[i] - v[i - 1]);
        long long maxh = *max_element(hd.begin(), hd.end());
        long long maxw = *max_element(wd.begin(), wd.end());
        return (long long)(maxh * maxw) % mod;
    }
};

class Solution {
public:
    vector<bool> vis;
    vector<vector<int>> g;
    int ans = 0;

    void dfs(int cur)
    {
        vis[cur] = true;
        for(int i = 0; i < g[cur].size(); ++i)
        {
            if(vis[g[cur][i]] == false)
            {
                dfs(g[cur][i]);
                ++ans;
            }
        }
    }

    int minReorder(int n, vector<vector<int>>& c) {
        vis.resize(n);
        g.resize(n);
        vis[0] = true;
        for(auto i : c)
        {
            if(i[1] == 0) vis[i[0]] = true;
            g[i[0]].push_back(i[1]);
        }
        for(int i = 0; i < vis.size(); ++i)
        {
            for(int j = 0; j < g[i].size(); ++j)
            {
                // 如果领接表中有可以达到0的，则其也可以达到0
                if(vis[g[i][j]] == true) vis[i] = true;
            }
            //cout << i << " " << vis[i] << endl;
            if(vis[i] == true) dfs(i);
        }
        return ans;
    }
};