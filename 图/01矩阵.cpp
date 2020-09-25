#include <bits/stdc++.h>
using namespace std;

// 多源BFS，从0开始BFS
class Solution {
public:
    // 感觉可以dp
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        int row = matrix.size(), col = matrix[0].size();
        int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
        vector<vector<int>> ans(row);
        for(int i = 0; i < row; ++i) ans[i].resize(col);
        bool vis[row][col];
        // 每一个元素都要BFS
        for(int i = 0; i < row; ++i)
            for(int j = 0; j < col; ++j)
            {
                if(matrix[i][j] == 0)
                {
                    ans[i][j] = 0;
                    continue;
                }
                int asw = 0;
                memset(vis, 0, sizeof(vis));
                queue<pair<int, int>>q;
                q.push({i, j});
                vis[i][j] = true;
                while(!q.empty())
                {
                    auto temp = q.front();
                    q.pop();
                    if(matrix[temp.first][temp.second] == 0)
                    {
                        ans[i][j] = abs(temp.first - i) + abs(temp.second - j);
                        break;
                    }
                    for(int k = 0; k < 4; ++k)
                    {
                        int newI = temp.first + dx[k], newJ = temp.second + dy[k];
                        if(newI >= 0 && newI < row && newJ >= 0 && newJ < col && !vis[newI][newJ])
                        {
                            q.push({newI, newJ});
                            vis[newI][newJ] = true;
                        }
                    }
                }
            }
        return ans;
    }
};

// dp做法，dp[i][j]代表到最近的0
// 从0位置开始，0位置的dp[i][j] = 0
// 其他位置的dp[i][j] = min(dp[四个方向]) + 1
// 先规定两个方向，再计算另外两个方向
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {                
        int r = matrix.size(), c = matrix[0].size();
        vector<vector<int>> dist(r, vector<int>(c, INT_MAX - 10000));        
        //1. 从上到下，从左到右遍历矩阵,计算的是左上的，更新好右下的值
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (matrix[i][j] == 0) {
                    dist[i][j] = 0;                    
                } else {
                    if (i > 0) dist[i][j] = min(dist[i][j], dist[i - 1][j] + 1);
                    if (j > 0) dist[i][j] = min(dist[i][j], dist[i][j - 1] + 1);
                }                
            }
        }        
        //2. 从下到上，从右到左遍历，计算的是右下的，更新好左上的值
        for (int i = r - 1; i >= 0; --i) {
            for (int j = c - 1; j >= 0; --j) {
                if (i < r - 1) dist[i][j] = min(dist[i][j], dist[i + 1][j] + 1);
                if (j < c - 1) dist[i][j] = min(dist[i][j], dist[i][j + 1] + 1);
            }
        }
        return dist;
    }
};