#include "header.h"

// 求解矩阵中的最大矩形
// 最暴力的解法
// 对于每一个长度和每一个宽度都检查是不是1
// 时间复杂度为O(m^2*n^2)
// 降低一层时间复杂度：
// 对于矩阵中的每一个点，先计算出左侧连续1的个数（包括自己），假设是left[i][j]
// 再对于矩阵中每一个点，矩阵对应的最大宽度就是min(left[0][j]...left[i][j])
// 矩阵最大面积即(i - k + 1) * min(left[0][j]...left[i][j])

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if(matrix.size() == 0) return 0;
        int row = matrix.size(), col = matrix[0].size();
        vector<vector<int>> left(row, vector<int>(col, 0));
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (matrix[i][j] == '1') {
                    left[i][j] = (j ? (left[i][j - 1] + 1) : 1);
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (matrix[i][j] == '0') {
                    continue;
                }
                int maxWidth = left[i][j];
                int area = maxWidth;
                for (int k = i - 1; k >= 0; --k) {
                    maxWidth = min(maxWidth, left[k][j]);
                    area = max(area, (i - k + 1) * maxWidth);
                }
                ans = max(ans, area);
            }
        }
        return ans;
    }
};