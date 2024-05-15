long sum(long a, long b) {
    long res = (a + b) % MOD;
    if (res < 0) res += MOD;
    return res;
}
long mult(long a, long b) {
    long res = a * b % MOD;
    if (res < 0) res += MOD;
    return res;
}
 
long power(long a, long b) {
    long res = 1;
    while (b > 0) {
        if (b & 1) {
            res = mult(res, a);
        }
        a = mult(a, a);
        b >>= 1;
    }
    return res;
}
 
long inv(long a) {
    return power(a, MOD - 2);
}