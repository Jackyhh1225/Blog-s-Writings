# CERC 2014 Parades

我是看claris题解学会的

## 题解：

	猜复杂度：$O(nd2^d)$。

	发现一个性质，当一条从子树u内到子树u外的路径如果不能和子树u的最优策略共存，那么这条路径没有意义，因为这不会使答案更优。

	那就记$f_u$表示u子树内的值，在记录在可以和子树u的最优决策共存的点。

	dp就是，$f_u=\Sigma_v fv+最大匹配值$，最大匹配值有两种情况，如果能和u点直接匹配的，显然是最优的，剩下的再状压dp。

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
namespace IO{
const int S=(1<<20)+10;
char buf[S],*H,*T;
inline char Get()
{
	if(H==T)T=(H=buf)+fread(buf,1,S,stdin);
	if(H==T)return -1;return *H++;
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
}using IO::rd;
const int N=1010;
int n,m,bit[1024];
int tot,head[N];
struct edge{int v,next;}e[N<<1];
int f[N],a[N][N],tim=0,dp[1024];
bool can[20][20];
vector<int>g[N];

inline void add(int u,int v){e[++tot]=edge{v,head[u]};head[u]=tot;}
inline bool check(int u,int v)
{
	for(auto x:g[u])for(auto y:g[v])if(a[x][y]==tim)return 1;
	return 0;
}
inline void merge(int u,int v)
{
	if(g[u].size()<g[v].size())g[u].swap(g[v]);
	for(auto x:g[v])g[u].push_back(x);
	g[v].clear();
}

void dfs(int u,int fat)
{
	f[u]=0;g[u].clear();
	fe(i,u){
		int v=e[i].v;if(v==fat)continue;
		dfs(v,u);f[u]+=f[v];
	}
	g[u].push_back(u);
	static vector<int>son;son.clear();
	fe(i,u){
		int v=e[i].v;if(v==fat)continue;
		bool hh=0;
		if(!g[v].size())continue;
		for(auto x:g[v])if(a[x][u]==tim){hh=1;++f[u];break;}
		if(hh)continue;
		son.push_back(v);
	}
	if(!son.size())return;
	int siz=son.size(),L=(1<<siz)-1;
	fo(i,0,siz-1)fo(j,0,siz-1)if(i^j)can[i][j]=check(son[i],son[j]);
	fo(s,1,L){
		int t=s&-s,i=bit[t];
		dp[s]=dp[s^t];
		fo(j,i+1,siz-1)if((s>>j&1)&&can[i][j])dp[s]=max(dp[s],dp[s^t^(1<<j)]+1);
	}
	f[u]+=dp[L];
	fo(i,0,siz-1)if(dp[L]==dp[L^(1<<i)])merge(u,son[i]);
}

inline void gao()
{
	++tim;tot=0;
	memset(head+1,0,n<<2);
	n=rd();
	fo(i,2,n){
		int x=rd(),y=rd();
		add(x,y);add(y,x);
	}
	m=rd();fo(i,1,m){int x=rd(),y=rd();a[x][y]=a[y][x]=tim;}
	dfs(1,0);
	printf("%d\n",f[1]);
}

int main()
{open("hh");
	int x=1;
	fo(i,0,9)bit[x]=i,x<<=1;
	for(int T=rd();T--;gao());
	return 0;
}

```

