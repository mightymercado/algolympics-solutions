#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#include <cstdio>
#include <cstring>
#include <algorithm>
const int mod = 104857601;
using namespace std;

int f[5500001];
int invf[5500001];

int modpow(int n, int k) {
    int r = 1;
    while (k) {
        if (k&1) r = (long long) r * n % mod;
        n = (long long) n * n % mod;
        k >>= 1;
    }
    return r;
}

int inv(int n) {
    return modpow(n, mod - 2);
}
int c(int n, int k) {
    return (long long) f[n] * invf[k] % mod * invf[n - k] % mod;
}

int main() {
    int l, w;
    f[0] = 1;
    invf[0] = 1;
    for (int i = 1; i <= 5500001; i++) f[i] = ((long long) f[i - 1] * i) % mod;
    for (int i = 1; i <= 5500001; i++) invf[i] = inv(f[i]);
    scanf("%d %d", &l, &w);l--;w--;
    int tot = 0;
    for (int i = - l / (l - w + 2); i <= w / (l - w + 2); i++) {
        int sign = 1;
        int term = ((long long) sign * c(l + w, l + i * (l - w + 2))) % mod;
        tot = (tot + term) % mod;   
    }
    for (int i = - max(0, w - 1) / (l - w + 2); i <= (l + 1) / (l - w + 2); i++) {
        int sign = mod - 1;
        int term = ((long long) sign * c(l + w, w - 1 + i * (l - w + 2))) % mod;
        tot = (tot + term) % mod;
    }
    printf("%d\n", tot);
}