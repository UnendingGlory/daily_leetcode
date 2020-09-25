#include <bits/stdc++.h>
using namespace std;

// 直接暴力，sumRange o(n)，update为o(1)，如果k次操作均是求和，则时间复杂度为o(kn)，难以承受
class NumArray {
    vector<int> v;
public:
    NumArray(vector<int>& nums) {
        for(int i : nums) v.push_back(i);
    }
    
    void update(int i, int val) {
        v[i] = val;
    }
    
    int sumRange(int i, int j) {
        int sum = 0;
        for(int k = i; k <= j; ++k)
            sum += v[k];
        return sum;
    }
};

// 使用前缀和维护sum[i]
// sumRange时间复杂度是o(1)，但是update时间复杂度为o(n)，如果k次操作均是求和，时间复杂度为o(kn)

class NumArray {
    vector<int> arr, sum;
public:
    NumArray(vector<int>& nums) {
        if(nums.size() == 0) return;
        arr = nums;
        sum.resize(nums.size());
        fill(sum.begin(), sum.end(), 0);
        sum[0] = nums[0];
        for(int i = 1; i < nums.size(); ++i)
            sum[i] = sum[i - 1] + nums[i];
    }
    
    void update(int i, int val) {
        for(int k = i; k < sum.size(); ++k)
            sum[k] += (val - arr[i]);
        arr[i] = val; // 修改之
    }
    
    int sumRange(int i, int j) {
        if(i == 0) return sum[j];
        else return sum[j] - sum[i - 1];
    }
};

// 树状数组，tree[i]存放的是i号位之前lowbit(i)个元素之和
class NumArray {
    vector<int> arr, tree; // tree树状数组,注意树状数组下标比原数组多1
public:
    NumArray(vector<int>& nums) {
        arr.resize(nums.size() + 1);
        tree.resize(nums.size() + 1); // 树状数组下标从1开始
        fill(arr.begin(), arr.end(), 0);
        fill(tree.begin(), tree.end(), 0); // 初始化arr和树状数组为0
        for(int i = 0; i < nums.size(); ++i)    
            update(i, nums[i]); // 初始化树状数组
    }
    
    inline int lowbit(int x) //求得能整除x的最大的2的幂次
    {
        return x & (-x);
    }

    void update(int i, int val) { // 向后更新，注意下标
        for(int j = i + 1; j < tree.size(); j += lowbit(j))
            tree[j] += (val - arr[i + 1]);
        arr[i + 1] = val; // 修改该位置
    }
    
    int getSum(int x) // 获得x位置之前的元素和，向前求和
    {
        int sum = 0;
        for(int k = x + 1; k >= 1; k -= lowbit(k))
            sum += tree[k];
        return sum;
    }

    int sumRange(int i, int j) { 
        return getSum(j) - getSum(i - 1); // 得到区间和
    }
};

// 线段树，sumRange (logn), update(logn)
int n; // 全局变量作为默认参数
class NumArray{
    vector<int> tree; // tree线段树存放和，arr存放原数组
public:
    NumArray(vector<int>& nums) {
        if(nums.size() == 0) return;
        n = nums.size() - 1;
        tree.resize(4 * nums.size()); // 4倍原数组
        build_tree(nums); // 根节点下标为0
    }
    
    // left-right二分区间，cur为当前的tree的下标
    void build_tree(const vector<int>& arr, int cur = 0, int left = 0, int right = n) 
    {
        if(left == right)
        {
            tree[cur] = arr[left];
            return;
        }
        int mid = (left + right) >> 1;
        int l_child = 2 * cur + 1, r_child = 2 * cur + 2;
        build_tree(arr, l_child, left, mid);
        build_tree(arr, r_child, mid + 1, right);
        tree[cur] = tree[l_child] + tree[r_child];
    }

    // 区间搜索依赖于原数组的下标，更新依赖于线段树
    void update(int i, int val, int cur = 0, int left = 0, int right = n) {
        if(left == right)
        {
            tree[cur] = val;
            return;
        }
        int mid = (left + right) >> 1;
        int l_child = 2 * cur + 1, r_child = 2 * cur + 2;
        if(i >= left && i <= mid) // 要更新的位置落在原数组左半区，更新左子树及其路径
            update(i, val, l_child, left, mid);
        else update(i, val, r_child, mid + 1, right);
        tree[cur] = tree[l_child] + tree[r_child]; //修改完后更新线段树
    }
    
    int sumRange(int i, int j, int cur = 0, int left  = 0, int right = n) {
        if(right < i || left > j) return 0; // 不在查询区间内
        if(left >= i && right <= j) return tree[cur]; // 包含当前区间则直接返回
        int mid = (left + right) >> 1;
        int l_child = 2 * cur + 1, r_child = 2 * cur + 2;
        return sumRange(i, j, l_child, left, mid) + sumRange(i, j, r_child, mid + 1, right);
    }
};