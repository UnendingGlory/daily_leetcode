#include <bits/stdc++.h>
using namespace std;

// dp
// dp[i][a][b][c]表示前i列染完色，最后一列颜色分别为a b c时的方案数
// ans = sum(dp[n - 1][i][j][k])相加
// 0,1,2代表三种颜色

class Solution {
public:
    int numOfWays(int n) {
        int dp[5005][3][3][3];
        memset(dp, 0, sizeof(dp));
        const int mod = 1e9 + 7;
        for(int i = 0; i < n; ++i)
            for(int a = 0; a < 3; ++a)
                for(int b = 0; b < 3; ++b)
                    for(int c = 0; c < 3; ++c) // 枚举每一个位置
                    {
                        if(a == b || b == c) continue; // 没有重复颜色，保证横着没有重复颜色
                        if(i == 0) dp[i][a][b][c] = 1; // 第一行各类只有一种
                        else // 不是第一行则dp相加
                        {
                            for(int aa = 0; aa < 3; ++aa)
                                for(int bb = 0; bb < 3; ++bb)
                                    for(int cc = 0; cc < 3; ++cc)
                                    {
                                        if(aa != a && bb != b && cc != c) // 保证竖着没有重复颜色
                                            (dp[i][a][b][c] += dp[i - 1][aa][bb][cc]) %= mod; // 对自己累加
                                    }
                        }
                    }
        int ans = 0;
        for(int a = 0; a < 3; ++a)
            for(int b = 0; b < 3; ++b)
                for(int c = 0; c < 3; ++c)
                {
                    if(a != b && b != c) 
                        (ans += dp[n - 1][a][b][c]) %= mod;
                }
        return ans;
    }
};

int main()
{
    return 0;
}