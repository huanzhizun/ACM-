/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

#include <stdio.h>
#include <ctype.h>
unsigned long long a[1000005];
int n;
unsigned long long FastScan() {
    unsigned long long ret = 0;
    char c;
    while(!isdigit(c = getchar()));
    while(isdigit(c)) {
        ret = ret * 10 + (c - '0');
        c = getchar();
    }
    return ret;
}
void Solve();
typedef unsigned long long un;
void Solve(){
    int i,j;
    for(i=63;i>=0;i--){
        for(j=1;j<=n;j++){
            if(((a[j]>>i)&1)&&(a[j]<(un)1<<(i+1))){
                for(int f=1;f<=n;f++){
                    if(f==j) continue;
                    if((a[f]>>i)&1){
                        a[f]=a[f]^a[j];
                    }
                }
            }
        }
    }
    un s=0;
    for(i=1;i<=n;i++){
        s=s^a[i];
    }
    printf("%llu\n",s);
}
int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) a[i] = FastScan();
    Solve();
    return 0;
}

/* PRESET CODE END - NEVER TOUCH CODE ABOVE */