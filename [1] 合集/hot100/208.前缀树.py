# Trie（发音类似 "try"）或者说 前缀树 是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。
# 这一数据结构有相当多的应用情景，例如自动补完和拼写检查。

# word 和 prefix 仅仅由小写字母组成。
# 结点仅仅记录next映射和当前结点是否为结束结点即可。
class TrieNode:
    def __init__(self) -> None:
        self.next = [None for _ in range(26)]
        self.isEnd = False

class Trie:

    def __init__(self):
        self.root = TrieNode()

    def insert(self, word: str) -> None:
        p = self.root
        for ch in word:
            idx = ord(ch) - ord('a')
            if p.next[idx] is None:
                p.next[idx] = TrieNode()
            p = p.next[idx]
        p.isEnd = True

    def search(self, word: str) -> bool:
        # 从根结点开始检查是否刚好存在单词 word
        p = self.root
        for ch in word:
            idx = ord(ch) - ord('a')
            if p.next[idx] is None:
                return False
            p = p.next[idx]
        return p.isEnd

    def startsWith(self, prefix: str) -> bool:
        # 只需要存在前缀即可
        p = self.root
        for ch in prefix:
            idx = ord(ch) - ord('a')
            if p.next[idx] is None:
                return False
            p = p.next[idx]
        return True

# Your Trie object will be instantiated and called as such:
# obj = Trie()
# obj.insert(word)
# param_2 = obj.search(word)
# param_3 = obj.startsWith(prefix)
