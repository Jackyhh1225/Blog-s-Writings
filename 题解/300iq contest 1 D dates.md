# 300iq contest 1 D dates

## 题意：

​	咕咕咕

## 题解：

​	相当于做一个二分图最大匹配，那就按权值从大到小看能不能插入，能就插入，不能就略过。

​	一个人能被插入的充分必要条件是$\forall L,R\ \Sigma_{i=L}^R a_i\geq \Sigma_{i\in S}\left [[l_i,r_i]\subseteq [L,R]\right]$。

​	$\Leftrightarrow\forall L,R\ \Sigma_{i=L}^R[i\in S] \leq \Sigma_{i=l_L}^{r_R}a_i$。

​	转成前缀和模式，可以用线段树维护。

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
const int N=300010;
int n,m,val[N],id[N];
ll sa[N],c[N],d[N];

namespace Seg{
#define lson tr[o].ls,l,mid
#define rson tr[o].rs,mid+1,r
#define qlson lson,L,min(mid,R)
#define qrson rson,max(mid+1,L),R
struct tree{
	int ls,rs;ll mx,mn,tag;
}tr[N<<2];int cnt=0;

inline void pushup(int o)
{
	tr[o].mx=max(tr[tr[o].rs].mx,tr[tr[o].ls].mx);
	tr[o].mn=min(tr[tr[o].rs].mn,tr[tr[o].ls].mn);
}
void build(int&o,int l,int r,ll*a)
{o=++cnt;
	if(l==r)return tr[o].mx=tr[o].mn=a[l],void();
	int mid=(l+r)>>1;build(lson,a);build(rson,a);
	pushup(o);
}
inline void pushdown(int o)
{
	if(!tr[o].tag)return;
	int x=tr[o].ls;
	tr[x].mn+=tr[o].tag;tr[x].mx+=tr[o].tag;tr[x].tag+=tr[o].tag;
	x=tr[o].rs;
	tr[x].mn+=tr[o].tag;tr[x].mx+=tr[o].tag;tr[x].tag+=tr[o].tag;
	tr[o].tag=0;
}
void mdy(int o,int l,int r,int L,int R,int d)
{
	if(l==L&&r==R)return tr[o].mn+=d,tr[o].mx+=d,tr[o].tag+=d,void();
	int mid=(l+r)>>1;pushdown(o);if(L<=mid)mdy(qlson,d);if(R>mid)mdy(qrson,d);
	pushup(o);
}
ll qmx(int o,int l,int r,int L,int R)
{
	if(l==L&&r==R)return tr[o].mx;
	pushdown(o);int mid=(l+r)>>1;ll res=-1e16;
	if(L<=mid)res=max(res,qmx(qlson));
	if(R>mid)res=max(res,qmx(qrson));
	return res;
}
ll qmn(int o,int l,int r,int L,int R)
{
	if(l==L&&r==R)return tr[o].mn;
	pushdown(o);int mid=(l+r)>>1;ll res=1e16;
	if(L<=mid)res=min(res,qmn(qlson));
	if(R>mid)res=min(res,qmn(qrson));
	return res;
}
}

int main()
{
	n=rd();m=rd();
	fo(i,1,m)sa[i]=sa[i-1]+rd();
	fo(i,1,n){
		int x=rd(),y=rd(),w=rd();
		c[i]=-sa[y];
		d[i]=-sa[x-1];
		val[i]=w;
		id[i]=i;
	}
	int rt1,rt2;
	Seg::build(rt1,1,n,c);
	Seg::build(rt2,1,n,d);
	sort(id+1,id+n+1,[](int a,int b){return val[a]>val[b];});
	ll ans=0;
	fo(i,1,n){
		int x=id[i];
		if(Seg::qmx(rt1,1,n,x,n)<Seg::qmn(rt2,1,n,1,x)){
			ans+=val[x];
			Seg::mdy(rt1,1,n,x,n,1);
			if(x<n)Seg::mdy(rt2,1,n,x+1,n,1);
		}
	}
	cout<<ans;
	return 0;
}

```

