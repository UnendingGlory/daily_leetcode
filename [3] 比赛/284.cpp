#include "../header.h"

// key左右的k个均是
class Solution {
public:
    vector<int> findKDistantIndices(vector<int>& nums, int key, int k) {
        int n = nums.size();
        vector<int> ans;
        set<int> s;
        for (int i = 0; i < n; ++i) {
            if (nums[i] == key) {
                for (int j = i - k; j <= i + k; ++j) {
                    if (j >= 0 && j < n) s.insert(j);
                }
            }
        }
        for (int i : s) ans.push_back(i);
        return ans;
    }
};

// 每个工件最多只覆盖四个单元格
// n * n
// 连通图分块
class Solution1 {
public:
    int digArtifacts(int n, vector<vector<int>>& artifacts, vector<vector<int>>& dig) {
        vector<vector<int>> g(n, vector<int>(n, -1));
        // 将四块映射到一个地方
        int an = artifacts.size(); // 工件块数
        vector<int> area(an, -1);
        for (int index = 0; index < an; ++index) {
            vector<int> v = artifacts[index];
            int s0 = v[0], e0 = v[1], s1 = v[2], e1 = v[3];
            for (int i = s0; i <= s1; ++i) {
                for (int j = e0; j <= e1; ++j) {
                    g[i][j] = index; // 该位置属于哪个工件
                }
            }
            area[index] = (s1 - s0 + 1) * (e1 - e0 + 1);
        }
        for (int index = 0; index < dig.size(); ++index) {
            vector<int> d = dig[index];
            if (g[d[0]][d[1]] != -1)
                --area[g[d[0]][d[1]]];
        }
        int ans = 0;
        for (int i: area) {
            if (i == 0) ++ans;
        }
        return ans;
    }
};


int main() {
    Solution1 s;
    int n = 2;
    vector<vector<int>> artifacts {{0,0,0,0},{0,1,1,1}};
    vector<vector<int>> digs {{0,0}, {0,1}};
    s.digArtifacts(n, artifacts, digs);
    return 0;
}
