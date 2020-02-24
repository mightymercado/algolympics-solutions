#include <cstdio>
#include <algorithm>
using namespace std;
pair<long long, long long> wh[100000];
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &wh[i].second);
    }
    for (int i = 0; i < n; i++) {
        scanf("%lld", &wh[i].first);
    }
    sort(wh, wh + n);
    for (int i = 0; i < n; i++) {
        printf("%lld%s", wh[i].second, i == n - 1 ? "" : " ");
    }
}