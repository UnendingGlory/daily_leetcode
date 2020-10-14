#include <vector>
#include <string>
#include <array>
#include <algorithm>
using namespace std;

// 统计每一个单词字符，保存出现次数最少的字符
// 最后每一个单词在min_freq中出现几次就输入几次到结果数组即可
class Solution {
public:
    vector<string> commonChars(vector<string>& A) 
    {
        array<int, 26> freq, min_freq;
        // array有自己的fill
        min_freq.fill(__INT_MAX__);
        for(const auto &i : A)
        {
            freq.fill(0);
            for(char j : i) ++freq[j - 'a'];
            for(int i = 0; i < 26; ++i)
                min_freq[i] = min(min_freq[i], freq[i]);
        }
        vector<string> ans;
        for(int i = 0; i < 26; ++i)
        {
            while (min_freq[i]--)
                ans.emplace_back(string(1, 'a' + i));
        }
        return ans;
    }
};