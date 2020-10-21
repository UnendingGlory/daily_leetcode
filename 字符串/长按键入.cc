#include <./header.h>


class Solution {
public:
    bool isLongPressedName(string name, string typed) {
        int p = 0, q = 0;
        while(q < typed.size())
        {
            if(p < name.size() && name[p] == typed[q]) ++p, ++q;
            else if(q >= 1 && typed[q] == typed[q - 1]) ++q;
            else return false;
        }
        return p == name.size();
    }
};