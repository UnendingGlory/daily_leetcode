/***************************************************************************
 *  @file       radix_sort.cpp
 *  @author     Wilosn.Wang
 *  @date       26  Nov 2020
 *  @remark     This code is a template for radix/bucket sort.
				radix sort过程：先按个位数分配进10个桶中，然后按顺序收集，再按十位数分配
				时间复杂度：O(d * n)，d为位数，n为元素个数。
				虽然是线性时间复杂度，但是经过分析可以知道，在数据量没那么庞大的情况下还
				是快排等算法较优。
 *  @note
 ***************************************************************************/
// g++ .\radix_sort.cpp -I "..\" -o radix_sort
#include "header.h"

// 模板类，用来打印各类数据（只要该类重载了运算符<<即可）
template <typename T>
class display
{
public:
	void operator()(const T& x)
	{
		cout << x << ' ';
	}
};

void radix_sort(vector<int>& nums) {
	int n = nums.size();
	vector<vector<int>> bucket(10); // 10个桶
	// 获得最大元素，以此作为循环终止条件
	int maxNum = *max_element(nums.begin(), nums.end());
	int divisor = 1;
	while(divisor <= maxNum)
	{
		// 每一趟重置桶内元素，注意要每一个clear
		// 如果直接bucket.clear则要resize
		for(int i = 0; i < 10; ++i) bucket[i].clear();
		for(int i = 0; i < n; ++i)
		{
			size_t idx = (nums[i] / divisor) % 10;
			bucket[idx].push_back(nums[i]);
		}
		nums.clear();
		// o(n)
		for(auto j : bucket)
		{
			for(auto t : j)
			{
				// 由于t之后丢弃不用，所以直接std::move
				nums.emplace_back(std::move(t));
			}
		}
		divisor *= 10;
	}
}

int main()
{
	vector<int> nums {1, 4, 22, 13, 45, 21};
	vector<int> nums2 {100, 3, 2, 1};
	for_each(nums2.begin(), nums2.end(), display<int>());
	cout << '\n';
	radix_sort(nums2);
	for_each(nums2.begin(), nums2.end(), display<int>());
	cout << '\n';
	return 0;
}


