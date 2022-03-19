#include "header.h"

// 哈希表和双向链表
// get用hash,哈希表的value为链表节点类型。时间复杂度为o(1), put用双向链表，复杂度也为o(1)
struct DLinkedNode
{
    int key, value;
    DLinkedNode *pre, *next;
    DLinkedNode(): key(0), value(0), pre(nullptr), next(nullptr){}
    DLinkedNode(int _key, int _value): key(_key), value(_value), pre(nullptr), next(nullptr){}
};

class LRUCache {
    unordered_map<int, DLinkedNode*> m;
    int size, cur = 0;
    DLinkedNode *head, *tail;
public:
    LRUCache(int capacity) {
        size = capacity;
        // 带头结点和尾节点的双向链表
        head = new DLinkedNode();
        tail = new DLinkedNode();
        head->next = tail;
        tail->pre = head;
    }
    
    int get(int key) {
        auto it = m.find(key);
        if(it != m.end())
        {
            // get使用过后更新链表使用状况
            moveToHead(m[key]);
            return m[key]->value;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if(m.find(key) != m.end()) // 存在则更新之
        {
            m[key]->value = value;
            moveToHead(m[key]);
            return;
        }
        // 新生成节点，插入到头部
        DLinkedNode *d = new DLinkedNode(key, value);
        m[key] = d;

        d->next = head->next;
        head->next->pre = d;
        head->next = d;
        d->pre = head;
        ++cur;

        if(cur > size) // 超出容量则删掉尾节点和哈希表对应项
        {
            DLinkedNode *temp = tail->pre;
            m.erase(temp->key);
            temp->pre->next = tail;
            tail->pre = temp->pre;
            free(temp);
            --cur;
        }
    }

    void moveToHead(DLinkedNode *d)
    {
        d->pre->next = d->next;
        d->next->pre = d->pre;
        d->next = head->next;
        head->next->pre = d;
        head->next = d;
        d->pre = head;
    }
};

// LRU Cache简易实现：
// ○ display函数显示LRUCache中目前存在的数字。
// ○ deque + map实现

// We can use stl container list as a double
// ended queue to store the cache keys, with
// the descending time of reference from front
// to back and a set container to check presence
// of a key. But to fetch the address of the key
// in the list using find(), it takes O(N) time.
// This can be optimized by storing a reference
//     (iterator) to each key in a hash map.
 

// 队头是最久未使用的，队尾是最近使用的
class LRUCache {
    // store keys of cache
    list<int> dq;
 
    // store references of key in cache
    unordered_map<int, list<int>::iterator> ma;
    int csize; // maximum capacity of cache
 
public:
    LRUCache(int);
    void refer(int);
    void display();
};
 
// Declare the size
LRUCache::LRUCache(int n)
{
    csize = n;
}
 
// Refers key x with in the LRU cache
void LRUCache::refer(int x)
{
    // not present in cache
    if (ma.find(x) == ma.end()) {
        // cache is full
        if (dq.size() == csize) {
            // delete least recently used element
            int last = dq.back();
 
            // Pops the last element
            dq.pop_back();
 
            // Erase the last
            ma.erase(last);
        }
    }
 
    // present in cache
    else
        dq.erase(ma[x]);
 
    // update reference
    dq.push_front(x);
    ma[x] = dq.begin();
}
 
// Function to display contents of cache
void LRUCache::display()
{
 
    // Iterate in the deque and print
    // all the elements in it
    for (auto it = dq.begin(); it != dq.end();
         it++)
        std::cout << (*it) << " ";
 
    std::cout << std::endl;
}
 
// Driver Code
int main()
{
    LRUCache ca(5);
 
    ca.refer(0);
    ca.refer(1);
    ca.refer(2);
    ca.refer(3);
    ca.refer(4);
    ca.refer(2);
    ca.display();
 
    return 0;
}

