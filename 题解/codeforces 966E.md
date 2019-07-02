# codeforces 966E

## 题意：

​	给你一颗树，每个点有一个权值$t_i$，一开始所有点都是黑色，每次操作将一个点反色，问每次操作后有多少个点满足是黑色点并且子树内白色点的个数严格大于$t_i$。($N,M\leq1e5​$）。

## 题解：

​	经典的cf分块，将操作分块建虚树，对每条链暴力维护。时间复杂度$O(N\sqrt N)$。可能还要带上一个sort的$logN​$。

```c++
#include<bits/stdc++.h>
#define fo(i,l,r) for(int i=l;i<=r;i++)
#define of(i,l,r) for(int i=l;i>=r;i--)
#define fe(i,u) for(int i=head[u];i;i=e[i].next)
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
const int N=100010,SZ=321;
struct edge{int v,next;}e[N];
int n,m,B,val[N],fa[N],head[N],fv[N];
int st[N],top=0,dfn[N],tim=0;
vector<int>vec[N],cnt[N];
int p[N],s[N],tag[N],a[N],tt=0,cur[N];
int pos[N],tot=0,ans=0;
bool vis[N];

inline void add(int u,int v){e[v-1]=edge{v,head[u]};head[u]=v-1;}

namespace Rmq{
int bit[N<<1],bin[21];
pii rmq[20][N<<1];
void dfs(int u){dfn[u]=++tim;rmq[0][tim]=pii(dfn[u],u);fe(i,u)dfs(e[i].v),rmq[0][++tim]=pii(dfn[u],u);}
inline void build()
{
	dfs(1);
	fo(i,2,tim)bit[i]=bit[i>>1]+1;
	bin[0]=1;fo(i,1,bit[tim])bin[i]=bin[i-1]<<1;
	fo(i,1,bit[tim])fo(j,1,tim-bin[i]+1)rmq[i][j]=min(rmq[i-1][j],rmq[i-1][j+bin[i-1]]);
}
inline int getlca(int x,int y){x=dfn[x],y=dfn[y];if(x>y)swap(x,y);int k=bit[y-x+1];return min(rmq[k][x],rmq[k][y-bin[k]+1]).second;}
}using Rmq::getlca;

inline void build(int x)
{static int v[N],b[N],tt;tt=0;
	for(int u=x;u!=fv[x];u=fa[u])if(!vis[u])++v[b[++tt]=val[u]];
	if(vis[x])b[++tt]=val[x];
	sort(b+1,b+tt+1);tt=unique(b+1,b+tt+1)-b-1;
	vec[x].resize(tt+1);cnt[x].resize(tt+1);
	vec[x][0]=-1e9;
	fo(i,1,tt){
		vec[x][i]=b[i];cnt[x][i]=v[b[i]];v[b[i]]=0;
		if(b[i]==val[x])cur[x]=i;
		if(vec[x][i]<0)p[x]=i,s[x]+=cnt[x][i];
	}
}

inline void mdy(int x,int d)
{
	tag[x]+=d;ans-=s[x];
	if(vec[x][p[x]]+tag[x]>=0)s[x]-=cnt[x][p[x]--];
	if(p[x]+1<(int)vec[x].size()&&vec[x][p[x]+1]+tag[x]<0)s[x]+=cnt[x][++p[x]];
	ans+=s[x];
}
inline void solve(int x)
{
	vis[x]^=1;
	if(vis[x]){--cnt[x][cur[x]];if(cur[x]<=p[x])--ans,--s[x];}
	else{++cnt[x][cur[x]];if(cur[x]<=p[x])++ans,++s[x];}
	for(int u=x;u;u=fv[u])mdy(u,vis[x]?-1:1);
}
inline void clr(int x)
{
	for(int u=x;u!=fv[x];u=fa[u])val[u]+=tag[x];
	vec[x].clear();cnt[x].clear();s[x]=p[x]=tag[x]=fv[x]=0;
}

inline void gao()
{static int q[N];
	fo(i,1,tt)q[i]=a[i];
	sort(a+1,a+tt+1,[](int a,int b){return dfn[a]<dfn[b];});
	st[top=1]=1;
	fo(i,1,tt){
		int x=a[i],lca=getlca(x,st[top]);
		while(dfn[lca]<dfn[st[top]]){
			if(dfn[lca]>=dfn[st[top-1]]){
				fv[st[top]]=lca,pos[++tot]=st[top--];
				if(lca!=st[top])st[++top]=lca;
				break;
			}
			fv[st[top]]=st[top-1],pos[++tot]=st[top--];
		}
		if(x!=st[top])st[++top]=x;
	}
	while(top)fv[st[top]]=st[top-1],pos[++tot]=st[top--];
	fo(i,1,tot)build(pos[i]);
	fo(i,1,tt)solve(q[i]),printf("%d ",ans);
	fo(i,1,tot)clr(pos[i]),pos[i]=0;
	tt=tot=0;
}

int main()
{open("hh");
	n=rd();m=rd();
	fo(i,2,n)add(fa[i]=rd(),i);Rmq::build();
	fo(i,1,n)val[i]=rd();
	B=sqrt(m)+1;
	while(m--){
		int x=rd();if(x<0)x=-x;
		a[++tt]=x;
		if(tt==B||!m)gao();
	}
	return 0;
}
```

