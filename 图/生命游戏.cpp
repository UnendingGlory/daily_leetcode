#include <bits/stdc++.h>
using namespace std;

// 开两个二维数组或使用复合状态
class Solution {
public:
    // -1之前是活细胞现在是死细胞，0死细胞，1活细胞，2之前是死细胞现在是活细胞
    void gameOfLife(vector<vector<int>>& board) {
        int dx[8] = {1, 0, -1, 0, 1, -1, 1, -1};
        int dy[8] = {0, 1, 0, -1, 1, -1, -1, 1};
        for(int i = 0; i < board.size(); ++i)
            for(int j = 0; j < board[0].size(); ++j)
            {
                int alive = 0; // 该位置周围的活细胞数
                for(int k = 0; k < 8; ++k)
                {
                    int I = i + dx[k], J = j + dy[k];
                    // 该位置有效
                    if(I >= 0 && I < board.size() && J >= 0 && J < board[0].size())
                    {
                        if(board[I][J] == 1 || board[I][J] == -1) ++alive;
                        if(alive > 3) break;
                    }
                }
                if(board[i][j] == 1 && (alive < 2 || alive > 3)) board[i][j] = -1;
                if(board[i][j] == 0 && alive == 3) board[i][j] = 2;
            }
        for(int i = 0; i < board.size(); ++i)
            for(int j = 0; j < board[0].size(); ++j)
            {
                if(board[i][j] > 0) board[i][j] = 1;
                else board[i][j] = 0;
            }
    }
};

int main()
{
    return 0;
}