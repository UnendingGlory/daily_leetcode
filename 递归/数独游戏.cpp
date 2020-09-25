#include <bits/stdc++.h>
using namespace std;

// 解数独游戏，使用最基本的递归

class Solution {
private:
    bool row[9][9]; // 第一个维度标志第几行，第二个维度标志数字
    bool col[9][9];
    bool map[3][3][9]; // 3 * 3的宫格，每个位置填入的数字
    bool valid; // 标志该次dfs是否有效
    vector<pair<int, int>> spaces; // 记录空白位置

public:
    // 对每一个空格位置进行dfs
    void dfs(vector<vector<char>>& board, int pos)
    {
        // 到了尽头则有效
        if(pos == spaces.size())
        {
            valid = true;
            return;
        }
        auto i = spaces[pos].first, j = spaces[pos].second;
        // 将1到9填入该空位置
        for(int digit = 0; digit < 9 && valid != true; ++digit)
        {
            // 该行没有该数，则该列没有该数，且3 * 3的宫格中没有该数字
            if(!row[i][digit] && !col[j][digit] && !map[i / 3][j / 3][digit])
            {
                // 将该数填入
                row[i][digit] = col[j][digit] = map[i / 3][j / 3][digit] = true;
                board[i][j] = digit + '0' + 1;
                dfs(board, pos + 1);
                // dfs完毕了要重置，进行回溯
                row[i][digit] = col[j][digit] = map[i / 3][j / 3][digit] = false;
            }
        }
    }

    void solveSudoku(vector<vector<char>>& board) 
    {
        // 先遍历一边数组，并记录空白位置和数字
        memset(row, false, sizeof(row));
        memset(col, false, sizeof(col));
        memset(map, false, sizeof(map));
        valid = false;
        for(int i = 0; i < 9; ++i)
        {
            for(int j = 0; j < 9; ++j)
            {
                if(board[i][j] == '.')
                    spaces.emplace_back(i, j);
                else
                {
                    int digit = board[i][j] - '0' - 1; // 作下标要-1
                    row[i][digit] = col[j][digit] = map[i / 3][j / 3][digit] = true;
                }
            }
        }
        dfs(board, 0);
    }
};