# [xsy3320 string](http://192.168.102.138/JudgeOnline/problem.php?id=3320)

## 题意：

​	给一颗树，每条边上有一个字符，求有多少条路径是回文的。（$N\leq50000$,$c\in\{1,2\}$）

------



## 题解：

​	前置芝士：回文前缀&&border

​	先点分治，问题变成求经过分治中心的回文路径个数。

​	观察这样的路径长啥样：u - S -> rt <- T - k <- S -v。

​	其中$(u,v)$是一条回文路径，T是回文串，$v$到$k$的串与$u$到$rt$的串相同。

​	判断一个从根到某个点的路径是不是回文路径可以用哈希解决。建出ac自动机，在fail树上找出每一个串的回文前缀。根据border理论，一个回文串的回文前缀可以被划分成$O(\log n)​$个不同的等差数列。每次在fail树上枚举$v​$，在暴力找它所有回文前缀，找S的个数，问题变成了给你一段区间，问里面$ len \% d​$为某个值的所有串的个数。考虑怎么处理这样的询问。发现可以差分区间，然后对每种公差，存所有余数的答案。但是这样的空间复杂度是$O(n^2)​$的。所以分块处理，对于公差大于$\sqrt {siz}​$的，暴力往上跳统计答案。

​	可以发现最差情况下ac自动机和原树同构，分块数组是$O(\sqrt n^2=n)$的，所以空间复杂度$O(n)$。

​	对于每一个点，跳回文前缀是$O(\log n)$的，对于公差大于$\sqrt n$的，暴力跳是$\sqrt  n$的，小于的要在链上二分，所以这一部分的时间复杂度是$O(n\sqrt n+n\log^2 n)$。处理询问时要$O(\sqrt n)$保存答案时间,所以这里复杂度是$O(n\sqrt n)$。加上每次分治的复杂度，总复杂度：
$$
T(n)=2T(\frac n2)+O(n\sqrt n)=O(n\sqrt n)
$$
​	可以通过此题。

## 代码：

```c++
#include<bits/stdc++.h>
#define fo(i,l,r) for(int i=l;i<=r;i++)
#define of(i,l,r) for(int i=l;i>=r;i--)
#define fe(i,u) for(int i=head[u];i;i=e[i].next)
#define el putchar('\n')
#define ta putchar('	')
using namespace std;
typedef long long ll;
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
const int NS=(1<<21)+5;
char buf[NS],*H,*T;
inline char Get()
{
	if(H==T)T=(H=buf)+fread(buf,1,NS,stdin);
	if(H==T)return -1;return *H++;
}
inline int rd()
{
	static int x,f;
	x=0;f=1;
	char ch=Get();
	for(;ch<'0'||ch>'9';ch=Get())if(ch=='-')f=-1;
	for(;ch>='0'&&ch<='9';ch=Get())x=x*10+ch-'0';
	return f>0?x:-x;
}
const int N=50010;
const int mod1=1000000007;
const int mod2=998244353;
struct edge{
	int v,w,next;
	edge(int v=0,int w=0,int next=0):v(v),w(w),next(next){}
}e[N<<1];
int n,bin1[N],bin2[N];
int tot=0,head[N];
int siz[N],s,root;
ll ans=0,res;
bool vis[N];
int B;

struct node{int d,m,siz,ty;};
vector<node>ask[N];
vector<int>g[N];

inline void add(int u,int v,int w){e[++tot]=edge(v,w,head[u]);head[u]=tot;}
inline void pre(int n){bin1[0]=bin2[0]=1;fo(i,1,n)bin1[i]=3ll*bin1[i-1]%mod1,bin2[i]=3ll*bin2[i-1]%mod2;}

namespace AC{
struct tree{
	int ch[2],siz,fail,revfa,len,anc;bool rev;
	tree(){ch[0]=ch[1]=siz=fail=revfa=len=anc=rev=0;}
}tr[N];int rt,cnt=0;
queue<int>q;

void buildfail()
{
	while(!q.empty())q.pop();
	q.push(rt);tr[rt].fail=rt;
	while(!q.empty()){
		int u=q.front();q.pop();
		fo(i,0,1){
			int v=tr[u].ch[i];
			if(!v){tr[u].ch[i]=u==rt?u:tr[tr[u].fail].ch[i];continue;}
			if(tr[u].rev)tr[v].revfa=u;else tr[v].revfa=tr[u].revfa;
			tr[v].fail=u==rt?u:tr[tr[u].fail].ch[i];q.push(v);
		}
	}
	fo(i,2,cnt)
		if(tr[i].len-tr[tr[i].revfa].len==tr[tr[i].revfa].len-tr[tr[tr[i].revfa].revfa].len)
			tr[i].anc=tr[tr[i].revfa].anc;
			else tr[i].anc=tr[i].revfa;
	fo(i,2,cnt)g[tr[i].fail].push_back(i);
}

}

void getsiz(int u,int fat){siz[u]=1;fe(i,u){int v=e[i].v;if(v==fat||vis[v])continue;getsiz(v,u);siz[u]+=siz[v];}}
void getrt(int u,int fat){int mx=siz[0]-siz[u];fe(i,u){int v=e[i].v;if(v==fat||vis[v])continue;mx=max(mx,siz[v]);getrt(v,u);}if(mx<s)s=mx,root=u;}
void dfs1(int u,int fat,int &o,int h1,int rh1,int h2,int rh2,int dep)
{using namespace AC;
	if(!o){tr[o=++cnt]=tree();tr[o].len=dep;tr[o].rev=h1==rh1&&h2==rh2;}
	++B;++tr[o].siz;
	fe(i,u){
		int v=e[i].v,w=e[i].w;if(v==fat||vis[v])continue;
		int nh1=(3ll*h1%mod1+w)%mod1;
		int nrh1=((ll)bin1[dep]*w+rh1)%mod1;
		int nh2=(3ll*h2%mod2+w)%mod2;
		int nrh2=((ll)bin2[dep]*w+rh2)%mod2;
		dfs1(v,u,tr[o].ch[w&1],nh1,nrh1,nh2,nrh2,dep+1);
	}
}

int sum[N],st[N],top=0,lst[N];
int f[350][350];
bool hhhhh=1;
void getq(int u)
{using namespace AC;
	st[++top]=tr[u].len;lst[top]=u;
	res+=(ll)tr[u].siz*(tr[u].siz-1)>>1;
	int x=tr[u].revfa;if(tr[u].rev)x=u;
	sum[tr[u].len]+=tr[u].siz;
	while(tr[x].len){
		int d=tr[x].len-tr[tr[x].revfa].len;
		int L=tr[x].len-tr[tr[x].anc].len;
		if(d<=B){
			int l=tr[u].len-tr[x].len,r=tr[u].len-tr[x].len+L-d;
			l=lower_bound(st+1,st+top+1,l)-st;r=upper_bound(st+1,st+top+1,r)-st-1;
			if(l-1)ask[lst[l-1]].push_back(node{d,(tr[u].len-tr[x].len)%d,tr[u].siz,-1});
			if(r)ask[lst[r]].push_back(node{d,(tr[u].len-tr[x].len)%d,tr[u].siz,1});
		}else for(int t=x;t!=tr[x].anc;t=tr[t].revfa)res+=(ll)tr[u].siz*sum[tr[u].len-tr[t].len];
		x=tr[x].anc;
	}
	fo(i,0,(int)g[u].size()-1)getq(g[u][i]);
	--top;sum[tr[u].len]-=tr[u].siz;
}
void getans(int u)
{using namespace AC;
	fo(i,1,B)f[i][tr[u].len%i]+=tr[u].siz;
	fo(i,0,(int)ask[u].size()-1)res+=f[ask[u][i].d][ask[u][i].m]*ask[u][i].siz*ask[u][i].ty;
	fo(i,0,(int)g[u].size()-1)getans(g[u][i]);
	fo(i,1,B)f[i][tr[u].len%i]-=tr[u].siz;
}

inline ll calc(int u,int w)
{
	using namespace AC;
	res=0;
	B=0;
	if(w){
		rt=cnt=1;tr[rt]=tree();tr[rt].rev=1;
		dfs1(u,0,tr[rt].ch[w&1],w,w,w,w,1);
	}
	else rt=cnt=0,dfs1(u,0,rt,0,0,0,0,0);
	B=floor(sqrt(B));
	AC::buildfail();
	getq(rt);getans(rt);
	fo(i,1,cnt)g[i].clear(),ask[i].clear();
	return res;
}

void gao(int u)
{
	getsiz(u,0);siz[0]=s=siz[u];root=0;getrt(u,0);vis[u=root]=1;ans+=calc(u,0);
	fe(i,u){
		int v=e[i].v,w=e[i].w;if(vis[v])continue;
		ans-=calc(v,w);gao(v);
	}
}

int main()
{
	open("c");
	n=rd();
	fo(i,2,n){
		int x=rd(),y=rd(),z=2-rd();
		add(x,y,z);add(y,x,z);
	}
	pre(n);gao(1);
	printf("%lld\n",ans);
	return 0;
}
```

 ~~好写好调，没细节。~~