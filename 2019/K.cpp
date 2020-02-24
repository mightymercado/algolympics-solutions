#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cassert>
using namespace std;
const int mod = 999983;

int _s[50];
int s[50];
struct Polynomial {
    vector<int> coef;
    Polynomial() {} 
    Polynomial operator*(const Polynomial &other) {
        Polynomial ret;
        for (int i = 0; i < other.coef.size() + coef.size(); i++) 
            ret.coef.push_back(0);
        for (int j = 0; j < other.coef.size(); j++) {
            for (int i = 0; i < coef.size(); i++) {
                ret.coef[i + j] = (ret.coef[i + j] + ((long long) coef[i] * other.coef[j]) % mod) % mod;
            }
        }
        // trim leading zeroes
        while (ret.coef.size() > 0 and ret.coef.back() == 0) 
            ret.coef.pop_back();
        return ret;
    }
    bool operator==(const Polynomial &other) {
        if (other.coef.size() != coef.size()) return false;
        for (int i = 0; i < coef.size(); i++) 
            if (coef[i] != other.coef[i]) return false;
        return true;
    }
    int eval(int x) {
        int tot = 0;
        for (int i = coef.size() - 1; i >= 0; i--) {
            tot = ((long long) tot * x) % mod;
            tot = (tot + coef[i]) % mod;
        }
        return tot;
    }
    int degree() {
        return coef.size() - 1;
    }
};

const int neg(int x) {
    return x >= 0 ? mod - x % mod : (- x) % mod;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, k, l = 1, _l;
        scanf("%d %d %d", &n, &k, &_l);
        for (int i = 0; i < _l; i++) {
            scanf("%d", &_s[i]);
        }
        sort(_s, _s + _l);
        s[0] = _s[0];
        // remove duplicates
        for (int i = 1; i < _l; i++) 
            if (_s[i] != _s[i - 1]) 
                s[l++] = _s[i];

        Polynomial prod;
        prod.coef.push_back(1); // 1
        for (int i = 0; i < l; i++) {
            Polynomial cur;
            cur.coef.push_back(neg(s[i]));
            cur.coef.push_back(1);
            prod = prod * cur;
        }
        if (k == prod.degree()) {
            // multiply by different constants
            for (int j = 0; j < l; j++) {
                assert(prod.eval(s[j]) == 0);
            }
            printf("%d\n", n);
            vector<Polynomial> poly;
            poly.push_back(prod);
            int g = -2;
            while (poly.size() < n) {
                Polynomial cur;
                cur.coef.push_back(g);
                poly.push_back(prod * cur);
                if (g < 0) g = -g;
                if (g > 0) g++;
            }
            for (int i = 0; i < poly.size(); i++) {
                printf("%d ", (int) poly[i].coef.size() - 1);
                for (int j = poly[i].coef.size() - 1; j >= 0; j--) {
                    printf("%d ", poly[i].coef[j]);
                }
                printf("\n");
            }

        } else if (k < prod.degree()) {
            // not possible
            printf("0\n");
        } else {
            // generate polynomials
            printf("%d\n", n);
            vector<Polynomial> poly;
            poly.push_back(prod);
            while (poly.size() < n) {
                Polynomial cur;
                int c = rand() % mod;
                cur.coef.push_back(neg(c));
                cur.coef.push_back(1);
                bool match = false;
                cur = prod * cur;
                for (int i = 0; i < poly.size(); i++) 
                    if (poly[i] == cur) { match = true; break; }
                if (match) continue;
                poly.push_back(cur);
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < l; j++) {
                    assert(poly[i].eval(s[j]) == 0);
                }
                printf("%d ", (int) poly[i].coef.size() - 1);
                for (int j = poly[i].coef.size() - 1; j >= 0; j--) {
                    printf("%d ", poly[i].coef[j]);
                }
                printf("\n");   
            }

        }
    }
}