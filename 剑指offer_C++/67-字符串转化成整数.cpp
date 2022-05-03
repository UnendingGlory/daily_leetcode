#include "header.h"


// 算法很简单。
// 主要需要考虑很多边界情况。
// 考虑以下输入："", "0100", "w", "512 hello", "+52", "-51", "+0100", "+", 
//             "-", "   -42"，“+-2”
// 溢出时返回INT_MAX和INT_MIN。
// 溢出的情况： "+10101001001010", "-6567718283189"。
class Solution {
public:
    int strToInt(string str) {
        if (str.size() == 0) return 0;
        int i = 0, sign = 1;
        long long sum = 0;
        while(str[i] == ' ') ++i; // 清空前缀空格
        if (str[i] == '+') ++i;
        else if (str[i] == '-') sign = -1, ++i; // 要写else，特殊case"+-2"
        // 得保证后面接的都是'0'-'9'之间的字符
        // 在以下处理方法可以不考虑前导0的情况如"0110"
        while (i < str.size() && str[i] >= '0' && str[i] <= '9') {
            sum = sum * 10 + (str[i] - '0');
            // 判断是否溢出
            if (sum * sign > INT_MAX) return INT_MAX;
            if (sum * sign < INT_MIN) return INT_MIN;
            ++i;
        }
        return sign * sum;
    }
};
