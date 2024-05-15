def min_distance(a, b):
    a = a.lower()
    res = ''
    mn = 100000
    n = len(a)
    for word in b:
        m = len(word)
        word = word.lower()
        dp = [[0] * (m + 1) for _ in range(n + 1)]
        for j in range(n + 1):
            for k in range(m + 1):
                if j == 0 or k == 0:
                    dp[j][k] = j + k
                    continue
                if a[j - 1] == word[k - 1]:
                    dp[j][k] = dp[j - 1][k - 1]
                else:
                    dp[j][k] = min(min(dp[j - 1][k - 1], dp[j - 1][k]), dp[j][k - 1]) + 1
        if dp[n][m] < mn:
            mn = dp[n][m]
            res = word
    res = res.capitalize()
    return res

# Example usage:
a = "hello"
b = ["hi", "world", "how", "are", "you"]
print(min_distance(a, b))  # Output: Hi
