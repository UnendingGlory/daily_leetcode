#include <bits/stdc++.h>
using namespace std;

class Solution {
    // 堆排序，维护一个大顶堆
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        priority_queue<int, vector<int>> pq;
        for(int i : arr)
        {
            pq.push(i);
            // 将堆顶最大元素pop出，保持大小在k
            if(pq.size() > k) pq.pop(); 
        }
        vector<int> ans;
        while(k--)
        {
            ans.push_back(pq.top());
            pq.pop();
        }
        return ans;
    }
};

// 借用快排的 patition操作。
// 时间复杂度：O(n)，空间复杂度：O(n)。


int main()
{
    return 0;
}