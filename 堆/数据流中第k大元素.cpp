#include <bits/stdc++.h>
using namespace std;

// 方法一，第一遍, 56ms，有很多很迷的垃圾操作
class KthLargest {
    int K;
    vector<int> heap;
public:
    KthLargest(int k, vector<int>& nums) {
        //heap.resize(k + 1);
        K = k; // 赋值给私有成员以便成员函数访问
        heap.push_back(0); // 第一个位置无效
        if(nums.empty()) return;
        int cnt;
        sort(nums.begin(), nums.end(), greater<int>());
        printf("%d", heap.size());
        if(nums.size() > k) cnt = k - 1;
        else  cnt = nums.size() - 1;
        for(int j = cnt; j >= 0; j--)
            heap.push_back(nums[j]);
        printf("%d", heap.size());
    }
    
    void downAdjust(int low, int high)
    {
        int i = low, j = i * 2; // j为其左孩子
        while(j <= high)
        {
            if(j + 1 <= high && heap[j + 1] < heap[j]) // 右孩子存在且右孩子值小于左孩子
                ++j; // 换为更小的右孩子
            if(heap[j] < heap[i])
            {
                swap(heap[i], heap[j]);
                i = j;
                j = i * 2;
            }
            else break; // 父节点已经比孩子结点均小
        }
    }

    int add(int val) {
        if(heap.size() - 1 < K)
            heap.push_back(val);
        else if(val > heap[1]) 
            heap[1] = val;
        downAdjust(1, heap.size() - 1);
        return heap[1];
    }
};

// 方法二，对第一遍的修改,本质上是对方法三的底层实现，32ms
class KthLargest {
    int K;
    vector<int> heap;
public:
    KthLargest(int k, vector<int>& nums) {
        K = k; // 赋值给私有成员以便成员函数访问
        heap.push_back(0); // 堆第一个位置无效
        for(int i = 0; i < nums.size(); i++)
        {
            heap.push_back(nums[i]);
            upAdjust(1, heap.size() - 1); // 堆增加元素要upAdjust
            if(heap.size() - 1 > k) deleteHeap();
        }
    }
    
    void deleteHeap() // 删除堆顶元素downAdjust
    {
        heap[1] = heap.back();
        heap.pop_back();
        downAdjust(1, heap.size() - 1);
    }

    void upAdjust(int low, int high)
    {
        int i = high, j = high / 2;
        while(j >= low)
        {
            if(heap[j] > heap[i]) 
            // 若父节点较大。由于除了最新插入的那个节点其余已经是一个堆，
            // 所以没必要像downAdjust那样再有对左右孩子大小的判断
            {
                swap(heap[i], heap[j]);
                i = j;
                j = i / 2;
            }
            else break; // 已经调整完毕
        }
    }

    void downAdjust(int low, int high)
    {
        int i = low, j = i * 2; // j为其左孩子
        while(j <= high)
        {
            if(j + 1 <= high && heap[j + 1] < heap[j]) // 右孩子存在且右孩子值小于左孩子
                ++j; // 换为更小的右孩子
            if(heap[j] < heap[i])
            {
                swap(heap[i], heap[j]);
                i = j;
                j = i * 2;
            }
            else break; // 父节点已经比孩子结点均小
        }
    }

    int add(int val) {
        heap.push_back(val);
        upAdjust(1, heap.size() - 1);
        if(heap.size() - 1 > K) deleteHeap();
        return heap[1];
    }
};

// 方法三，用STL的好处是不需要考虑数组的越界问题,并且会动态调整,40ms
class KthLargest {
public:
    priority_queue<int, vector<int>, greater<int>> pq; // 小顶堆
    int size;

    KthLargest(int k, vector<int> nums) {
        size = k;//将小根堆的大小控制在k
        for(int i = 0; i < nums.size(); i++) {
            pq.push(nums[i]);
            if(pq.size() > k) pq.pop(); // 将多余的元素pop掉
        }
    }
    
    int add(int val) {
        pq.push(val);
        if(pq.size() > size) pq.pop(); // 将多余的元素pop掉
        return pq.top();
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */

int main()
{
    return 0;
}