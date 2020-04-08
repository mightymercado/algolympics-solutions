#pragma GCC optimize("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <stdio.h>
#include <algorithm>
#include <assert.h>
#include <numeric>
#include <vector>
#include <string.h>
#include <map>
using u64 = long long;
using namespace std;

int inverse(u64 a, u64 m) {
  int o = m;
  u64 u = 0, v = 1;
  while (a != 0) {
      int t = m / a;
      m -= (u64) t * a; swap(a, m);
      u -= (u64) t * v; swap(u, v);
  }
  assert(m == 1);
  if (u < 0) u = o - (-u) % o;
  u %= o;
  return u;
}

int chinese(vector<int> &rem, vector<int> &mod) {
  int n = mod.size();
  int p = 1;
  for (int i = 0; i < n; i++) {
      p *= mod[i];
  }
  u64 x = 0;
  for (int i = 0; i < n; i++) {
      int y = p / mod[i];
      int inv = inverse(y, mod[i]);
      x += ((u64) y * inv % p) * (u64) rem[i] % p;
      x %= p;
  }
  for (int i = 0; i < mod.size(); i++) {
    assert (x % mod[i] == rem[i]);
  }
  return x;
}

inline int pow_mod(int a, int e, int mod) {
  assert (a >= 0 and e >= 0 and mod > 0);
  a %= mod;
  int ret = 1;
  for (; e; e >>= 1, a = u64(a) * a % mod) {
    if (e & 1) ret = u64(ret) * a % mod;
  }
  return ret;
}

const int maxm = 2 * 1e7;
int phi[maxm+1];
int lp[maxm+1];
vector<int> pr;

inline void calc_sieve() {
  phi[1] = 1;
  for (int i = 2; i <= maxm; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      phi[i] = i - 1;
      pr.push_back(i);
    } else {
      if (lp[i] == lp[i / lp[i]])
        phi[i] = phi[i / lp[i]] * lp[i];
      else
        phi[i] = phi[i / lp[i]] * (lp[i] - 1);
    }
    for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && (u64) i * pr[j] <= maxm; ++j)
      lp[i * pr[j]] = pr[j];
  }
}

int a(int n, int mod);
int m(int n, int mod) {
  // printf("m(%d, %d)\n", n, mod);
  if (n == 0) return 1;
  if (n == 1) return 10 % mod;
  if (n == 2) return 19 % mod;
  if (n == 3) return 199 % mod;
  // if (n == 4) return 19999999999999999999999 % mod;
  assert(mod % 3 == 0);
  return (2 * pow_mod(10, a(n - 1, mod / 3 * 2), mod) % mod + mod - 1) % mod;
}

int a(int n, int mod) {
  if (n == 0) return 0;
  if (n == 1) return 1 % mod;
  if (n == 2) return 2 % mod;
  if (n == 3) return 22 % mod;

  vector<int> mods;
  vector<int> rems;
  if (mod % 2 != 0 and mod % 5 != 0 && mod % 3 != 0) {
    mods.push_back(mod);
  } else {
    int mod_copy = mod;
    int mod5 = 1, mod3 = 1, mod2 = 1;
    while (mod_copy % 2 == 0) { mod_copy /= 2; mod2 *= 2; }
    while (mod_copy % 5 == 0) { mod_copy /= 5; mod5 *= 5; }
    while (mod_copy % 3 == 0) { mod_copy /= 3; mod3 *= 3; }

    if (mod5 > 1) {
      mods.push_back(mod5);
      rems.push_back((u64) (mod5 - 2) * inverse(9, mod5) % mod5);
    } 

    if (mod2 > 1) {
      mods.push_back(mod2);
      if (n > 4) { 
        rems.push_back((u64) (mod2 - 2) * inverse(9, mod2) % mod2);
      } else {
        // edge case
        rems.push_back((u64) (2 * pow_mod(10, 22, mod2) + mod2 - 2) * inverse(9, mod2) % mod2);
      }
    }

    if (mod3 > 1) {
      mods.push_back(mod3);
      int x = m(n, mod3 * 9);
      assert (x > 0 and (x - 1) % 9 == 0);
      rems.push_back((x - 1) / 9);
    }

    mods.push_back(mod_copy);
  }

  if (mods.back() > 1) {
    assert(mods.back() <= maxm);
    int sagot = (2 * pow_mod(10, a(n - 1, phi[mods.back()]), mods.back()) % mods.back() + mods.back() - 2) % mods.back();
    sagot = (u64) sagot * inverse(9, mods.back()) % mods.back();
    rems.push_back(sagot);
  } else {
    mods.pop_back();
  }
  return chinese(rems, mods);
}

int main() {
  calc_sieve();
  int t, N, M;
  // scanf("%d", &t);
  for (M = 1; M <= 10000000; M++) {
  while (t--) {
    scanf("%d %d", &N, &M);
    if (M == 1) {
      printf("0\n");
      continue;
    }
    if (N == 0) {
      printf("%d\n", N % M);
      continue;
    }
    int sagot = (9 * a(N, M) + 1) % M;
    printf("%d\n", sagot);
  }
}

