#include "header.h"
using namespace std;

class Solution {
public:
    string kthSmallestPath(vector<int>& destination, int k) {
		int numH = destination[1], numV = destination[0];
		// 先生成全排列排序
		string str;
		for(int i = 0; i < numH; ++i) str.push_back('H');
		for(int i = 0; i < numV; ++i) str.push_back('V');
		int i = 1;
		do
		{
			if(i++ == k) return str;
		} while (next_permutation(str.begin(), str.end()));
		return "";
    }
};

int main(int argc, char **argv)
{
    Solution s;
    vector<int> a {12, 13};
    std::cout << s.kthSmallestPath(a, 784173);
    return 0;
}