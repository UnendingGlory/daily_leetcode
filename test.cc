// #include "header.h"
// #include <random>
// #include <ctime>
// #include <numeric>
// #include <chrono>

// // o(n), 滑动窗口 + 哈希
// int has_anagram1(const string &str, const string &aim) {
//     if (str.size() < aim.size()) {
//         return -1;
//     }
//     unordered_map<char, int> occur, windows;
//     for (int i = 0; i < 26; ++i) { // 使用unordered_map的比较要先预处理字符
//         occur['a' + i] = windows['a' + i] = 0;
//     }
//     for (char c : aim) ++occur[c];
//     for (int i = 0; i < aim.size(); ++i) {
//         ++windows[str[i]];
//     }
//     if (windows == occur) return 0;
//     for (int i = 1, j = aim.size(); j < str.size(); ++i, ++j) {
//         --windows[str[i - 1]], ++windows[str[j]];
//         if(windows == occur) return i;
//     }
//     return -1;
// }

// // 如果不是anagram一定会有一个负的
// // 该方法寻找第一个位置，没有则返回-1
// // 即不用哈希表，统计是否有负的就行，用一个变量记录
// int has_anagram2(const string& str, const string& aim) {
//     int count[26] = {0}, invalid = 0, r = 0, len = aim.size();
//     for(const char c: aim) ++count[c - 'a'];
//     for (; r < aim.size(); ++r) {
//         if (--count[str[r] - 'a'] < 0) {
//             ++invalid;
//         }
//     }
//     for (; r < str.size(); ++r) {
//         if (invalid == 0) {
//             return r - len;
//         }
//         if (count[str[r] - 'a']-- <= 0) {
//             ++invalid;
//         }
//         if (count[str[r - len] - 'a']++ < 0) {
//             --invalid;
//         }
//     }
//     // 最后一个window
//     return !invalid ? r - len : -1;
// }

// const string table = "abcdefghijklmnopqrstuvwxyz";
// const size_t max_index = table.size() - 1;
// constexpr std::default_random_engine e;  // random_engine声明为static的
// std::uniform_int_distribution<size_t> distrib(1, max_index);

// std::string random_string(size_t len) 
// {
//     constexpr std::default_random_engine ee();
//     std::uniform_int_distribution<size_t> dis;
//     auto randchar = []()->char {
//         return table[distrib(e)];
//     };
//     string ret;
//     ret.resize(len);
//     generate_n(ret.begin(), len, randchar);
//     return ret;
// }

// // 从小到大
// void basicQuickSort(vector<int>& num, int l, int r)
// {
//     if (l >= r) return;
//     // partition
//     int pivot = num[l], x = l, y = r;
//     while (x < y) {
//         while (x < y && num[y] >= pivot) --y;
//         swap(pivot, num[y]);
//         while (x < y && num[x] <= pivot) ++x;
//         swap(pivot, num[x]);
//     }
//     // x == y
//     num[x] = pivot;
//     basicQuickSort(num, l, x - 1);
//     basicQuickSort(num, x + 1, r);
// }

// // 无监督版
// void unguardQuickSort(vector<int>& num, int l, int r)
// {
//     if (l >= r) return;
//     int pivot = num[l], x = l, y = r;
//     while (x <= y) {
//         while (num[x] > pivot) ++x;
//         while (num[y] < pivot) --y;
//         if (x <= y) {
//             swap(num[x], num[y]);
//             ++x, --y;
//         }
//     }
// }

#include "header.h"

int main()
{
    auto a = nullptr;
    auto b = 1;
    return 0;
}
