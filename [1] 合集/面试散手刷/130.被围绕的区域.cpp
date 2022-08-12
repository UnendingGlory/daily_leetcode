#include "header.h"

// 给你一个 m x n 的矩阵 board ，由若干字符 'X' 和 'O' ，找到所有被 'X' 围绕的区域，并将这些区域里所有的 'O' 用 'X' 填充。
// 被围绕的区间不会存在于边界上，换句话说，任何边界上的 'O' 都不会被填充为 'X'。
// 任何不在边界上，或不与边界上的 'O' 相连的 'O' 最终都会被填充为 'X'。
// 如果两个元素在水平或垂直方向相邻，则称它们是“相连”的。

// m == board.length
// n == board[i].length
// 1 <= m, n <= 200
// board[i][j] 为 'X' 或 'O'

// Solution: 只要从边界上的 'O'开始 dfs，如果和边界上的 'O'相连则不填充。
// 其他位置均填充即可。
class Solution {
public:
    int row, col;
    int dx[4] = {0, -1, 1, 0};
    int dy[4] = {1, 0, 0, -1};
    void solve(vector<vector<char>>& board) {
        row = board.size(), col = board[0].size();
        // 沿着四个方向走一遍。
        int x = 0, y = 0;
        // 直接在原数组上修改，用值判断，不需要 vis数组。
        while (y < col) {
            if (board[x][y] == 'O') {
                dfs(board, x, y);
            }
            ++y;
        }
        --y, ++x;
        while (x < row) {
            if (board[x][y] == 'O') {
                dfs(board, x, y);
            }
            ++x;
        }
        --x, --y;
        while (y >= 0) {
            if (board[x][y] == 'O') {
                dfs(board, x, y);
            }
            --y;
        }
        ++y, --x;
        while (x > 0) {
            if (board[x][y] == 'O') {
                dfs(board, x, y);
            }
            --x;
        }
        // 修正为结果数组。
        for (x = 0; x < row; ++x) {
            for (y = 0; y < col; ++y) {
                if (board[x][y] == 'O') {
                    board[x][y] = 'X';
                } else if (board[x][y] == '*') {
                    board[x][y] = 'O';
                }
            }
        }
    }
    
    // dfs过程中将与边界相连的 'O'修改为 '*'
    void dfs(vector<vector<char>>& board, int i, int j) {
        board[i][j] = '*';
        for (int k = 0; k < 4; ++k) {
            int x = i + dx[k], y = j + dy[k];
            if (x < row && x >= 0 && y < col && y >= 0 && board[x][y] == 'O') {
                dfs(board, x, y);
            }
        }
    }
};
