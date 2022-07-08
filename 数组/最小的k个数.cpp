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

int main()
{
    return 0;
}