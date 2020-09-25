#include <bits/stdc++.h>
using namespace std;
// 先水平翻转再沿对角线翻转

class Solution {
public:
    // 旋转90度，即先水平翻转再沿对角线翻转
    void rotate(vector<vector<int>>& matrix) {
        int row = matrix.size(), col = matrix[0].size();
        // 两边开始
        for(int i = 0, j = row- 1; i < j; ++i, --j)
            for(int k = 0; k < col; ++k)
                swap(matrix[i][k], matrix[j][k]);
        for(int i = 0; i < row; ++i)
            for(int j = i + 1; j < col; ++j)
                    swap(matrix[i][j], matrix[j][i]);
    }
};