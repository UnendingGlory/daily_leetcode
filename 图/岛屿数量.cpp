#include <bits/stdc++.h>
using namespace std;

// BFS或者并查集
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int row = grid.size(), col = grid.size(), ans = 0;
        if(row == 0) return 0;
        int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
        bool vis[row][col];
        memset(vis, 0, sizeof(vis));
        for(int i = 0; i < row; ++i)
        {
            for(int j = 0; j < col; ++j)
            {
                if(grid[i][j] == '1' && vis[i][j] == false)
                {
                    // bfs beginning
                    ++ans;
                    queue<pair<int, int>> q;
                    q.push({i, j});
                    vis[i][j] = true;
                    while(!q.empty())
                    {
                        auto temp = q.front();
                        q.pop();
                        for(int k = 0; k < 4; ++k)
                        {
                            int newI = temp.first + dx[k], newJ = temp.second + dy[k];
                            if(newI >= 0 && newI < row && newJ >= 0 && newJ < col && grid[newI][newJ] == '1' && vis[newI][newJ] == false)
                            {
                                q.push({newI, newJ});
                                vis[newI][newJ] = true;
                            }
                        }
                    }
                }
            }
        }
        return ans;
    }
};