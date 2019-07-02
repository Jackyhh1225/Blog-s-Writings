# codeforces1063 F

## 题意： 

​	不想翻译。

## 题解：

​	发现如果一个字符串有长度为$K$的Journey，那么一定存在一个Journey，里面的每个字符串长度为$1-k$。设$f_i$表示以$i$开头的最长Journey的长度，有：$f_i\leq f_{i+1}+1$。

​	因为$f_i\leq f_{i+1}+1$，所以可以暴力枚举$f_i$的取值。一个$f_i$可行，当且仅当$\exists j\geq i+f_i, lcp(Suf_j,Suf_i)\geq f_i-1,f_j\geq f_i-1$。可以用后缀树加线段树解决。

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
#ifndef ONLINE_JUDGE
const int N=50010;
#endif
#ifdef ONLINE_JUDGE
const int N=500010;
#endif
int n,len[N<<1],pos[N],rt,f[N],ans;
bool vis[N];
char s[N];

namespace Seg{
#define lson tr[o].ls,l,mid
#define rson tr[o].rs,mid+1,r
#define qlson lson,L,min(mid,R)
#define qrson rson,max(mid+1,L),R
struct tree{
	int ls,rs,mx;
	tree(){ls=rs=mx=0;}
}tr[N<<2];int cnt=0;
void bld(int&o,int l,int r){o=++cnt;if(l==r)return;int mid=(l+r)>>1;bld(lson);bld(rson);}
void ins(int o,int l,int r,int x,int d)
{
	tr[o].mx=max(tr[o].mx,d);if(l==r)return;
	int mid=(l+r)>>1;x<=mid?ins(lson,x,d):ins(rson,x,d);
}
int qry(int o,int l,int r,int L,int R)
{
	if(l==L&&r==R)return tr[o].mx;int mid=(l+r)>>1,res=0;
	if(L<=mid)res=max(res,qry(qlson));
	if(R>mid)res=max(res,qry(qrson));
	return res;
}
}

namespace T{
struct edge{int v,next;}e[N<<1];
int dfn[N<<1],ed[N<<1],tim=0,fa[21][N<<1];
int tot=0,head[N<<1];
inline void add(int u,int v){e[++tot]=edge{v,head[u]};head[u]=tot;}
void dfs(int u)
{
	dfn[u]=++tim;
	fo(i,1,20)fa[i][u]=fa[i-1][fa[i-1][u]];
	fe(i,u)fa[0][e[i].v]=u,dfs(e[i].v);
	ed[u]=tim;
}
inline void ins(int x,int d){Seg::ins(rt,1,tim,dfn[x],d);}
inline int jump(int x,int L){
	of(i,20,0)
		if(len[fa[i][x]]>=L)x=fa[i][x];
	return x;
}
inline bool qry(int x,int preans)
{if(!x)return 0;
	x=jump(x,preans);
	int hh=Seg::qry(rt,1,tim,dfn[x],ed[x]);
	return hh>=preans;
}
}

namespace SAM{
int las=1,cnt=1,ch[N<<1][26],fa[N<<1];
inline void ins(int x,int&pos)
{
	int p=las,np=las=pos=++cnt;len[np]=len[p]+1;
	for(;p&&!ch[p][x];p=fa[p])ch[p][x]=np;
	if(!p)return fa[np]=1,void();
	int q=ch[p][x];if(len[q]==len[p]+1)return fa[np]=q,void();
	int nq=++cnt;len[nq]=len[p]+1;fa[nq]=fa[q];fa[q]=fa[np]=nq;
	memcpy(ch[nq],ch[q],104);for(;p&&ch[p][x]==q;p=fa[p])ch[p][x]=nq;
}
inline void bld(){fo(i,2,cnt)T::add(fa[i],i);T::dfs(1);Seg::bld(rt,1,cnt);}
}

int main()
{open("hh");
	n=rd();scanf("%s",s+1);
	of(i,n,1)SAM::ins(s[i]-'a',pos[i]);
	len[0]=-1;SAM::bld();
	of(i,n,1){
		f[i]=f[i+1]+1;
		while(!T::qry(pos[i],f[i]-1)&&!T::qry(pos[i+1],f[i]-1)){
			--f[i];
			if(!vis[i+f[i]])vis[i+f[i]]=1,T::ins(pos[i+f[i]],f[i+f[i]]);
		}ans=max(ans,f[i]);
	}
	printf("%d\n",ans);
	#ifndef ONLINE_JUDGE
	fo(i,1,n)cout<<f[i]<<' ';cout<<endl;
	#endif
	return 0;
}

```

