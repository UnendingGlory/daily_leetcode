#include <bits/stdc++.h>
using namespace std;

// 比赛的时候只想到了第一层，没想到第二层，最后不得不暴力过
// 第一层：以递减为例，以中间数为轴，统计左边比中间数大的数个数p，右边比中间数小的数个数q
// 这一步可以通过暴力，也可以通过树状数组来解决
// 第二层： 最后答案是 p * q即可
class Solution {
public:
    int numTeams(vector<int>& rating) {
        int n = rating.size();
        int kase = 0;
        for(int j = 1; j < n - 1; j++){
            int lower = 0, upper = 0;
            for(int i = j - 1; i >=0; i--){
                if(rating[i] < rating[j]) lower++;
            }
            for(int k = j + 1; k < n; k++){
                if(rating[j] < rating[k]) upper++;
            }
            int s = lower * upper;
            kase += s;
        }
        for(int j = 1; j < n - 1; j++){
            int lower = 0, upper = 0;
            for(int i = j - 1; i >=0; i--){
                if(rating[i] > rating[j]) lower++;
            }
            for(int k = j + 1; k < n; k++){
                if(rating[j] > rating[k]) upper++;
            }
            int s = lower * upper;
            kase += s;
        }
        return kase;
    }
};


int main()
{
    return 0;
}