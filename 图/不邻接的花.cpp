#include <bits/stdc++.h>
using namespace std;

// 一开始理解错题意。。写了个并查集没过
// 只是简单的考察图的数据结构==
class Solution {
public:
    vector<int> gardenNoAdj(int N, vector<vector<int>>& paths) {
        vector<vector<int>> g(N + 1);
        int type[N + 1];
        memset(type, 0, sizeof(type));
        for(auto i : paths)
        {
            g[i[0]].push_back(i[1]);
            g[i[1]].push_back(i[0]);
        }
        vector<int> ans;
        for(int i = 1; i <= N; ++i)
        {
            for(int j = 1; j <= 4; ++j)
            {
                bool vis = false;
                for(int k = 0; k < g[i].size(); ++k)
                    if(type[g[i][k]] == j) // 顺序挑选
                    {
                        vis = true;
                        break;
                    }
                if(!vis)
                {
                    type[i] = j;
                    ans.push_back(j);
                    break;
                }
            }
        }
        return ans;
    }
};

int main()
{
    return 0;
}