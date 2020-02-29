#include <cstdio>
#include <algorithm>
using namespace std;
int grid[100][100];
int r, c, x, y;

bool solve(void) {
    const char *L = "L";
    const char *U = "U";
    const char *D = "D";
    const char *R = "R";
    // four corners
    if (c == 1 && x > 1 and x < r) return false;
    if (r == 1 && y > 1 and y < c) return false;
    if ((x == 1 or x == r) and (y == 1 or y == c)) {
        for (int j = 0; j < r; j++) {
            for (int i = 0; i < c - 1; i++) 
                printf(((y == 1) + j) % 2 == 1 ? "R" : "L");
            if (j < r - 1) 
                printf(x == 1 ? "D" : "U");
        }
        return true;
    } else {
        if (x == 1) {
            x = r;
            swap(U, D);
        }
        if (y == c) {
            y = 1;
            swap(L, R);
        }

        if (x % 2 == 0 && (c - y) % 2 == 1) {
            // good
        } else if (x % 2 == 1 && y % 2 == 1) { 
            // good
        } else if (y % 2 == 1 && (c - y) % 2  == 1) {
            // good
        } else if (x % 2 == 0 && c - y + 1 != c && (c - (c - y + 1)) % 2 == 1) {
            // fix y
            y = c - y + 1;
            swap(L, R);
        } else if ((r - x + 1) % 2 == 0 && r - x + 1 != 1 && (c - y) % 2 == 1) {
            // fix x
            x = r - x + 1;
            swap(U, D);
        } else if ((r - x + 1) % 2 == 1 && r - x + 1 != 1 && y % 2 == 1) {
            // fix x
            x = r - x + 1;
            swap(U, D);
        } else if ((r - x + 1) % 2 == 0 && r - x + 1 != 1 && c - y + 1 != c && (c - (c - y + 1)) % 2 == 1) {
            // fix x and y
            y = c - y + 1;
            swap(L, R);
        } else if (x % 2 == 1 && c - y + 1 != c && (c - y + 1) % 2 == 1) {
            // fix y
            y = c - y + 1;
            swap(L, R);
        } else if (x == r && (x % 2 == 0 || y % 2 == 1)) {
            // good
        } else {
            return false;
        }

        if (x % 2 == 0) {
            for (int j = 0; j < x; j++) {
                for (int i = 0; i < y - 1; i++) printf("%s", j % 2 == 0 ? L : R);
                if (j < x - 1) printf("%s", U);
            }
        } else if (y % 2 == 1) {
            // only works when y - 1 is even
            for (int i = 0; i < y - 1; i++) printf("%s", L);
            for (int j = 0; j < y; j++) {
                for (int i = 0; i < x - 1 - (j > 0); i++) printf("%s", j % 2 == 0 ? U : D);
                if (j < y - 1) printf("%s", R);
            }
        } 

        if (x == r) {
            printf("%s", R);
            for (int j = 0; j < x; j++) {
                for (int i = 0; i < c - y - 1; i++) printf("%s", j % 2 == 0 ? R : L);
                if (j < x - 1) printf("%s", D);
            };
        } else if (x % 2 == 1) {
            printf("%s", R);
            for (int j = 0; j < x; j++) {
                for (int i = 0; i < c - y - 1; i++) printf("%s", j % 2 == 0 ? R : L);
                if (j < x - 1) printf("%s", D);
            };
        } else if ((c - y) % 2 == 1) {
            for (int j = 0; j < c - y; j++) {
                printf("%s", R);
                for (int i = 0; i < x - 1; i++) printf("%s", j % 2 == 0 ? D : U);
            }
        } 
        
        if (x < r) printf("%s", D);
        for (int j = 0; j < r - x; j++) {
            for (int i = 0; i < c - 1; i++) {
                printf("%s", j % 2 == 0 ? L : R);
            }
            if (j < r - x - 1) printf("%s", D);
        }
        return true;
    }
    
    return false;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d %d %d", &r, &c, &x, &y);
        if (!solve()) printf("IMPOSSIBLE");
        printf("\n");
    }
}