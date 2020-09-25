#include <bits/stdc++.h>
using namespace std;

class Solution {
    int row, col;
    int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
    vector<vector<int>> protect;

public:
    void BFS(int i, int j, vector<vector<char>>& board)
    {
        queue<pair<int, int>> q;
        q.push(make_pair(i, j));
        // 从边界开始，按照代码逻辑，边界没必要保护
        while(!q.empty())
        {
            auto next = q.front();
            q.pop();
            for(int k = 0; k < 4; ++k)
            {
                int I = next.first + dx[k], J = next.second + dy[k];
                // 满足边界条件，且是O，且还未被保护
                if(I >= 1 && I < row - 1 && J >= 1 && J < col - 1 && board[I][J] == 'O' && !protect[I][J])
                {
                    q.push(make_pair(I, J));
                    protect[I][J] = 1;
                }
            }
        }
    }   

    void solve(vector<vector<char>>& board) {
        if(!board.size()) return;
        row = board.size(), col = board[0].size();
        protect.resize(row);
        for(int i = 0; i < row; ++i) 
        {
            protect[i].resize(col);
            fill(protect[i].begin(), protect[i].end(), 0);
        }
        // 先处理边界BFS
        for(int i: {0, row  - 1}) // 上下边界
            for(int j = 0; j < col; ++j)
            {
                if(board[i][j] == 'O' && !protect[i][j]) BFS(i , j, board);
            }
        for(int j:{0, col - 1})
            for(int i = 0; i < row; ++i)
            {
                if(board[i][j] == 'O' && !protect[i][j]) BFS(i , j, board);
            }
        for(int i = 1; i < row - 1; ++i)
            for(int j = 1; j < col - 1; ++j)
                if(board[i][j] == 'O' && !protect[i][j]) // 到这里在内层且未被保护的'O'要被修改
                    board[i][j] = 'X';
    }
};

// 并查集解法
class Solution {
    int row, col;
    int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
    vector<int> father; // 并查集

public:
    int Father(int x)
    {
        int a = x;
        while(x != father[x]) x = father[x];
        // 路径压缩优化查询操作
        while(a != father[a])
        {
            int b = father[a];
            b = x;
            a = b;
        }
        return x;
    }

    void Union(int x, int y)
    {
        int X = Father(x), Y = Father(y);
        if(X != Y) father[X] = Y; // 合并
    }

    void solve(vector<vector<char>>& board) {
        if(!board.size()) return;
        row = board.size(), col = board[0].size();
        father.resize(row * col + 1);
        // 开大一个，下标为row * col，作为所有保护圆点的父亲
        int grandF = row * col;
        for(int i = 0; i < father.size(); ++i) father[i] = i;
        for(int i: {0, row  - 1}) // 上下边界
            for(int j = 0; j < col; ++j)
            {
                if(board[i][j] == 'O') father[i * col + j] = grandF;
            }
        for(int j:{0, col - 1}) // 左右边界
            for(int i = 0; i < row; ++i)
            {
                if(board[i][j] == 'O') father[i * col + j] = grandF;
            }
        for(int i = 1; i < row - 1; ++i)
            for(int j = 1; j < col - 1; ++j)
            {
                if(board[i][j] == 'O')
                {
                    for(int k = 0; k < 4; ++k)
                    {
                        int I = i + dx[k], J = j + dy[k];
                        if(Father(I * col + J) == grandF) Union(i * col + j, I * col + J);
                    }
                }
            }
        for(int i = 1; i < row; ++i)
            for(int j = 1; j < col; ++j)
                if(board[i][j] == 'O' && Father(i * col + j) != grandF)
                    board[i][j] = 'X';
    }
};

int main()
{
    return 0;
}