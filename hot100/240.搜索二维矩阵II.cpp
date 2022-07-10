#include "header.h"

// matrix 中每行从左到右升序，每列丛上到下升序，搜索目标 target是否存在。

// Solution1: 暴力搜索。
// 没有利用数组有序的性质。
// 时间复杂度：O(mn)，会超时
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int row = matrix.size(), col = matrix[0].size();
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (target == matrix[i][j]) {
                    return true;
                }
            }
        }
        return false;
    }
};

// Solution2: 二分查找，对每一行进行二分。
// 但这样没有使用到每一列也是有序的性质。
// 时间复杂度：O(mlogn)
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int row = matrix.size(), col = matrix[0].size();
        for (int i = 0; i < row; ++i) {
            int l = 0, r = col - 1;
            while (l < r) {
                int mid = l + ((r - l) >> 1);
                if (matrix[i][mid] == target) {
                    return true;
                } else if (matrix[i][mid] > target) {
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
        }
        return false;
    }
};

// Solution3: 如何利用每一列也是有序的性质呢？
// 从矩阵右上角 (0, n-1) 开始查找，行从右到左，列从上到下假设当前下标为(x, y)，分三种情况。
// matrix[x][y] == target，直接返回 True。
// matrix[x][y] > target，由于每一列是递增的，因此 y 所在的列的下方元素全部大于 target，--y。
// matrix[x][y] < target，由于每一行是递增的，因此 x 所在的行的左方元素全部小于 target，++x。
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        int x = 0, y = n - 1;
        while (x < m && y >= 0) {
            int cur = matrix[x][y];
            if (cur == target) {
                return true;
            } else if (cur > target) {
                --y;
            } else {
                ++x;
            }
        }
        return false;
    }
};
