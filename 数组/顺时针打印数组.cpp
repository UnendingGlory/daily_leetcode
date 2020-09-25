#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ans;
        if(matrix.size() == 0) return ans;
        int r = matrix.size(), c = matrix[0].size();
        int n = r * c,  k = 1; // k用来计数，n为个数
        bool vis[r][c]; // 标志数组
        int x = 0, y = 0; // 一开始从左上角开始
        memset(vis, 0, sizeof(vis));
        ans.push_back(matrix[0][0]), vis[0][0] = true; // 将第一个数打入
        while(k < n)
        {
            while(y + 1 < c && !vis[x][y + 1]) ans.push_back(matrix[x][++y]), vis[x][y] = true, ++k;
            while(x + 1 < r && !vis[x + 1][y]) ans.push_back(matrix[++x][y]), vis[x][y] = true, ++k;
            while(y - 1 >= 0 && !vis[x][y - 1]) ans.push_back(matrix[x][--y]), vis[x][y] = true, ++k;
            while(x - 1 >= 0 && !vis[x - 1][y]) ans.push_back(matrix[--x][y]), vis[x][y] = true, ++k;
        }
        return ans;
    }
};