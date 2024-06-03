#include <bits/stdc++.h>
using namespace std;
constexpr int64_t inf = (int64_t)1e+18;
constexpr int mod = 1000000007;
// https://usaco.guide/gold/divisibility

/*
    Euler Totient Function - phi(n)
    : Counts the number of positive integers in the interval [1,2,3...n] which are coprime to n
    : Two numbers a and b are coprime if their greatest common divisor is equal to 1
    - Prop:
    1. phi(nm) = phi(n)*phi(m) ... where n and m are coprime
        eg. phi(15) = phi(3 * 5) = phi(3)*phi(5) = 2*4 = 8
    2. if(n == prime) phi(n) = n-1
    ... further can be read from "usaco"

*/
int phi(int n) {
    // O(sqrt(n))
    int ans = n;
    for (int p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) { n /= p; }
            ans -= ans / p;
        }
    }
    if (n > 1) { ans -= ans / n; }
    return ans;
}

void precompute() {
    // precomputing phi(n) - O(n * (logn)^2)
	for (int i = 1; i <= MAX_N; i++) { phi[i] = i; }
	for (int i = 2; i <= MAX_N; i++) {
		// If i is prime
		if (phi[i] == i) {
			for (int j = i; j <= MAX_N; j += i) { phi[j] -= phi[j] / i; }
		}
	}
}

/*
    lcm(a,b) = (a*b)/gcd(a,b)
    also these both functions are associative
    lcm(a,b,c) = lcm(lcm(a,b),c) - and similar for gcd
*/

int MAX_N = 1000000;
vector<int> max_div(MAX_N + 1, 0);

vector<int> factor(int n) {
    // calculating prime factors of each nums
    // O(sqrt(n))
    vector<int> ret;
    for (int i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            ret.push_back(i);
            n /= i;
        }
    }
    if (n > 1) { ret.push_back(n); }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // Counting Divisors
    {
        for (int i = 2; i <= MAX_N; i++) { // - precalc maximum prime divisor
            // O(n(logn))
            if (max_div[i] == 0) {
                for (int j = i; j <= MAX_N; j += i) { max_div[j] = i; }
            }
        }

        int n;
        cin >> n;

        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            int div_num = 1;
            while (x != 1) {
                /*
                 * get the largest prime that can divide x and see
                 * how many times it goes into x (stored in count)
                 */
                int prime = max_div[x];
                int cnt = 0;
                while (x % prime == 0) {
                    cnt++;
                    x /= prime;
                }
                div_num *= cnt + 1;
            }
            cout << div_num << '\n';
        }
    }
}