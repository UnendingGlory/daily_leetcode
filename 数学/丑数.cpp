#include "header.h"

using namespace std;
// 如果一个数x是丑数，则2x,3x,5x也是，第一个是1
// 由于可能重复，因此要用一个map判断
// 用优先级队列，每次取最小的一个，然后加入2x, 3x, 5x
typedef long long LL;
class Solution {
public:
    int nthUglyNumber(int n) {
        int idx[3] = {2, 3, 5};
        unordered_map<LL, bool> m;
        priority_queue<LL, vector<LL>, greater<LL>> pq;
        pq.push(1);
        m[1] = true;
        for(int i = 1; ; ++i)
        {
            LL x = pq.top();
            pq.pop();
            if(i == n) return x;
            for(int j = 0; j < 3; ++j)
            {
                // 这里可能超出int的范围
                LL temp = idx[j] * x;
                if(m[temp] != true)
                {
                    pq.push(temp);
                    m[temp] = true;
                }
            }
        }
    }
};