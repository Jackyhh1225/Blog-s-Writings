#  [JOISC 2017 Day1 T3 烟花棒](https://www.luogu.org/problemnew/show/AT2535)

## 题意：

​	数轴上有$N$人在放烟花，一开始只有第$K$个人的烟花是点燃的，烟花燃烧的时间为$T$秒，求让所有人的烟花都可以点燃的速度的最小值。（$N\leq1e5,T\leq1e9​$）。

## 题解：

​	好难啊。。。。

​	肯定是二分答案，现在问题转化为能否覆盖整个区间。一个很显然的结论：如果$[i,j]$都可以点燃，则满足$x_j+VT(j-i)\geq x_i-VT(j-i)$。令$a[i]=x_i-2VT*i$，则$a[i]\geq a[j]$。

​	现在要求的就是可不可以从$[k,k]$走到$[1,n]$，贪心即解决。

```c++
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define fo(i,l,r) for(int i=l;i<=r;i++)
#define of(i,l,r) for(int i=l;i>=r;i--)
#define fe(i,u) for(int i=head[u];i;i=e[i].next)
using namespace std;
typedef long long ll;
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
const int N=100010;
int n,K,T,x[N];
ll a[N];

inline bool gao(int V)
{
	fo(i,1,n)a[i]=x[i]-2ll*T*V*i;
	if(a[1]<a[n])return 0;
	int ql=K,qr=K,l,r;
	of(i,K-1,1)if(a[i]>=a[ql])ql=i;
	fo(i,K+1,n)if(a[i]<=a[qr])qr=i;
	l=r=K;
	while(l!=ql||r!=qr){
		bool hh=0;
		int L=l,R=r;
		while(L>ql&&a[L-1]>=a[r])if(a[--L]>=a[l])break;
		if(L<l&&a[L]>=a[l])hh=1,l=L;
		while(R<qr&&a[R+1]<=a[l])if(a[++R]<=a[r])break;
		if(R>r&&a[R]<=a[r])hh=1,r=R;
		if(!hh)return 0;
	}
	l=1;r=n;
	while(l!=ql||r!=qr){
		bool hh=0;
		int L=l,R=r;
		while(L<ql&&a[L+1]>=a[r])if(a[++L]>=a[l])break;
		if(L>l&&a[L]>=a[l])hh=1,l=L;
		while(R>qr&&a[R-1]<=a[l])if(a[--R]<=a[r])break;
		if(R<r&&a[R]<=a[r])hh=1,r=R;
		if(!hh)return 0;
	}
	return 1;
}

int main()
{
	n=rd();K=rd();T=rd();
	fo(i,1,n)x[i]=rd();
	int l=0,r=1000000000,mid,ans=r;
	while(l<=r){
		mid=(l+r)>>1;
		if(gao(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}

```

