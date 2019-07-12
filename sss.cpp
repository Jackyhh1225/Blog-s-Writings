#include<stdio.h>
#include<map>
#include<algorithm>
using namespace std;
const int N=1e6+10;
int n,m;
int v[N];
int g[N],a[N],M;
bool vis[N];
inline int p(int i,int j,int t){
    return t*n*m+(i-1)*m+j;
}
void dec_(map<int,int>&m,int x){
    if(!--m[x])m.erase(x);
}
struct dat{
    map<int,int>c,cc;
    void clear(){
        c.clear();
        cc.clear();
    }
    void inc(int x){
        if(c.count(x))dec_(cc,c[x]);
        cc[++c[x]]++;
    }
    void dec(int x){
        dec_(cc,c[x]);
        dec_(c,x);
        if(c.count(x))cc[c[x]]++;
    }
    int val(){
        return cc.rbegin()->first;
    }
}d[N];
int bl[N],C;
void del(){
    int x0,y0,x1,y1,a,b,c,d,x,y;
    scanf("%d%d%d%d",&x0,&y0,&x1,&y1);
    if(x0==x1){
        if(y0>y1)swap(y0,y1);
        a=p(x0+1,y1,0);
        b=p(x0,y1,3);
        c=p(x0,y1,2);
        d=p(x0+1,y1,1);
    }else{
        if(x0>x1)swap(x0,x1);
        a=p(x1,y0+1,3);
        b=p(x1,y0,2);
        c=p(x1,y0,1);
        d=p(x1,y0+1,0);
    }
    if(bl[a]!=bl[c]){
        for(x=b,y=d;x!=c&&y!=a;x=g[x],y=g[y]);
        if(x==c){
            ::d[bl[a]].dec(v[a]);
            x=b;
            do{
                if(v[x])::d[bl[a]].inc(v[x]);
                bl[x]=bl[a];
                x=g[x];
            }while(x!=c);
            ::d[bl[c]].clear();
        }else{
            ::d[bl[c]].dec(v[c]);
            x=d;
            do{
                if(v[x])::d[bl[c]].inc(v[x]);
                bl[x]=bl[c];
                x=g[x];
            }while(x!=a);
            ::d[bl[a]].clear();
        }
    }else{
        for(x=b,y=d;x!=a&&y!=c;x=g[x],y=g[y]);
        if(x==a){
            ::d[bl[c]].dec(v[c]);
            ::d[bl[c]].dec(v[c]);
            C++;
            x=b;
            do{
                bl[x]=C;
                if(v[x]){
                    ::d[bl[c]].dec(v[x]);
                    ::d[C].inc(v[x]);
                }
                x=g[x];
            }while(x!=a);
        }else{
            ::d[bl[a]].dec(v[a]);
            ::d[bl[a]].dec(v[a]);
            C++;
            x=d;
            do{
                bl[x]=C;
                if(v[x]){
                    ::d[bl[a]].dec(v[x]);
                    ::d[C].inc(v[x]);
                }
                x=g[x];
            }while(x!=c);
        }
    }
    g[a]=b;
    v[a]=0;
    g[c]=d;
    v[c]=0;
}
int get(){
    int x1,y1,x2,y2,d,x;
    scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&d);
    if(x1==x2){
        if(y1>y2)swap(y1,y2);
        x=d==0?p(x1,y2,2):p(x1+1,y2,0);
    }else{
        if(x1>x2)swap(x1,x2);
        x=d==0?p(x2,y1,1):p(x2,y1+1,3);
    }
    return x;
}
void query(){
    printf("%d\n",d[bl[get()]].val());
}
int main(){
	freopen("hh.in","r",stdin);
    int q,i,j,x,op;
    scanf("%d%d%d",&n,&m,&q);
    for(j=1;j<=m;j++){
        g[p(1,j,0)]=p(1,j,1);
        if(j<m)g[p(1,j,1)]=p(1,j+1,0);
    }
    for(i=1;i<=n;i++){
        g[p(i,m,1)]=p(i,m,2);
        if(i<n)g[p(i,m,2)]=p(i+1,m,1);
    }
    for(j=m;j>0;j--){
        g[p(n,j,2)]=p(n,j,3);
        if(j>1)g[p(n,j,3)]=p(n,j-1,2);
    }
    for(i=n;i>0;i--){
        g[p(i,1,3)]=p(i,1,0);
        if(i>1)g[p(i,1,0)]=p(i-1,1,3);
    }
    for(i=1;i<n;i++){
        for(j=1;j<m;j++){
            g[p(i,j,2)]=p(i+1,j,1);
            g[p(i+1,j,1)]=p(i+1,j+1,0);
            g[p(i+1,j+1,0)]=p(i,j+1,3);
            g[p(i,j+1,3)]=p(i,j,2);
        }
    }
    for(i=1;i<=n;i++){
        for(j=0;j<=m;j++){
            scanf("%d",&x);
            if(j==0)v[p(i,1,3)]=x;
            if(j==m)v[p(i,m,1)]=x;
            if(0<j&&j<m&&x){
                g[p(i,j,1)]=p(i,j,2);
                v[p(i,j,1)]=x;
                g[p(i,j+1,3)]=p(i,j+1,0);
                v[p(i,j+1,3)]=x;
            }
        }
    }
    for(i=0;i<=n;i++){
        for(j=1;j<=m;j++){
            scanf("%d",&x);
            if(i==0)v[p(1,j,0)]=x;
            if(i==n)v[p(n,j,2)]=x;
            if(0<i&&i<n&&x){
                g[p(i,j,2)]=p(i,j,3);
                v[p(i,j,2)]=x;
                g[p(i+1,j,0)]=p(i+1,j,1);
                v[p(i+1,j,0)]=x;
            }
        }
    }
    for(i=1;i<=n*m*4;i++){
        if(!vis[i]){
            M=0;
            for(j=i;!vis[j];j=g[j])vis[a[++M]=j]=1;
            C++;
            for(j=1;j<=M;j++){
                bl[a[j]]=C;
                if(v[a[j]])d[C].inc(v[a[j]]);
            }
        }
    }
    while(q--){
        scanf("%d",&op);
        if(op==1)
            del();
        else
            query();
    }
}
