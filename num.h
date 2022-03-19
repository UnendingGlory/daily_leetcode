#include <vector>

const std::vector<int> *seq1(int size);
const std::vector<int> *seq2(int size);
const std::vector<int> *seq3(int size);
const std::vector<int> *seq4(int size);
const std::vector<int> *seq5(int size);
const std::vector<int> *seq6(int size);

const int seq_count = 6;
extern const std::vector<int>* (*seq_array[seq_count])(int);