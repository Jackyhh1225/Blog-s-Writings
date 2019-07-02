# [JOISC 2018 Day 2 最差记者3](https://loj.ac/problem/2836)

## 题意：

​	数轴上有$N$个选手和一个旗手，旗手在位置$0$<第$i$人的位置为$-i$，每个选手有一个参数$D_i$。旗手每单位时间向右走$1$单位，选手根据以下规则向右走：

- 若与前一个人距离$\le D_i$，$i​$号选手不移动；
- 若与前一个人距离$> D_i$，则$i$号选手会立即向前走，走到距前者的后方$1$单位距离的位置。

​        $Q$组询问，每组询问给你$T,l,i$，问在$T$时刻，数轴上$l-r$有多少人？（$N,Q\leq1e5,D_i\leq1e9$）

## 题解：

​	提高组题，每个人走的周期都是可以算的，如果这个人的周期少于上个人的周期，显然他的周期就和上个人的一样，否则他的周期$f_i=\lceil \frac{f_{i-1}}{D_i} \rceil$。然后这个函数的增长至少是两倍，直接存就好了。复杂度$O(QlogD)$。

```c++
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
#define fo(i,l,r) for(int i=l;i<=r;i++)
#define of(i,l,r) for(int i=l;i>=r;i--)
#define fe(i,u) for(int i=head[u];i;i=e[i].next)
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
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
int n,m;
vector<piii>v;

int main()
{
	n=rd();m=rd();
	ll d=1;int st=0;
	fo(i,1,n){
		int x=rd();
		if(x>d){
			v.push_back(piii(d,pii(st,i-1)));
			d=(ll)((x-1)/d+1)*d;st=i;
		}
	}
	v.push_back(piii(d,pii(st,n)));
	while(m--){
		ll T=rd(),l=rd(),r=rd(),ans=0;
		for(int i=0;i<(int)v.size();++i){
			ll ql=T/v[i].first*v[i].first-v[i].second.first;
			ll qr=ql-v[i].second.second+v[i].second.first;
			ans+=max(0ll,min(ql,r)-max(qr,l)+1ll);
		}
		printf("%lld\n",ans);
	}
	return 0;
}

```

