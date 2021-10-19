#include "header.h"

/**
 *  字符串匹配问题
 *  基本思路：暴力匹配 or KMP算法
 */

// 暴力匹配, haystack主串，needle模式串
// O(mn)
class Solution {
public:
    int strStr(string haystack, string needle) {
        int m = haystack.size(), n = needle.size();
        if (n == 0) return 0;
        if (n > m) return -1;
        for (int i = 0; i < m; ) {
            int j = 0, k = i; // 每次主串指针都会重置
            while(j < n) {
                if (haystack[k] != needle[j]) {
                    break;
                }
                else ++j, ++k; // 两者匹配则同时后移
            }
            if (j == n) return i;
        }
        return -1;
    }
};

// KMP算法，主串指针不回溯
// O(m + n)
// 首先需要说明KMP算法实际不常用
// 而在实际应用场景中因为考虑的是「平均」而不是「最坏」，各种语言一般都实现的是暴力or BM or Sunday算法
// 大量的场景中会出现全失配的情况, 全失配对于暴力算法就是O(n)，而对于KMP算法需要预构建nxt数组，反而开销更大

// 主要利用共同的前后缀 + 建立next数组实现
// 如主串为abcdbca，模式串为bca
// 主字符串下标i从0开始，如果匹配，则++i, ++j
// 如果不匹配，那么++i，且要匹配的下一个j的位置为next[j]
// next[j]单纯由模式串构建，构建next其实时间复杂度很高
// 构建思路：如 A B A B A B B
//             1 2 3 4 5 6 7
// j = 1时不匹配，next[j] = 1; j = 2时不匹配，next[j] = 1; next[3] = 1
// j = 4时不匹配，ABA，前后缀A相同，next[j] = 2
// j = 5时不匹配，ABABA，前后缀ABA相同, next[5] = 3

// 观察前后缀相同的前缀指针的下一个位置，如果不存在符合条件的前后缀，那么next[i] = 0（从头开始匹配）
// 对next改进为nextval
class Solution {
public:
    int strStr(string haystack, string needle) {
        int m = haystack.size(), n = needle.size();
        if (n == 0) return 0;
        vector<int> nxt(n);
        // 构建next数组
        nxt[0] = 0;
        for (int i = 1, j = 0; i < n; i++) {
            while (j > 0 && needle[i] != needle[j]) {
                j = nxt[j - 1];
            }
            if (needle[i] == needle[j]) {
                j++;
            }
            nxt[i] = j;
        }

        for (int i = 0, j = 0; i < m; ++i) {
            while (j > 0 && haystack[i] != needle[j]) {
                j = nxt[j - 1];
            }
            if (haystack[i] == needle[j]) {
                j++;
            }
            if (j == n) return i - n + 1; // 返回的是开始位置
        }
        return -1;
    }
};