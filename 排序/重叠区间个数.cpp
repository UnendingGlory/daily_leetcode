#include<bits/stdc++.h>
using namespace std;

int solution(vector<pair<int,int>> a)
{
    vector<int> in, out;
    for(auto i : a)
    {
        in.push_back(i.first); 
        out.push_back(i.second);
    }
    sort(in.begin(), in.end());
    sort(out.begin(), out.end());
    // out[j]记录上一个走的人的时间, j为out数组的当前下标，代表上一个离开的人
    // 只记录当前在场的人数
    int ans = 0, cur = 1, j = 0;
    for(int i = 1; i < in.size() && j < out.size(); )
    {
        if(in[i] < out[j])
        {
            ++cur;
            ++i;
            ans = max(ans, cur);
        }
        else
        {
            --cur;
            ++j;
        }
    }
    return ans;
}

int main()
{
    vector<pair<int, int>> a{{0, 30}, {5, 10}, {15, 20}};
    printf("%d\n", solution(a));
    return 0;
}