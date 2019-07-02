# [「JOISC 2018 Day 3」比太郎的聚会](https://loj.ac/problem/2838)

## 题意：

​	给你一个$DAG$，若干组询问，每次给出一个终点和若干个点，问从给出点以外的点出发，到达终点的最长路。（$|V|\leq 1e5 |E|\leq 1e6 \sum Y_i\leq 1e5$）

## 题解：

​	一开始没看见最后那个条件，不会做。。。

​	既然有那个$\sum Y_i\leq 1e5$就好办了，把$Y_i\geq \sqrt{Q}$的询问暴力$O(n)$DP。剩下的直接预处理。$O((|V|+|E|)\sqrt{Q})$完成。

（UPD：18.12.11 14:11 原来的代码是错的，之前交的时候loj还没有数据。至于错哪了：

```c++
if(y<=B) -> if(y<B)
```

出题人也是懂啊。。。。

## 代码：

```c++
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<assert.h>
#define fo(i,l,r) for(int i=l;i<=r;i++)
#define of(i,l,r) for(int i=l;i>=r;i--)
#define fe(i,u) for(int i=head[u];i;i=e[i].next)
#define rfe(i,u) for(int i=h[u];i;i=e[i].next)
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
inline void open(const char *s)
{
	#ifndef ONLINE_JUDGE
	char str[20];
	sprintf(str,"%s.in",s);
	freopen(str,"r",stdin);
	sprintf(str,"%s.out",s);
	freopen(str,"w",stdout);
	#endif
}
inline int rd()
{
	static int x,f;
	x=0;f=1;
	char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())x=x*10+ch-'0';
	return f>0?x:-x;
}
const int N=100010,B=320;
struct edge{
	int v,next;
	edge(int v=0,int next=0):v(v),next(next){}
}e[N<<2];
int n,m,dis[N][321],st[N][321],d[N];
int tot=0,head[N],h[N];
int vis[N],used[N];

inline void add(int u,int v)
{
	e[++tot]=edge(v,head[u]);head[u]=tot;
	e[++tot]=edge(u,h[v]);h[v]=tot;
}

inline bool chk(int u,int t,int id)
{
	if(used[st[u][t]]!=id)return 0;
	return 1;
}

inline void gao(int u)
{static int t1[321],t2[321];
	fe(i,u){
		int v=e[i].v;
		int j=0,k=0,tt=0;
		while(tt<B){
			while(j<B&&chk(u,j+1,i))++j;
			while(k<B&&chk(v,k+1,i))++k;
			if(dis[u][j+1]+1>dis[v][k+1]){
				t1[++tt]=dis[u][++j]+1;
				t2[tt]=st[u][j];
				used[t2[tt]]=i;
			}
			else{
				t1[++tt]=dis[v][++k];
				t2[tt]=st[v][k];
				used[t2[tt]]=i;
			}
			if(t2[tt]==v)break;
		}
		fo(j,1,tt)dis[v][j]=t1[j],st[v][j]=t2[j];
	}
}

int main()
{
	open("hh");
	memset(dis,-0x3f,sizeof dis);
	n=rd();m=rd();int Q=rd();
	fo(i,1,m){
		int u=rd(),v=rd();
		add(u,v);assert(u<v);
	}
	fo(i,1,n)dis[i][1]=0,st[i][1]=i;
	fo(i,1,n)gao(i);
	while(Q){
		int x=rd(),y=rd();
		fo(i,1,y)vis[rd()]=Q;
		if(y<B){
			int ans=-1;
			fo(i,1,B)if(vis[st[x][i]]!=Q){
				if(!st[x][i])break;
				ans=dis[x][i];break;
			}
			printf("%d\n",ans);
		}
		else{
			int ans=-1;
			fo(i,1,x-1)d[i]=-1000000000;d[x]=0;
			of(u,x,1)
				rfe(i,u){
					int v=e[i].v;
					d[v]=max(d[v],d[u]+1);
				}
			fo(i,1,x)if(vis[i]!=Q)ans=max(ans,d[i]);
			printf("%d\n",ans);
		}
		--Q;
	}
	return 0;
}
```

