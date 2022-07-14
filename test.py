def parseNum(s, i):
    '''s[i]为数字，解析当前数字'''
    sum = 0
    while i < len(s) and '0' <= s[i] <= '9':
        sum *= 10
        sum += ord(s[i]) - ord('0')
        i += 1
    return sum, i


s = "1234"
sum, i = parseNum(s, 0)
print(sum)
