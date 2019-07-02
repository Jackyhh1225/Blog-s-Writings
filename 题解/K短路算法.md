# K短路算法

​	这是一个经典问题，但是我在网上只找到了$A^*$算法，是$O(NK)$，复杂度十分不优秀。后来我找到了可以在$O(nlogn+m+klogk)$时间内解决此问题的方法，写篇博客记录。

## 问题形式：

​	已知源点$S$，汇点$T$，图$G=<V,E>$，求从$S$出发，到$T$的所有路径中可重复经过一个点不严格递增第$K$短的路径长度。



##算法一：

​	一般的$A^*$算法是先以$T$为起点，算出所有点到$T$的最短路。并用此作为估价函数：$F_u(d)=d+dis_{v\rightarrow T}$（当前在点$u$，路径长$d$）。类似狄杰斯特拉更新，堆里存的是估价值。直到找到$k$条从$S$到$T$的路径。但这个算法在面对一个$n$元环的时候，它的时间复杂度是$O(nk)$的。

​	为了在较短的时间内求解，我们需要使用：最短路径树和可持久化堆。

## 算法二：

​	我们把以$T$为根的最短路径树建出来（注意这棵树是儿子指向父亲的）。记这棵树为$T_p=<V,E_t>$。对于一条从$u$到$T$的路径一定是经过若干条树上的边和非树上的边，我们记这样的路径为​$P(u)$，记$P_s(u)=P(u)-E_t$，即为路径$P(u)$中非树边的集合。

​	我们可以发现$P_s(u)$的相邻的边$e,f$，$from_f$在$T_p$上一定是$to_e$自己或祖先，而我们走这条路径对当前最短路的贡献是可以简单地算出来的，那么一个算法已经呼之欲出：

​	我们对当前状态记录我们当前走的是哪条非树边，寻找可以作为这一条边相邻边出现的对当前权值修改贡献最小的边转移。或者我们跳到当前这条边的终点，寻找这个点可以走的最小的非树边转移。

​	现在问题变成，我们需要一种数据结构，可以支持我们迅速找到下一条边，也就是插入，删除，查询最大值。另外，我们发现一个点所有可转移边一部分是它的出边，一部分是来自它祖先的边。这使得我们需要一个可持久化的数据结构。那么可持久化堆可以满足我们。

### 最终算法流程：

1. 建出以$T$为根的最短路径树。
2. 遍历最短路径树，将从这个点出发的非树边加入堆中，并这个点的堆继承给儿子。
3. 如果$K=1$，直接输出最短路，否则使用优先队列，通过上面的方法转移。转移$K-1$次得到的状态即为答案。

### 代码：

​	可持久化堆我是用左偏树实现的。

```c++
#include<bits/stdc++.h>
#define fo(i,l,r) for(int i=l;i<=r;i++)
#define of(i,l,r) for(int i=l;i>=r;i--)
#define fe(i,u) for(int i=head[u];i;i=e[i].next)
#define fe2(i,u) for(int i=head2[u];i;i=e2[i].next)
#define el putchar('\n')
#define ta putchar('	')
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
inline void open(const char *s)
{
	#ifndef ONLINE_JUDGE
	char str[20];
	sprintf(str,"%s.in",s);
	freopen(str,"r",stdin);
//	sprintf(str,"%s.out",s);
//	freopen(str,"w",stdout);
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
const int N=150010;
int n,K,vs,vt,d[N],rt[N];
inline int id(int x,int y){return y*n+x;}
struct edge{int v,w,next;}e[N<<1],e2[N<<1];
int tot=0,head[N],in[N],fa[N],head2[N],tot2=0;

inline void add1(int u,int v,int w){e[++tot]=edge{v,w,head[u]};head[u]=tot;++in[v];}
inline void add2(int u,int v,int w){e2[++tot2]=edge{v,w,head2[u]};head2[u]=tot2;}
inline void add(int u,int v,int w){add1(v,u,-w);add2(u,v,-w);}

namespace H{
struct node{int ls,rs,p,val;node(){ls=rs=p=val=0;}}tr[20*(N<<1)];
int cnt=0;
int merge(int x,int y)
{
	if(!x||!y)return x^y;
	if(tr[x].val>tr[y].val)swap(x,y);
	int o=++cnt;tr[o]=tr[x];
	tr[o].rs=merge(tr[o].rs,y);
	swap(tr[o].ls,tr[o].rs);return o;
}
inline void insert(int&rt,int p,int val)
{
	int o=++cnt;tr[o].p=p,tr[o].val=val;
	rt=merge(rt,o);
}
}

void dfs(int u)
{
	fe2(i,u){
		int v=e2[i].v,w=e2[i].w;
		if(fa[u]==v)continue;
		int hh=w-d[u]+d[v];
		H::insert(rt[u],v,hh);
	}
	fe(i,u){
		int v=e[i].v;if(fa[v]!=u)continue;
		rt[v]=rt[u];dfs(v);
	}
}

inline void gao()
{static queue<int> q;while(!q.empty())q.pop();
	memset(d,0x3f,(vt+1)<<2);d[vt]=0;
	memset(fa,-1,(vt+1)<<2);
	q.push(vt);
	while(!q.empty()){
		int u=q.front();q.pop();
		fe(i,u){
			int v=e[i].v,w=e[i].w;
			if(d[v]>d[u]+w)d[v]=d[u]+w,fa[v]=u;
			if(!--in[v])q.push(v);
		}
	}
	dfs(vt);
}

int main()
{open("hh");
	n=rd();K=rd();
	vs=0;vt=n*3+1;
	add(vs,id(1,0),0);
	fo(i,1,n){
		add(id(i,2),vt,0);
		int x=rd(),y=rd(),z=rd();
		add(id(i,0),id(i,2),x);
		add(id(i,1),id(i,2),y);
		if(i<n){
			add(id(i,0),id(i+1,0),0);
			add(id(i,1),id(i+1,1),0);
			add(id(i,2),id(i+1,z),0);
		}
	}
	gao();
	if(K==1)return printf("%d\n",-d[vs]),0;--K;
	static priority_queue<pii>q;while(!q.empty())q.pop();
	q.push(pii(-(d[vs]+H::tr[rt[vs]].val),rt[vs]));
	while(K--){
		pii hh=q.top();q.pop();
		if(!K)return printf("%d\n",hh.first),0;
		int v=rt[H::tr[hh.second].p];
		if(v)q.push(pii(hh.first-H::tr[v].val,v));
		int ls=H::tr[hh.second].ls,rs=H::tr[hh.second].rs;
		if(ls)q.push(pii(hh.first+H::tr[hh.second].val-H::tr[ls].val,ls));
		if(rs)q.push(pii(hh.first+H::tr[hh.second].val-H::tr[rs].val,rs));
	}
	return 0;
}
```

原题：hdu5960