#include <bits/stdc++.h>
using namespace std;

// 用栈来计算深度，但是此题中输入已经保证了括号一定是匹配的，所以不需要
// 直观解法：
class Solution {
public:
    // 使得两组字符串的深度相差最小
    vector<int> maxDepthAfterSplit(string seq) {
        vector<int> ans;
        int A_depth = 0, B_depth = 0; // A和B的当前深度
        for(char i : seq)
        {
            if(i == '(') // 加深度
            {
                if(A_depth >= B_depth)
                    ++B_depth, ans.push_back(1);
                else 
                    ++A_depth, ans.push_back(0);
            }
            else // 减深度
            {
                if(A_depth >= B_depth) // 等号一定要对应，使其匹配
                    --A_depth, ans.push_back(0);
                else
                    --B_depth, ans.push_back(1);
            }
        }
        return ans;
    }
};

// 使挨着的左括号分属与不同的集合即可，右括号同理
// 使用异或操作^
class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        vector<int> ans;
        int pre = 1; // 标记前一个字符是不是A
        for(char i : seq)
        {
            if(i == '(') pre ^= 1, ans.push_back(pre);
            else 
                ans.push_back(pre), pre ^= 1; // 先push保证匹配
        }
        return ans;
    }
};

int main()
{
    return 0;
}