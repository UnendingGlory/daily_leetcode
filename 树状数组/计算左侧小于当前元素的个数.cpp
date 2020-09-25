#include <bits/stdc++.h>
using namespace std;

// hash[x]记录当前出现的次数，接着，从左到右遍历序列A，假如当前访问的是A[i]则hash[A[i]]++增加一次，
// 同时，序列左边比A[i]小的数个数为hash[1] + hash[2] + ...，这个和需要输出
// 显然，这对应着树状数组模板问题中的update和getSum问题
const int maxn = 10010;

int c[maxn]; // 树状数组，记录元素出现的次数

inline int lowbit(int i)
{
    return i & (-i);
}

void update(int x, int v) // 第x个数加上v，往后更新
{
    for(int i = x; i <= maxn; i+= lowbit(i))
        c[i] += v;
}

int sumRange(int i) // 求前i个元素之和，包括i, 往前求和
{
    int sum = 0;
    for(int k = i; k > 0; k -= lowbit(k))
        sum += c[k];
    return sum;
}

// 离散化，将原数组的数转换为不超过元素个数大小的整数
struct node
{
    int val; 
    int pos;// 原始序号
}temp[maxn];


int main()
{
    int A[] = {11111, 4, 3, 9090, 6, 7, 2};
    memset(c, 0, sizeof(c));
    // 右侧小于当前元素
    for(int i = 0; i <= 6; ++i)
    {
        temp[i].pos = i; // 原始序号
        temp[i].val = A[i];
    }
    sort(temp, temp + 7, [&](const node &a, const node &b){
        return a.val < b.val;
    }); // 按值从小到大排序
    A[temp[0].pos] = 1; // 最小的一名化为1

    for(int i = 1; i <= 6; ++i)
    {
        if(temp[i].val == temp[i - 1].val) A[temp[i].pos] = A[temp[i - 1].pos];
        else A[temp[i].pos] = i + 1; // 1 - N
    }

    // 倒着就是计算右侧比当前元素小的元素个数
    for(int i = 6; i >= 0; --i)
    {
        update(A[i], 1); // A[i]元素出现次数+1
        printf("%d %d\n", A[i], sumRange(A[i] - 1)) ; // 由于求的是小于的，所以-1
    }
    return 0;
}