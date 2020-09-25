// 有序数组二分查找 logn
// 可以调用algorithm中的lower_bound函数
// 若是第一个大于的元素，则调用upper_bound函数
#include <bits/stdc++.h>
using namespace std;

// 二分查找解决问题o(logn)
// val为要查找的值
int bi_search(int a[], int val, int left, int right)
{
    int res = right; // res来存放最近的满足条件的数的下标
    while(left <= right)
    {
        int mid = (left + right) >> 1;
        if(a[mid] >= val) // 若是大于，这里改成>
        {
            res = mid;
            right = mid - 1;
        }
        else left = mid + 1;
    }
    if(val <= a[res]) return res;
    return -1;
}

int main()
{
    int a[10] = {1, 3, 4, 5, 7, 8, 10, 12};
    printf("%d\n", bi_search(a, 6, 0, 7));
    return 0;
}