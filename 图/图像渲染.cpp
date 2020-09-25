#include <bits/stdc++.h>
using namespace std;

// BFS
class Solution {
    int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) 
    {
        int row = image.size(), colomn = image[0].size(), raw = image[sr][sc];
        bool vis[row][colomn];
        memset(vis, 0, sizeof(vis));
        queue<pair<int, int>> q;
        q.push({sr, sc});
        while(!q.empty())
        {
            auto temp = q.front();
            q.pop();
            int x = temp.first, y = temp.second;
            vis[x][y] = true;
            image[x][y] = newColor;
            for(int i = 0; i < 4; ++i)
            {
                int newX = x + dx[i], newY = y + dy[i];
                if(newX >= 0 && newX < row && newY >= 0 && newY < colomn && !vis[newX][newY] && image[newX][newY] == raw)
                {
                    q.push({newX, newY});
                    vis[newX][newY] = true;
                }
            }
        }
        return image;
    }
};