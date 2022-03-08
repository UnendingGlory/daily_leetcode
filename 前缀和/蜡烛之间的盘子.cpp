#include "header.h"

// 需要找到区间内左右两侧的第一根蜡烛的位置i, j
// 采用前缀和处理，盘子数量为pre[j] - pre[i - 1]
class Solution {
public:
    vector<int> platesBetweenCandles(string s, vector<vector<int>>& queries) {
      int n = s.size();
      vector<int> pre(n, 0);
      for (int i = 1; i < n; ++i) {
        pre[i] = pre[i - 1];
        if(s[i] == '*') {
          ++pre[i];
        }
      }

      vector<int> left(n); // 记录每个位置左侧最靠近的蜡烛
      for (int i = 0, l = -1; i < n; ++i) {
        if (s[i] == '|') {
          l = i;
        }
        left[i] = l;
      }

      vector<int> right(n); // 记录每个位置右侧最靠近的蜡烛
      for (int i = n - 1, r = -1; i >= 0; --i) {
        if (s[i] == '|') {
          r = i;
        }
        right[i] = r;
      }

      vector<int> ans;
      for (int i = 0; i < queries.size(); ++i) {
        int s = left[queries[i][0]], e = right[queries[i][1]];
        if (s == -1 || e == -1) ans.push_back(0);
        else ans.push_back(pre[e] - pre[s - 1]);
      }
      return ans;
    }
};
