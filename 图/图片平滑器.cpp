#include "header.h"

class Solution {
    int r, c;
    vector<pair<int, int>> v{{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, -1}, {-1, 1}, {1, 1}, {-1, -1}};
    // int dx[9] = {1, 0, -1, 0, 1, 1, -1, -1}, dy[9] = {0, 1, 0, -1, -1, 1, 1, -1};
public:
    int smoothKernel(vector<vector<int>>& img, int x, int y) {
        // 以(i, j)为中心计算

        int cnt = 1, sum = img[x][y]; // 计算个数
        for (int i = 0; i < 8; ++i) {
            int newx = x + v[i].first, newy = y + v[i].second;
            if (newx >= 0 && newx < r && newy >= 0 && newy < c) {
                ++cnt;
                sum += img[newx][newy];
            }
        }
        return floor((1.0 * sum) / cnt);
    }

    vector<vector<int>> imageSmoother(vector<vector<int>>& img) {
        // 类似于卷积
        r = img.size();
        if (r == 0) return {};
        c = img[0].size();
        vector<vector<int>> ans;
        for (int i = 0; i < r; ++i) {
            vector<int> tmp;
            for (int j = 0; j < c; ++j) {
                tmp.emplace_back(smoothKernel(img, i, j));
            }
            ans.emplace_back(tmp);
        }
        return ans;
    }
};
