#include "header.h"

// 从地图的最左上角开始走，每次只能往下或者往右
// 有多少条不同路径到达地图的右下角

// Solution1 dp
// dp[i][j]表示从左上角到当前位置的路径个数
// 那么dp[i][j] = dp[i - 1][j] + dp[i][j - 1]
// 边界条件：dp[0][j] = 1, dp[i][0] = 1
// O(mn)
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            dp[0][i] = 1;
        }
        for (int i = 0; i < m; ++i) {
            dp[i][0] = 1;
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i && j) {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
            }
        }
        return dp[m - 1][n - 1];
    }
};

// Solution2 数学思想
// 总共向下走m-1步，向右走n-1步
// 所以总共要走m + n - 2步，只要从这m + n - 2步里面
// 选向下的m-1步即可 😎
// 所以就是C(m - 1, m + n - 2)
// C(m - 1, m + n - 2) = (m + n - 2)! / (m - 1)! * (n - 1)!
// =(m + n - 2)*(m + n - 3) ... m / (n - 1)!

class Solution {
public:
    int uniquePaths(int m, int n) {
        long long ans = 1;
        for (int x = 1, y = m; x < n; ++x, ++y) {
            // ans *= (y / x); // 这么写会出现因为整数截断出现的错误
            ans = ans * y / x; // 这么会溢出，所以ans需要是long long
        }
        return ans;
    }
};
