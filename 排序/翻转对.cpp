#include "header.h"

/**
 * 暴力法：o(n^2)没什么好解释的
 * 由于要计算nums[i] > 2 * nums[j]的个数
 * 和计算逆序对个数问题一样（可见求逆序对个数.cpp)
 * 不同的是，这里在归并的过程中要进行一个查找工作
 * 比如两个有序区间[l1, r1], [l2, r2]
 * 3 6 7 | 2 5 6
 * 归并时选择2，那2对答案的贡献度是多少呢？
 * 应该先遍历[l1, r1]，然后在[l2,r2]中查找到第一个满足 > 2 * 2的位置q
 * 然后 ans += (q-l2)
 */

class Solution {
	int ans = 0;
public:
	void mergeSort(vector<int>& nums, int l, int r)
	{
		if(l < r)
		{
			int mid = ((r - l) >> 1) + l;
			mergeSort(nums, l, mid);
			mergeSort(nums, mid + 1, r);
			// 至此[l, mid]和[mid+1, r]均有序
			merge(nums, l, mid, mid + 1, r);
		}
	}

	// [l1, r1]和[l2, r2]一定是相邻区间，注意判断条件，是相等哦
	void merge(vector<int>& nums, int l1, int r1, int l2, int r2)
	{
		vector<int> temp; // 由临时数组存好，等下需要拷贝
        // 先累加答案
        // 注意这里不能写等，因为有相等的负数影响
        // 比如 [-5] [-5]
        int p = l1, q = l2;
        while(p <= r1)
        {
            while(q <= r2 && (long)nums[p] > (2 * (long)nums[q])) q++;
            // 到此q位置不满足条件了便直接累加
            // q不用重置，因为[l1,r1]有序，前面的小
            // 如果之前的元素满足条件，则后面的元素也必定满足条件
            ans += (q - l2);
            ++p;
        }
        
		// 开始归并两个区间
        int i = l1, j = l2;
		while(i <= r1 && j <= r2)
		{
            // 左边区间的较小就直接加
			if(nums[i] < nums[j]) temp.emplace_back(nums[i++]);
			else // 右边区间的较小就要好好考究
			    temp.emplace_back(nums[j++]);
		}
		// 最多只有一个区间冗余
		while(i <= r1) temp.emplace_back(nums[i++]);
		while(j <= r2) temp.emplace_back(nums[j++]);
		for(int i = 0; i < temp.size(); ++i) nums[l1 + i] = temp[i];
		// copy(temp.begin(), temp.end(), nums.begin() + l1);
	}

    int reversePairs(vector<int>& nums) {
		int n = nums.size() - 1;
		mergeSort(nums, 0, n);
		return ans;
    }
};