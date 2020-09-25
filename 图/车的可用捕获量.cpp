#include <bits/stdc++.h>
using namespace std;

class Solution {
    int a, b; // 白车的位置
    int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
public:
    int numRookCaptures(vector<vector<char>>& board) {
        for(int i = 0; i < 8; ++i)
            for(int j = 0; j < 8; ++j)
                if(board[i][j] == 'R')
                {
                    a = i, b = j;

                    
                    break;
                }       
        int ans = 0;
        for(int i = 0; i < 4; ++i)
        {
            for(int step = 0; ; ++step)
            {
                int newI = a + step * dx[i], newJ = b + step * dy[i];
                if(newI < 0 || newI > 7 || newJ < 0 || newJ > 7 || board[newI][newJ] == 'B') break;
                if(board[newI][newJ] == 'p')
                {
                    ++ans;
                    break;
                }
            }
        }
        return ans;
    }
};