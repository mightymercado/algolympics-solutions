#include <cstdio>

char rate[10];
const char* out[] = {
    "OK",
    "OK IF ACCOMPANIED",
    "ACCESS DENIED"
};
int main() {
    int a;
    scanf("%d %s", &a, rate);
    if (rate[0] == 'G') {
        puts(out[0]);
    } else if (rate[0] == 'P') {
        if (a < 13) {
            puts(out[1]);
        } else {
            puts(out[0]);
        }
    } else if (rate[3] == '3') {
        if (a < 13) {
            puts(out[2]);
        } else {
            puts(out[0]);
        }
    } else if (rate[3] == '6') {
        if (a < 16) {
            puts(out[2]);
        } else {
            puts(out[0]);
        }  
    } else if (rate[3] == '8') {
        if (a < 18) {
            puts(out[2]);
        } else {
            puts(out[0]);
        }
    }
}