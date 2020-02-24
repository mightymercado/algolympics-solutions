#include <cstdio>
#include <algorithm>
#include <vector>
#include <deque>
#include <cstring>
using namespace std;

int n, m;
bool visited[81] = {0};
char initial[81];
char step[81];
vector< pair<int,int> > solution;

bool f(int zeroes) {
    // printf("f(%d)\n", zeroes);
    if (zeroes == 0) return true;
    if (visited[zeroes]) return false;
    visited[zeroes] = true;
    for (int z = min(zeroes, m); z >= 0; z--) {
        int o = m - z;
        if (n - zeroes < o) continue;//zero supply
        // pick `o` ones and `z` zeroes
        // turn ones into zeroes
        // turn zeroes into ones
        solution.push_back(make_pair(o, z));
        // printf("%d %d\n", o, z);
        if (f(zeroes - z + o)) return true;
        solution.pop_back();
    }
    return false;
}
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        memset(visited, 0, sizeof visited);
        scanf("%d %d", &n, &m);
        scanf("%s", initial);
        solution.clear();
        for (int i = 0; i < n; i++) step[i] = '0';
        step[n] = '\0';
        int z = count(initial, initial + n, '0');
        if (f(z)) {
            printf("%d\n", (int) solution.size());
            deque< int > num[2];
            for (int i = 0; i < n; i++) num[initial[i] - '0'].push_back(i);
            for (int i = 0; i < solution.size(); i++) {
                int pick_o = solution[i].first;
                int pick_z = solution[i].second;
                while (pick_o--) {
                    int x = num[1].front();
                    num[1].pop_front();
                    initial[x] = '0'; step[x] = '1';
                    num[0].push_back(x);
                }
                while (pick_z--) {
                    int x = num[0].front();
                    num[0].pop_front();
                    initial[x] = step[x] = '1';
                    num[1].push_back(x);
                }
                printf("%s\n", step);
                for (int i = 0; i < n; i++) step[i] = '0';
                step[n] = '\0';
            }
        } else {
            printf("CATACLYSM IMMINENT - TIME TO HOARD FACE MASKS\n");
        }
    }
}