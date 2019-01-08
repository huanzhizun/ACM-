#include<cstdio>
#include<cstring>
#include<set>
#include<algorithm>
using namespace std;
struct pp{
    int id;
    int pi;
};
struct cmp{
    bool operator()(const pp& a,const pp &b)const{
        return a.pi<b.pi;
    }
};
pp ppi;
set<pp,cmp>q;
set<pp,cmp>::iterator it;
int main()
{
    int n,p,k;
    while(1){
        scanf("%d",&n);
        if(!n) break;
        if((n==2||n==3)&&q.size()==0){
            printf("0\n");
            continue;
        }
        if(n==1){
            scanf("%d%d",&k,&p);
            ppi.id=k;
            ppi.pi=p;
            q.insert(ppi);
            continue;
        }
        if(n==2){
            it=q.end();
            it--;
            printf("%d\n",it->id);
            q.erase(*it);
        }
        else{
            it=q.begin();
            printf("%d\n",it->id);
            q.erase(*it);
        }
    }
    return 0;
}