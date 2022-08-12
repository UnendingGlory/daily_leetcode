#include "header.h"

// 给你两个版本号 version1 和 version2 ，请你比较它们。
// 版本号由一个或多个修订号组成，各修订号由一个 '.' 连接。每个修订号由 多位数字 组成，可能包含 前导零。
// 每个版本号至少包含一个字符。修订号从左到右编号，下标从 0开始，最左边的修订号下标为 0，下一个修订号下标为 1，以此类推。
// 例如，2.5.33和 0.1都是有效的版本号。
// 比较版本号时，请按从左到右的顺序依次比较它们的修订号。比较修订号时，只需比较 忽略任何前导零后的整数值。
// 也就是说，修订号 1和修订号 001相等。
// 如果版本号没有指定某个下标处的修订号，则该修订号视为 0。
// 例如，版本 1.0小于版本 1.1，因为它们下标为 0的修订号相同，而下标为 1的修订号分别为 0 和 1，0 < 1。

// 返回规则如下：
// 如果 version1 > version2 返回 1，
// 如果 version1 < version2 返回 -1，
// 除此之外返回 0。

// 输入：version1 = "1.01", version2 = "1.001"
// 输出：0
// 解释：忽略前导零，"01" 和 "001" 都表示相同的整数 "1"

// 输入：version1 = "1.0", version2 = "1.0.0"
// 输出：0
// 解释：version1 没有指定下标为 2 的修订号，即视为 "0"

// 输入：version1 = "0.1", version2 = "1.1"
// 输出：-1
// 解释：version1 中下标为 0 的修订号是 "0"，version2 中下标为 0 的修订号是 "1"。0 < 1，所以 version1 < version2。

// 从左到右，两个字符串按照 .进行分割，去除前缀0之后进行比较。
class Solution {
public:
    string splitFirst(string &version, int &i) {
        string ans;
        while (i < version.size() && version[i] != '.') {
            ans.push_back(version[i]);
            ++i;
        }
        ++i;
        return ans;
    }

    int compareVersion(string version1, string version2) {
        int len1 = version1.size(), len2 = version2.size();
        int i = 0, j = 0;
        while (i < len1 || j < len2) {
            string str1, str2;
            if (i >= len1) { // 超出按照0处理
                str1 = "0";
            } else {
                str1 = splitFirst(version1, i);
            }
            if (j >= len2) { // 超出按照0处理
                str2 = "0";
            } else {
                str2 = splitFirst(version2, j);
            }
            int ver1 = stoi(str1), ver2 = stoi(str2);
            if (ver1 != ver2) {
                return ver1 > ver2 ? 1 : -1;
            }
        }
        return 0;
    }
};
