#include <bits/stdc++.h>
#include <limits.h>
using namespace std;

// 注意"+42"返回值是42
// 注意"+42"返回值是42
class Solution {
public:
    int myAtoi(string str) {
        // 无符号，同是32位，将int的符号位也用来表示数字，范围比int大一倍（*2)
        // long lone也可
        unsigned int ans = 0; 
        int i = 0, sign = 1;
        // 先清空字符串前缀空格
        while(str[i] == ' ') ++i;
        if(str[i] == '+') ++i;
        else if(str[i] == '-') sign = -1, ++i; // 符号为负
        while(i < str.size() && str[i] >= '0' && str[i] <= '9')
        {
            ans = 10 * ans + (str[i] - '0');
            if(ans > (unsigned int)INT_MAX && sign == 1) return INT_MAX;
            if(ans > (unsigned int)INT_MAX + 1 && sign == -1) return INT_MIN;
            ++i;
        }
        ans *= sign;
        return ans;
    }
};

int main()
{
    return 0;
}