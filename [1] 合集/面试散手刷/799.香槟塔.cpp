#include "header.h"

// 我们把玻璃杯摆成金字塔的形状，其中 第一层 有 1 个玻璃杯， 第二层 有 2 个，依次类推到第 100 层，每个玻璃杯 (250ml) 将盛有香槟。
// 从顶层的第一个玻璃杯开始倾倒一些香槟，当顶层的杯子满了，任何溢出的香槟都会立刻等流量的流向左右两侧的玻璃杯。
// 当左右两边的杯子也满了，就会等流量的流向它们左右两边的杯子，依次类推。（当最底层的玻璃杯满了，香槟会流到地板上）。
// 例如，在倾倒一杯香槟后，最顶层的玻璃杯满了。倾倒了两杯香槟后，第二层的两个玻璃杯各自盛放一半的香槟。
// 在倒三杯香槟后，第二层的香槟满了 - 此时总共有三个满的玻璃杯。在倒第四杯后，第三层中间的玻璃杯盛放了一半的香槟，他两边的玻璃杯各自盛放了四分之一的香槟。
// 在当倾倒了非负整数杯香槟后，返回第 i 行 j 个玻璃杯所盛放的香槟占玻璃杯容积的比例（ i 和 j 都从0开始）。

// 输入: poured(倾倒香槟总杯数) = 1, query_glass(杯子的位置数) = 1, query_row(行数) = 1
// 输出: 0.00000
// 解释: 我们在顶层（下标是（0，0））倒了一杯香槟后，没有溢出，因此所有在顶层以下的玻璃杯都是空的。
// 0 <= query_glass <= query_row < 100

// Solution1：直觉：动态规划，dp模拟。
// 开辟一个二维 dp数组。
// 如果第 i行 第 j列溢出，那么溢出的会分一半流到 i+1行 第j列和第 j + 1列里。
// 行数最多为 100。
// 时间复杂度O(n^2)，空间复杂度: O(N^2)
class Solution {
public:
    double champagneTower(int poured, int query_row, int query_glass) {
        double dp[101][101], overflow;
        memset(dp, 0, sizeof(dp));
        dp[0][0] = poured;
        // 101层即倒在地上
        for (int i = 0; i < 100; ++i) {
            for (int j = 0; j <= i; ++j) {
                if (dp[i][j] > 1.0) {
                    overflow = (dp[i][j] - 1.0) / 2;
                    dp[i][j] = 1.0; // 溢出直接赋值为 1.0
                    dp[i + 1][j] += overflow;
                    dp[i + 1][j + 1] += overflow;
                }
            }
        }
        return dp[query_row][query_glass];
    }
};

// Solution2：动态规划空间复杂度优化。
// 其实我们只需要计算到 query_row行即可。
// 且 dp[i+1][j] 和 dp[i + 1][j + 1] 只和 dp[i][j]有关。
// 因此可以采用滚动数组对空间进行优化。
// 由于j+1会覆盖，因此应该倒序遍历。
// 时间复杂度O(n^2)，空间复杂度: O(N)
class Solution {
public:
    double champagneTower(int poured, int query_row, int query_glass) {
        double dp[101], overflow, volume;
        memset(dp, 0, sizeof(dp));
        dp[0] = poured;
        // 101层即倒在地上
        for (int i = 0; i < query_row; ++i) {
            // j最多只计算到 query_row即可，右侧的不需要管。
            for (int j = min(i, query_row); j >= 0; --j) {
                volume = dp[j];
                // 重置下一层，因为可能查询到还没有重置的层
                dp[j] = 0;
                if (volume > 1.0) {
                    overflow = (volume - 1) / 2;
                    dp[j] += overflow;
                    dp[j + 1] += overflow; 
                }
            }
        }
        // 计算到 query_glass时也可能溢出，还没有模拟完。
        // 溢出时直接返回 1.
        return min(1.0, dp[query_glass]);
    }
};