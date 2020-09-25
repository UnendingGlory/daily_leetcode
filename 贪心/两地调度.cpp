#include <bits/stdc++.h>
using namespace std;

// 思路：先不考虑两个城市去的人数，优先选小的
// 然后考虑城市人数均分，将人数多的城市均给另一个城市
// 如何选择？容易想到，为了保证总体值最小，选择的应该是cost的差值小的
// 输入时用小顶堆来维护即可

class Solution {
public:
    int twoCitySchedCost(vector<vector<int>>& costs) {
        int ans = 0;
        priority_queue<int, vector<int>, greater<int>> A, B;
        for(int i = 0; i < costs.size(); i++)
        {
            int dis = abs(costs[i][0] - costs[i][1]);
            if(costs[i][0] < costs[i][1])
            {
                ans += costs[i][0];
                A.push(dis);
            }
            else
            {
                ans += costs[i][1];
                B.push(dis);
            }
        }
        int num_A = A.size(), num_B = B.size();
        while(num_A != num_B)
        {
            if(num_A < num_B)
            {
                ans += B.top();
                B.pop();
                ++num_A, --num_B;
            }
            else
            {
                ans += A.top();
                A.pop();
                ++num_B, --num_A;
            }
        }
        return ans;
    }
};

int main()
{
    return 0;
}