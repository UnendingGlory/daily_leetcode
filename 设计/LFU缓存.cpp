#include <bits/stdc++.h>
using namespace std;

struct item
{
    int key, value, time, cnt; // 值，时间，出现次数
    bool operator < (const item &a) const
    {
        // time越大则越近使用，优先去除最近没用过的
        return cnt == a.cnt ? time < a.time : cnt < a.cnt;
    }
};

// Least Frequent最不经常使用, put和get都算使用
class LFUCache {
    // 使用map来快速存取，由于map对值排序需要转换为vector再sort，时间复杂度为(nlogn)
    // 因此再开个set实现自动排序以及查找修改操作
    int size, cur_size, time;
    unordered_map<int, item> m;
    set<item> s;
public:
    LFUCache(int capacity) {
        size = capacity;
        cur_size = time = 0;
    }
    
    // 存在于缓存中，取得键值，不存在返回-1
    int get(int key) {
        ++time;
        auto it = m.find(key);
        if(it == m.end()) return -1;
        item cur = m[key];
        s.erase(cur);
        ++cur.cnt;
        cur.time = time;
        m[key] = cur;
        s.insert(cur);
        return it->second.value;
    }
    
    // 键不存在，则插入值。缓存达到容量时，去除最不经常使用的项目。
    // if there is a tie，去除最近的键值
    void put(int key, int value) {
        if(size == 0) return;
        ++time;
        auto it = m.find(key);
        printf("%d\n", cur_size);
        // 找不到应该插入
        if(it == m.end())
        {
            if(cur_size == size)
            {
                m.erase(s.begin()->key); // 先删m
                s.erase(s.begin());
                --cur_size;
            }
            item cur = {key, value, time, 1};
            m[key] = cur;
            s.insert(cur);
            ++cur_size;
        }
        // 若能找到
        else
        {
            // set中元素不可修改
            item cur = m[key];
            s.erase(cur);
            cur.value = value;
            ++cur.cnt;
            cur.time = time;
            m[key] = cur;
            s.insert(cur);
        } 
    }
};

int main()
{
    return 0;
}