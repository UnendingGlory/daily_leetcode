from itertools import count
from typing import List
import collections
# 输入：["eat", "tea", "tan", "ate", "nat", "bat"]
# 输出：[["bat"],["nat","tan"],["ate","eat","tea"]]

# Solution1：哈希表。
# 排序好的字符串作为键值，分组作为结果。
# 时间复杂度：O(nklogk)
class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        anagrams = collections.defaultdict(list) # List作为默认value类型
        for s in strs:
            # python字符串是不可变类型，用sorted对string排序返回一个新string
            key = "".join(sorted(s)) 
            anagrams[key].append(s)
        
        return list(anagrams.values())

# Solution2：哈希表。
# 字符串中字母的出现次数作为键值，分组作为结果。
# 时间复杂度：O(nk)
class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        anagrams = collections.defaultdict(list) # List作为默认value类型
        for s in strs:
            counts = [0 for _ in range(26)]
            for c in s:
                counts[ord(c) - ord("a")] += 1
            anagrams[tuple(counts)].append(s)
        return list(anagrams.values())
