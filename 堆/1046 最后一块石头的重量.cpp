#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int, vector<int>> pq; // 默认大顶堆
        for(auto i : stones) pq.push(i);
        while(pq.size() > 1)
        {
            int x = pq.top();
            pq.pop();
            int y = pq.top();
            pq.pop();
            if(x > y) pq.push(x - y);
        }
        if(pq.size()) return pq.top();
        else return 0;
    }
};