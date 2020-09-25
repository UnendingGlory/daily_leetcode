#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
    int row, col;
    // 位置 + 当前下标
    bool check(vector<vector<char>>&board, vector<vector<bool>>&vis ,string word, int i, int j, int k)
    {
        if(board[i][j] != word[k]) return false;
        // 如果k == word.size() - 1且通过了上一行的检测，则一定为true
        if(k == word.size() - 1) return true;
        vis[i][j] = true;
        bool result = false;
        for(int ss = 0; ss < 4; ++ss)
        {
            int newi = i + dx[ss], newj = j + dy[ss];
            if(newi >= 0 && newi < row && newj >= 0 && newj < col && !vis[newi][newj])
            {
                if(check(board, vis, word, newi, newj, k + 1))
                    return true;
            }
        }
        // 如果是false需要重置
        vis[i][j] = false;
        return false;
    }

    bool exist(vector<vector<char>>& board, string word) 
    {
        row = board.size(), col = board[0].size();
        vector<vector<bool>> vis(row, vector<bool>(col));
        for(int i = 0; i < row; ++i)
            for(int j = 0; j < col; ++j)
            {
                if(check(board, vis, word, i, j, 0)) return true;
            }
        return false;
    }
};