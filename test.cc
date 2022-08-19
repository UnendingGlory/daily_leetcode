#include "header.h"

class Solution {
public:
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, -1, 0, 1};
    int maxDistance(vector<vector<int>>& grid) {
        int row = grid.size(), col = grid[0].size();
        queue<pair<int, int>> q;

        // 先将所有的陆地入队
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (grid[i][j] == 1) {
                    q.push({i, j});
                }
            }
        }

        // 从每个陆地开始，一圈圈遍历海洋，最后遍历到的海洋就是离陆地最远的海洋
        int x, y;
        bool hasOcean = false;
        pair<int, int> point = nullptr;
        while (!q.empty()) {
            point = q.top();
            q.pop();
            // 将四周的海洋入队
            for (int i = 0; i < 4; ++i) {
                x = point.first + dx[i];
                y = point.second + dy[i];
                if (x < 0 || x >= row || y < 0 || y >= col || grid[x][y] != 0) {
                    continue;
                }
                // 直接修改原数组避免了设置访问数组
                grid[x][y] = grid[point.first][point.second] + 1;
                hasOcean = true;
                q.push({x, y});
            }
        }

        // 没有陆地或者海洋
        if (point == nullptr || !hasOcean) {
            return -1;
        }
        
        // 返回最后一次遍历到海洋的距离
        return grid[point.first][point.second] - 1;
    }
};

void dijkstra(int s) {
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < n; ++i) {
        d[i] = INF;
    }
    d[s] = 0;
    using pii = pair<int, int>;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, s});
    while (!pq.empty()) {
        pii x = pq.top();
        pq.pop();
        int u = x.first;
        if (vis[u]) { // 该结点已访问过
            continue;
        }
        vis[u] = true;
        for (int j = 0; j < adj[u].size(); ++j) {
            int v = adj[u][j].v;
            if (d[u] + adj[u][v].dis < d[v]) {
                d[v] = d[u] + adj[u][v].dis;
                pq.push({d[v], v}); // 能访问到的结点入队
                // father[v] = u;
            }
        }
    }
}

bool Bellman(int s) {
    for (int i = 0; i < n; ++i) {
        d[i] = INF;
    }
    d[s] = 0;
    memset(inq, false, sizeof(q)); // 结点是否已经在队列中
    memset(cnt, 0, sizeof(cnt)); // 每个结点入队的次数
    queue<int> Q;
    Q.push(s);
    inq[s] = true;
    cnt[s]++;
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        inq[u] = false; // 出队了
        // 遍历 u的所有邻接边
        for (int j = 0; j < Adj[u].size(); ++j) {
            int v = Adj[u][j].v;
            int dis = Adj[u][j].dis;
            if (d[u] + dis < d[v]) {
                d[v] = d[u] + dis;
                if (!inq[v]) {
                    Q.push(v);
                    if (++cnt[v] > n - 1) {
                        return false;
                    }
                    inq[v] = true;
                }
            }
        }
    }
    return true;
}

void Floyd() {
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dis[i][k] != INF && dis[k][j] != INF) {
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
                }
            }
        }
    } 
}

// Solution2：优化
class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> pre(n + 1);
        int sum = 0;
        for (int i = 1; i <= n; ++i) {
            sum += nums[i - 1];
            pre[i] = sum;
            cout << pre[i] << " ";
        }
        cout << endl;
        int ans = 0;
        for (int i = 0; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if ((pre[j] - pre[i]) % k == 0) {
                    ++ans;
                }
            }
        }
        return ans;
    }
};

int main() {
    vector<int> vec{4, 5, 0, -2, -3, 1};
    int k = 5;
    Solution s;
    cout << s.subarraysDivByK(vec, k) << endl;
    return 0;
}
