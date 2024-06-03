int64_t sum(int64_t a, int64_t b) {
    int64_t res = (a + b) % MOD;
    if (res < 0) res += MOD;
    return res;
}
int64_t mult(int64_t a, int64_t b) {
    int64_t res = a * b % MOD;
    if (res < 0) res += MOD;
    return res;
}
 
int64_t power(int64_t a, int64_t b) {
    int64_t res = 1;
    while (b > 0) {
        if (b & 1) {
            res = mult(res, a);
        }
        a = mult(a, a);
        b >>= 1;
    }
    return res;
}
 
int64_t inv(int64_t a) {
    return power(a, MOD - 2);
}