vector<vector<int64_t>> matMultiply(vector<vector<int64_t>> &matA, vector<vector<int64_t>> &matB, int64_t p = mod) {
    int64_t n1 = matA.size();
    int64_t m1 = matA[0].size();
    int64_t n2 = matB.size();
    int64_t m2 = matB[0].size();
    vector<vector<int64_t>> ans(n1, vector<int64_t>(m2, 0));
    for (int64_t i = 0; i < n1; i++) {
        for (int64_t j = 0; j < m2; j++) {
            for (int64_t k = 0; k < m1; k++) {
                ans[i][j] = (ans[i][j] + ((matA[i][k]) * matB[k][j]) % p) % p;
            }
        }
    }
    return ans;
}
vector<vector<int64_t>> matExp(vector<vector<int64_t>> mat, int64_t y, int64_t p = mod) {
    int64_t n = mat.size();
    vector<vector<int64_t>> res(n, vector<int64_t>(n, 0));
    for (int64_t i = 0; i < n; i++) res[i][i] = 1;
    while (y > 0) {
        if (y & 1)
            res = (matMultiply(res, mat, p));
        y = y >> 1;
        mat = matMultiply(mat, mat, p);
    }
    return res;
}