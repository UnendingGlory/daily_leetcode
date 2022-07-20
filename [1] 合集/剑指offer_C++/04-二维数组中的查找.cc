#include "header.h"

// 首先从数组的右上角开始找。
// 充分利用每行每列均递增的性质。
// 如果该数字大于要查找的数字，则删除该列，向左查找。
// 如果该数字小于要查找的数字，则删除该行，向下查找。

class Solution {
public:
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        int row = matrix.size();
        if (row == 0) return false;
        int col = matrix[0].size(), i = 0, j = col - 1;
        while (i < row && j >= 0) {
            int cur = matrix[i][j];
            if (cur == target) {
                return true;
            }
            else if (cur > target) {
                --j;
            }
            else {
                ++i;
            }
        }
        return false;
    }
};