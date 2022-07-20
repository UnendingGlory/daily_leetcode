#include "header.h"

// 给你一个文件，并且该文件只能通过给定的 read4 方法来读取，请实现一个方法使其能够读取 n 个字符。
// read4 可以从文件中读取 4 个连续的字符，并且将它们写入缓存数组 buf 中。
// 返回值为实际读取的字符个数。

// 通过使用 read4 方法，实现 read 方法。该方法可以从文件中读取 n 个字符并将其存储到缓存数组 buf 中。
// 不能直接操作文件。

/**
 * The read4 API is defined in the parent class Reader4.
 *     int read4(char *buf4);
 */

// 迭代，每四个字符读取即可，注意读取个数不要超过限制 n。
class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Number of characters to read
     * @return    The number of actual characters read
     */
    int read(char *buf, int n) {
        int ans = 0;
        for (int i = 0; i < n; i += 4) {
            int cnt = read4(buf + i);
            ans += min(cnt, n - i);
        }
        return ans;
    }
};
