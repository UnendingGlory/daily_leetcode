#include <bits/stdc++.h>

// 双向循环链表模拟
struct node
{
    int val;
    struct node *pre, *next;
    node(int _val){val = _val;};
};

class MyCircularDeque {
    int size, cur_size;
    node *front, *rear;
public:
    MyCircularDeque(int k) {
        size = k;
        cur_size = 0;
        front = rear = nullptr;
    }
    
    bool insertFront(int value) {
        if(cur_size >= size) return false;
        node *cur = new node(value);
        if(cur_size == 0)
        {
            front = rear = cur;
            cur->next = cur->pre = cur;
        }
        else
        {
            front->pre = cur;
            cur->pre = rear;
            cur->next = front;
            rear->next = cur;
            front = cur;
        }
        ++cur_size;
        return true;
    }
    
    bool insertLast(int value) {
        if(cur_size >= size) return false;
        node *cur = new node(value);
        if(cur_size == 0) 
        {
            front = rear = cur;
            cur->next = cur->pre = cur;
        }
        else
        {
            rear->next = cur;
            cur->next = front;
            cur->pre = rear;
            front->pre = cur;
            rear = cur;
        }
        ++cur_size;
        return true;
    }
    
    bool deleteFront() {
        if(cur_size == 0) return false;
        if(cur_size == 1)
        {
            delete(front);
            front = rear = nullptr;
        }
        else
        {
            node *cur = front->next;
            cur->pre = rear;
            delete(front);
            front = cur;
        }       
        --cur_size;
        return true;
    }
    
    bool deleteLast() {
        if(cur_size == 0) return false;
        if(cur_size == 1)
        {
            delete(rear);
            rear = front = nullptr;
        }
        else
        {
            node *cur = rear->pre;
            cur->next = front;
            delete(rear);
            rear = cur;
        }       
        --cur_size;
        return true;
    }
    
    int getFront() {
        if(cur_size == 0) return -1;
        return front->val;
    }

    int getRear() {
        if(cur_size == 0) return -1;
        return rear->val;
    }
    
    bool isEmpty() {
        return cur_size == 0;
    }
    
    bool isFull() {
        return cur_size == size;
    }
};