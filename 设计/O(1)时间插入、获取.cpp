#include <../header.h>

class RandomizedCollection {
    int n;
	// maintain the index
	unordered_map<int, unordered_multiset<size_t>> um; 
	vector<int> data;
public:
    /** Initialize your data structure here. */
    RandomizedCollection() {
		n = 0;
    }
    
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
		auto iter = um.find(val);
		um[val].insert(data.size());
		data.emplace_back(val);
		++n;
		if(iter == um.end()) return true;
		else return false;
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
		auto iter = um.find(val);
		if(iter == um.end()) return false;
		// // swap a data with the last element
		auto swapped = *um[val].begin();
		std::swap(data[swapped], data[n - 1]);
        // swap位置后data[swapped]的um要改变
		um[data[swapped]].erase(n - 1);
		um[data[swapped]].insert(swapped);
		--n;
		um[val].erase(um[val].begin());
		return true;
    }
    
    /** Get a random element from the collection. */
    int getRandom() {
		return data[rand() % n];
    }
};
