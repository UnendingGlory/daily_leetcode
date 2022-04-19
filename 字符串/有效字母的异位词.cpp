#include "header.h"
using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        unordered_map<char, int> S, T;
        for(auto i : s) ++S[i];
        for(auto i : t) ++T[i];
        return S == T ? true : false;
    }
};

int main()
{
    return 0;
}
