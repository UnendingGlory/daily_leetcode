#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000, n = 6;

void build_tree(int arr[], int tree[], int node, int start, int end) // node 线段树节点下标
{
    if(start == end)
    {
        tree[node] = arr[start];
        return;
    }
    int mid = (start + end) >> 1;
    int l_node = node * 2 + 1, r_node = node * 2 + 2;
    build_tree(arr, tree, l_node, start, mid); // 建线段树的左子树，下标为l_node
    build_tree(arr, tree, r_node, mid + 1, end);
    tree[node] = tree[l_node] + tree[r_node]; // 返回
}

void update_tree(int tree[], int node, int start, int end, int idx, int val) 
// 将idx位置的数修改为val
{
    if(start == end)
    {
        //arr[idx] = val; // 这里可以不update，直接依靠线段树即可
        tree[node] = val;
        return;
    }
    int mid = (start + end) >> 1;
    int l_node = node * 2 + 1, r_node = node *2 + 2;
    if(idx >= start && idx <= mid) update_tree(tree, l_node, start, mid, idx, val); // 要更新的位置与相关路径位于左子树
    else update_tree(tree, r_node, mid + 1, end, idx, val); // 更改右子树
    tree[node] = tree[l_node] + tree[r_node]; // 更新
}

int query_tree(int tree[], int node, int start, int end, int L, int R)
{
    if(R < start || L > end) return 0;
    if(L <= start && end <= R) return tree[node]; // 递归的区间落在要查找的区间内
    int mid = (start + end) >> 1;
    int l_node = node * 2 + 1, r_node = node *2 + 2;
    int sum_left = query_tree(tree, l_node, start, mid, L, R);
    int sum_right = query_tree(tree, r_node, mid + 1, end, L, R);
    return sum_left + sum_right;
}

int main()
{
    int arr[n] = {1, 2, 3, 4, 5, 6}, tree[maxn];
    memset(tree, 0, sizeof(tree));
    for(int i = 0; i < n; ++i) printf(i == 0? "%d" : " %d", arr[i]);
    printf("\n");
    build_tree(arr, tree, 0, 0, n - 1); // 根节点开始建树
    for(int i = 0; i < 15; ++i) printf(i == 0? "%d" : " %d", tree[i]);

    printf("\n%d", query_tree(tree, 0, 0, n - 1, 0 , 4));

    update_tree(tree, 0, 0, n - 1, 4, 10);

    printf("\n%d", query_tree(tree, 0, 0, n - 1, 0 , 4));
    return 0;
}