// 一个问题必须有重叠子问题和最优子结构，才能使用动态规划去解决
// 和分治法有点相似，不同的是，分治法的子问题是不重叠的，比如归并排序，快排，左右边没有重叠区域
// 而动态规划一般是有重叠区域的
#include "header.h"
using namespace std;

/** 数塔问题
 * dp[i][j]记录从第i行第j个数字出发到达底层所有路径中能得到的最大和
 * dp[1][1]就是最终想要得到的答案
 * 状态转移方程:dp[i][j] = max(dp[i + 1][j], dp[i + 1][j + 1]) + f[i][j]
 * 递推则从下往上，递归则从上往下，到达边界条件返回
*/
const int maxn = 1000;
int dp[maxn][maxn], f[maxn][maxn];

int recur(int i, int j, int n)
{
    if(i == n) return f[i][j]; // 到达边界后返回
    return max(recur(i + 1, j, n), recur(i + 1,  j+ 1, n)) + f[i][j];
}

int main()
{
    int n; // 层数
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= i; ++j)
            scanf("%d", &f[i][j]);
    // 从下层往上计算,最底层等于自己
    for(int i = 1; i <= n; ++i)
        dp[n][i] = f[n][i];
    // 递推方法
    for(int i = n - 1; i >= 1; --i)
        for(int j = 1; j <= i; ++j)
            dp[i][j] = max(dp[i + 1][j], dp[i + 1][j + 1]) + f[i][j];
    printf("%d\n", dp[1][1]);

    // 递归方法
    printf("%d", recur(1, 1, n));
    return 0;
}