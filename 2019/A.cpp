#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

char a[100001];
char b[100001];

const char *sagot[] = {
    "You're logged in!",
    "You almost got it. You're wrong in just one spot.",
    "You almost got it, but you're wrong in two spots.",
    "You're wrong in three spots.",
    "What you entered is too different from the real password."
};

int solve(int i, int j, int k) {
    if (i < 0 and j < 0) return 0;
    if (i < 0 or j < 0) return min(4, max(i + 1, j + 1));
    while (i >= 0 and j >= 0 and a[i] == b[j]) i--, j--;
    if (i < 0 and j < 0) return 0;
    if (k == 0) return min(4, max(i + 1, j + 1));
    int best = 4;
    // replace 
    best = min(best, 1 + solve(i - 1, j - 1, k - 1));
    // add
    best = min(best, 1 + solve(i - 1, j, k - 1));
    // remove
    best = min(best, 1 + solve(i, j - 1, k - 1));
    return best;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%s %s", b, a);
        int n = strlen(a);
        int m = strlen(b);
        int si = solve(n - 1, m - 1, 3);
        puts(sagot[si]);
    }
}