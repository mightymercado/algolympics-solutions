#include <cstdio>
#include <algorithm>
#include <tuple>
#include <queue>
#include <set>
#include <cstring>
using namespace std;

int n, m, K;
int sx, sy, ex, ey;
char g[5001][5001];
bool vis[5001][51];

int dx[] = {-1, 0, 0, 1};
int dy[] = {0, -1, 1, 0};

inline bool valid(int x, int y) {
    return x >= 0 and x < n and y >= 0 and y < m;
}

int bfs() {
    typedef tuple<int,int,int,int> T;
    auto cmp = [](const T &a, const T &b) { return get<0>(a) > get<0>(b); };
    priority_queue< T, vector<T>, decltype(cmp)> q(cmp); // reduce comparison cost by only comparing first
    q.push(make_tuple(0, 0, sx, sy));
    while (q.size() > 0) {
        auto e = q.top(); q.pop();
        int d = get<0>(e);
        int k = get<1>(e);
        int x = get<2>(e);
        int y = get<3>(e);
        if (vis[x * m + y][k]) continue;
        // printf("d = %d, (%d, %d), k = %d\n", d, x, y, k);
        vis[x * m + y][k] = true;
        if (x == ex and y == ey) return d;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (valid(nx, ny)) {
                if (g[nx][ny] == '.' or g[nx][ny] == 'B') {
                    q.push(make_tuple(d + 1, k, nx, ny));
                } else if (g[nx][ny] == 'D') {
                    /*
                        EDGE case?
                        we can time travel and close any previously opened door and
                        adjust the time cost
                        But, we can't do it when we're currently at a door (i.e. g[x][y] == 'D') because
                        we can't close it. we can only close it after moving to an adjacent cell.

                        Otherwise, we can close any of the K open doors.
                    */
                    if (g[x][y] == 'D' and k == 1 and K == 1) {
                        // cant do shit
                    } else {
                        q.push(make_tuple(d + 2 + (k == K), k + (k < K), nx, ny)); // open a door and leave
                    }
                }
            }
        }
    }
    return -1;
}
int main() {
    int t;
    scanf("%d", &t);
    
    while (t--) {
        memset(vis, 0, sizeof vis);
        scanf("%d %d %d", &n, &m, &K);
        for (int i = 0; i < n; i++) {
            scanf("%s", g[i]);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (g[i][j] == 'A') { sx = i, sy = j; }
                if (g[i][j] == 'B') { ex = i, ey = j; }
            }
        }
        // printf("%d %d %d %d\n", sx, sy, ex, ey);
        int sagot = bfs();
        if (sagot == -1) puts("HAHAHUHU");
        else printf("%d\n", sagot);
    }
}