#include <bits/stdc++.h>
using namespace std;

class Solution1 {
public:
    bool canBeEqual(vector<int>& target, vector<int>& arr) {
        unordered_map<int, int> s1, s2;
        for(auto i : target) ++s1[i];
        for(auto i : arr) ++s2[i];
        return s1 == s2;
    }
};

// 长度为k的二进制串都是其子串
class Solution {
public:
    bool hasAllCodes(string s, int k) {
        unordered_map<int, bool> m;
        for(int i = 0; i + k <= s.size(); ++i)
        {
            string sub = s.substr(i, k);
            int sum = 0, d = 1; // 乘基加权
            for(int j = sub.size() - 1; j >= 0; j--)
            {
                sum += (sub[j] - '0') * d;
                d <<= 1;
            }
            //cout << sum << endl;
            m[sum] = true;
        }
        for(int i = 0; i < (int)pow(2, k) ; ++i)
            if(m[i] == false)
                return false;
        return true;
    }
};

// 即能否通过图搜到，直接dfs超时，设置标志位dfs ac
class Solution {

public:
    vector<bool> ans, vis;
    vector<vector<int>> g;
    bool flag;

    void dfs(int cur, int d)
    {
        vis[cur] = true;
        if(cur == d)
        {
            flag = true;
            return;
        }
        if(flag) return;
        for(int i = 0; i < g[cur].size(); ++i)
            if(vis[g[cur][i]] == false) // 设置访问位剪枝
                dfs(g[cur][i], d);
    }

    vector<bool> checkIfPrerequisite(int n, vector<vector<int>>& p, vector<vector<int>>& q) {
        g.resize(n);
        vis.resize(n);
        for(auto i : p)
        {
            g[i[0]].push_back(i[1]);
        }
        for(auto i : q)
        {
            fill(vis.begin(), vis.end(), false);
            flag = false;
            dfs(i[0], i[1]);
            if(!flag) ans.push_back(false);
            else ans.push_back(true);
        }
        return ans;
    }
};

int main()
{
    Solution a;
    //cout << a.hasAllCodes("00110", 2) << endl;
    return 0;
}