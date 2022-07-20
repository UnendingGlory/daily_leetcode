#include "header.h"

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ans;
        int r = matrix.size();
        if (r == 0) return ans;
        int c = matrix[0].size(), x = 0, y = 0, n = r * c, cnt = 0;
        vector<vector<bool>> vis(r, vector<bool>(c, false));
        ans.emplace_back(matrix[0][0]);
        vis[0][0] = true;
        while (cnt < n) {
            while (y + 1 < c && !vis[x][y + 1]) { // 先往右
                ans.emplace_back(matrix[x][++y]), vis[x][y] = true, ++cnt;
            }
            while (x + 1 < r && !vis[x + 1][y]) { // 再往下
                ans.emplace_back(matrix[++x][y]), vis[x][y] = true, ++cnt;
            }
            while (x - 1 >= 0 && !vis[x - 1][y]) { // 再往左
                ans.emplace_back(matrix[--x][y]), vis[x][y] = true, ++cnt;
            }
            while (y - 1 >= 0 && !vis[x][y - 1]) { // 再向上
                ans.emplace_back(matrix[x][--y]), vis[x][y] = true, ++cnt;
            }
        }
        return ans;
    }
};