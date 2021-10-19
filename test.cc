#include "header.h"

class Solution {
public:
    int movingCount(int threshold, int rows, int cols) 
    {
        if (rows <= 0 || cols <= 0 || threshold < 0)return 0;
        vector<vector<bool> > visited(rows, vector<bool>(cols));
        return Count(0, 0, visited, threshold, rows, cols);
    }
    int Count(int x, int y, vector<vector<bool> >visited, int thr, int rows, int cols)
    {
        //递归出口 被访问了 出界 超过边际
        if(visited[x][y]||x >= rows||x < 0||y >= cols||y < 0||Sum(x) + Sum(y) > thr) return 0;
        visited[x][y] = true;
        return 1 + Count(x + 1, y, visited, thr, rows, cols) 
                 + Count(x - 1, y, visited, thr, rows, cols)
                 + Count(x, y + 1, visited, thr, rows, cols) 
                 + Count(x, y - 1, visited, thr, rows, cols);
    }
    
      int Sum(int num) {
        int sum = 0;
        while (num > 0) {
            sum += num % 10;
            num /= 10;
        }
        return sum;
      }
};