#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include<algorithm>
#define maxn 1000010
#define inf 31
using namespace std;
char s[maxn];
int  N;
unsigned long long bit[maxn],f[maxn],t[maxn];
void init(void) {
    bit[0] = 1;
    for (int i = 1; i <=maxn-10;i++) {
        bit[i] = (unsigned long long)bit[i-1]*inf;
    }
}
int low(int x){
    return x & -x;
}
void add(int x, unsigned long long c[], unsigned long long val) {
    for (int i = x; i <= N; i += low(i)) {
        c[i] += val;
    }
}
unsigned long long sum(int x, unsigned long long c[]) {
    unsigned long long ret = 0;
    for (int i = x; i > 0; i -= low(i)) {
        ret += c[i];
    }
    return ret;
}
int panduan(int a, int b) {
    int x = a-1, y = N-b, z;
    z = max(x, y);
    unsigned long long ll = sum(b, f) - sum(a-1, f);
    unsigned long long rr = sum(N-a+1, t) - sum(N-b, t);
    ll *= bit[z-x];
    rr *= bit[z-y];
    return ll == rr;
}
void merg(int x, int val) {
    add(x, f, (val-s[x])*bit[x-1]);
    add(N+1-x, t, (val-s[x])*bit[N-x]);
    s[x] = val;
}
int main() {
    char cc[5], ch[5];
    int a, b,Q;
    init();
    while (scanf("%s", s+1)!=EOF) {
        N = (int)strlen(s+1);
        memset(f, 0, sizeof (long long) * (N+1));
        memset(t, 0, sizeof (long long) * (N+1));
        for (int i = 1, j = N; i <= N; ++i, --j) {
            s[i] -= 'a';
            add(i, f, s[i]*bit[i-1]);
            add(j, t, s[i]*bit[j-1]);
        }
        scanf("%d", &Q);
        for(int i=0;i<Q;i++) {
            scanf("%s", cc);
            if (cc[0] == 'Q') {
                scanf("%d %d", &a, &b);
                if(panduan(a, b)){
                    printf("Yes\n");
                }
                else{
                    printf("No\n");
                }
            } else {
                scanf("%d %s", &a, ch);
                merg(a, ch[0]-'a');
            }
        }
        printf("\n");
    }
    return 0;
}