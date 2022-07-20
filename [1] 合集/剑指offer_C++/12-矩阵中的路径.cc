#include "header.h"

// 矩阵中是否存在某个路径等于某个单词
// DFS + 回溯
// 从任意一个格子开始
class Solution {
    int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
    int row, col;
    string _word;
public:
    // index为当前下标
    bool dfs(vector<vector<char>>& board, vector<vector<bool>>& vis,\
            int i, int j, int index) 
    {
        if (board[i][j] != _word[index]) return false;
        if (index == _word.size() - 1) return true;
        // 开始dfs
        vis[i][j] = true;
        for (int k = 0; k < 4; ++k) {
            int new_i = dx[k] + i, new_j = dy[k] + j;
            if (new_i >= 0 && new_i < row && new_j >= 0 && new_j < col\
               && !vis[new_i][new_j] && dfs(board, vis, new_i, new_j, index + 1))
            {
                return true;
            }
        }
        // 注意重置
        vis[i][j] = false;
        return false;
    }

    bool exist(vector<vector<char>>& board, string word) {
        _word = word, row = board.size(), col = board[0].size();
        vector<vector<bool>> vis(row, vector<bool>(col));
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if(dfs(board, vis, i, j, 0)) {
                    return true;
                }
            }
        }
        return false;
    }
};