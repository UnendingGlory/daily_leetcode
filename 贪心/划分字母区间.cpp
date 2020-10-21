#include <../header.h>

// 每个字符最后出现的位置一定在片段中+贪心
class Solution {
public:
    vector<int> partitionLabels(string S) {
        // 保存S中每个字母的最后一位
        // 由于每个字母在一个片段内只能出现一次，所以片段切分到endi
        vector<int> ans;
        unordered_map<char, int> last_ind;
        for(int i = 0; i < S.size(); ++i) last_ind[S[i]] = i;
        int start = 0, end = 0; // 当前片段下标
        for(int i = 0; i < S.size(); ++i)
        {
            end = max(end, last_ind[S[i]]);
            if(i == end)
            {
                ans.emplace_back(end - start + 1);
                start = i + 1;
            }
        }
        return ans;
    }
};