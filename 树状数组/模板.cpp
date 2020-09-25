#include <bits/stdc++.h>
using namespace std;

inline int lowbit(int x)
{
    return x & (-x);
}

int getSum(int x, int tree[]) //  获得前x个正整数和
{
    int sum = 0;
    for(int i = x; i >= 1; i -= lowbit(i)) // 向前求和
        sum += tree[i];
    return sum;
}

void update(int x, int val, int arr[], int tree[], int N) // 将x位置的元素值修改为val
{
    for(int i = x; i <= N; i += lowbit(i)) // 向后更新，更新值为val - arr[x]
        tree[i] += (val - arr[x]);
    arr[x] = val; // 修改之
}

int main()
{
    int n, temp;
    scanf("%d", &n);
    int num[n + 1], tree[n + 1];
    memset(tree, 0, sizeof(tree));
    memset(num, 0, sizeof(num));
    for(int i = 1; i <= n; ++i)
    {
        scanf("%d", &temp);
        update(i, temp, num, tree, n);
    }
    for(int i = 1; i <= n; ++i)
        printf(i == 1 ? "%d" : " %d", num[i]);
    printf("\n");
    for(int i = 1; i <= n; ++i)
        printf(i == 1 ? "%d" : " %d", tree[i]);

    update(2, 5, num, tree, n);
    printf("\n");
    for(int i = 1; i <= n; ++i)
        printf(i == 1 ? "%d" : " %d", num[i]);
    printf("\n");
    for(int i = 1; i <= n; ++i)
        printf(i == 1 ? "%d" : " %d", tree[i]);
    return 0;
}