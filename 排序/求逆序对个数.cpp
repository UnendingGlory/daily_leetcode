#include <bits/stdc++.h>
using namespace std;

/** 使用归并排序，分治法
1. 划分问题，将序列划分成元素个数尽量相等的两半
2. 递归求解，分别统计两边的逆序对个数
3. 合并问题，统计i在左边，j在右边的逆序对个数
如何求出i在左边，j在右边的逆序对个数？分类
对于右边的每个j，统计左边比它大的元素个数f(j)，则所有f(j)之和便是答案
o(nlogn)
*/
class Solution {
public:
    int ans = 0;
    void mergeSort(vector<int>& nums, int left, int right)
    {
        if(left < right)
        {
            int mid = left + ((right - left) >> 1); // 注意，移位运算符优先级很低
            mergeSort(nums, left, mid);
            mergeSort(nums, mid + 1, right);
            merge(nums, left, mid, mid + 1, right);
        }
    }

    // merge two sorted lists
    void merge(vector<int>& nums, int l1, int r1, int l2, int r2)
    {
        vector<int> temp;
        int i = l1, j = l2;
        while(i <= r1 && j <= r2)
        {
            // 如果右边的更小，则左边的均比其大，则逆序对个数均累加
            if(nums[i] <= nums[j]) temp.push_back(nums[i++]);
            else
            {
                temp.push_back(nums[j++]);
                // 归并的时候统计即可
                ans += (r1 - i + 1);
            }
        }
        while(i <= r1) temp.push_back(nums[i++]);
        while(j <= r2) temp.push_back(nums[j++]);
        for(int i = 0; i < temp.size(); ++i) nums[l1 + i] = temp[i];
    }

    int reversePairs(vector<int>& nums) {
        int n = nums.size();
        mergeSort(nums, 0, n - 1);
        return ans;
    }
};