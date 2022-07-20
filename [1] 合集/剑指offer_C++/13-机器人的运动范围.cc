#include "../header.h"

// DFS + 回溯 || BFS
// 注意求的是数位之和

class Solution {
private:
    int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
    int ans = 0, _m, _n, _k;
public:
    int getSum(int n) {
        int ret = 0;
        while (n)
        {
            ret += (n % 10);
            n /= 10;
        }
        return ret;
    }

    void dfs(int i, int j, vector<vector<bool>>& vis) {
        if (getSum(i) + getSum(j) <= _k) {
            vis[i][j] = true;
            ++ans;
        } else {
            return;
        }
        for (int k = 0; k < 4; ++k) {
            int newX = i + dx[k], newY = j + dy[k];
            if (newX >= 0 && newX < _m && newY >= 0 && newY < _n && !vis[newX][newY]) {
                dfs(newX, newY, vis);
            }
        }
    }

    int movingCount(int m, int n, int k) {
        _m = m, _n = n, _k = k;
        vector<vector<bool>> vis(m, vector<bool>(n));
        dfs(0, 0, vis);
        return ans;
    }
};

// BFS更好
class Solution {
private:
    int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
public:
    int getSum(int n) {
        int ret = 0;
        while (n)
        {
            ret += (n % 10);
            n /= 10;
        }
        return ret;
    }

    int movingCount(int m, int n, int k) {
        int ans = 0;
        vector<vector<bool>> vis(m, vector<bool>(n));
        queue<pair<int, int>> q;
        q.push({0, 0});
        vis[0][0] = true;
        ++ans;
        while (!q.empty()) {
            auto temp = q.front();
            q.pop();
            for (int ind = 0; ind < 4; ++ind) {
                int newX = temp.first + dx[ind], newY = temp.second + dy[ind];
                if (newX >= 0 && newX < m && newY >= 0 && newY < n && !vis[newX][newY]\
                    && getSum(newX) + getSum(newY) <= k) { // 注意是在这里判断
                    ++ans;
                    q.push({newX, newY});
                    vis[newX][newY] = true;
                }
            }
        }
        return ans;
    }
};