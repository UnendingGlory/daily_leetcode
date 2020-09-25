#include <bits/stdc++.h>
using namespace std;

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