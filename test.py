class Solution:
    def concatenatedBinary(self, n: int) -> int:
        res = []
        for i in range(n, 0, -1):
            j = i
            while j :
                res.append('1' if j & 1 else '0')
                j >>= 1
        res = res[::-1]
        ans = 0
        r = 0
        for i in range(len(res) - 1, -1, -1):
            if res[i] is '1':
                ans += 1 * pow(2, r)
            r = r + 1
        return ans % (1000000000 + 7)