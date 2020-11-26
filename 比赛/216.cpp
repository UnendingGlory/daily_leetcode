#include "../header.h"

// T1
class Solution {
public:
    bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2) {
        string temp1, temp2;
        for(auto i : word1) temp1 += i;
        for(auto i : word2) temp2+= i;
        return temp1 == temp2;
    }
};

// T2
class Solution {
	int N;
	vector<int> temp;
public:
	void dfs(int index, int remain, string &s)
	{
		if(index == N && remain == 0) return;
		
		temp.push_back();

		

	}

    string getSmallestString(int n, int k) {

    }
};