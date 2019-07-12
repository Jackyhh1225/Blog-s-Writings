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
const int N=1000010;
int n,m,Q,id[510][510][4];
int val[N],nxt[N];
int tot=0,bel[N];

struct data{
map<int,int>mp1,mp2;
inline void clr(){mp1.clear();mp2.clear();}
inline void ins(int x)
{
	if(mp1.count(x))if(!--mp2[mp1[x]])mp2.erase(mp1[x]);
	++mp2[++mp1[x]];
}
inline void del(int x)
{
	if(!--mp2[mp1[x]])mp2.erase(mp1[x]);
	if(!--mp1[x])mp1.erase(x);
	if(mp1.count(x))++mp2[mp1[x]];
}
inline int qry(){return mp2.rbegin()->first;}
}s[N];

inline void pre()
{
	int tt=0;
	fo(i,1,n)fo(j,1,m)fo(k,0,3)id[i][j][k]=++tt;
	fo(i,1,m){
		nxt[id[1][i][0]]=id[1][i][1];
		if(i<m)nxt[id[1][i][1]]=id[1][i+1][0];
		nxt[id[n][i][2]]=id[n][i][3];
		if(i>1)nxt[id[n][i][3]]=id[n][i-1][2];
	}
	fo(i,1,n){
		nxt[id[i][m][1]]=id[i][m][2];
		if(i<n)nxt[id[i][m][2]]=id[i+1][m][1];
		nxt[id[i][1][3]]=id[i][1][0];
		if(i>1)nxt[id[i][1][0]]=id[i-1][1][3];
	}
	fo(i,1,n-1)fo(j,1,m-1){
		nxt[id[i+1][j+1][0]]=id[i][j+1][3];
		nxt[id[i+1][j][1]]=id[i+1][j+1][0];
		nxt[id[i][j][2]]=id[i+1][j][1];
		nxt[id[i][j+1][3]]=id[i][j][2];
	}
	fo(i,1,n)fo(j,0,m){
		int x=rd();
		if(j==0)val[id[i][1][3]]=x;
		else if(j==m)val[id[i][j][1]]=x;
		else if(x){
			val[id[i][j+1][3]]=val[id[i][j][1]]=x;
			nxt[id[i][j+1][3]]=id[i][j+1][0];
			nxt[id[i][j][1]]=id[i][j][2];
		}
	}
	fo(i,0,n)fo(j,1,m){
		int x=rd();
		if(i==0)val[id[1][j][0]]=x;
		else if(i==m)val[id[i][j][2]]=x;
		else if(x){
			val[id[i+1][j][0]]=val[id[i][j][2]]=x;
			nxt[id[i+1][j][0]]=id[i+1][j][1];
			nxt[id[i][j][2]]=id[i][j][3];
		}
	}
	static bool vis[N];
	static vector<int>vec;vec.clear();
	fo(i,1,tt)if(!vis[i]){
		if(!vis[i]){
			int x=i;
			vec.clear();++tot;
			for(;!vis[x];x=nxt[x]){
				vis[x]=1,vec.push_back(x);
				printf("%d ",x);
			}el;
			for(int x:vec){
				bel[x]=tot;
				if(val[x])s[tot].ins(val[x]);
			}
		}
	}
}

inline void mdy(int x0,int y0,int x1,int y1)
{
	int a,b,c,d;
	if(x0==x1){
		if(y0<y1)swap(y0,y1);
		a=id[x0+1][y0][0];
		b=id[x0][y0][3];
		c=id[x0][y0][2];
		d=id[x0+1][y0][1];
	}
	else{
		if(x0<x1)swap(x0,x1);
		a=id[x0][y0+1][3];
		b=id[x0][y0][2];
        c=id[x0][y0][1];
        d=id[x0][y0+1][0];
	}
	s[bel[a]].del(val[a]);
	s[bel[a]].del(val[a]);
	if(bel[a]==bel[c]){
		int x=b,y=d;++tot;
		for(;x!=a&&y!=c;x=nxt[x],y=nxt[y]);
		if(x==a){
			for(x=b;;x=nxt[x]){
				bel[x]=tot;
				if(val[x])s[tot].ins(val[x]),s[bel[c]].del(val[x]);
				if(x==a)break;
			}
		}
		else{
			for(x=d;;x=nxt[x]){
				bel[x]=tot;
				if(val[x])s[tot].ins(val[x]),s[bel[a]].del(val[x]);
				if(x==c)break;
			}
		}
	}
	else{
		int x=d,y=b;
		for(;x!=a&&y!=c;x=nxt[x],y=nxt[y]);
		if(x==a){
			for(x=d;;x=nxt[x]){
				bel[x]=bel[c];
				if(val[x])s[bel[c]].ins(val[x]);
				if(x==a)break;
			}
			s[bel[a]].clr();
		}
		else{
			for(x=b;;x=nxt[x]){
				bel[x]=bel[a];
				if(val[x])s[bel[a]].ins(val[x]);
				if(x==c)break;
			}
			s[bel[c]].clr();
		}
	}
	nxt[a]=b;
	nxt[c]=d;
	val[a]=val[c]=0;
}

inline int qry(int x0,int y0,int x1,int y1,int f)
{
	int hh;
	if(y0==y1){
		if(x0<x1)swap(x0,x1);
		hh=f?id[x0][y0+1][3]:id[x0][y0][1];
	}
	else{
		if(y0<y1)swap(y0,y1);
		hh=f?id[x0+1][y0][0]:id[x0][y0][2];
	}
	return s[bel[hh]].qry();
}

int main()
{
	open("hh");
	n=rd();m=rd();Q=rd();
	pre();
	while(Q--){
		int ty=rd(),x0=rd(),y0=rd(),x1=rd(),y1=rd();
		if(ty==1)mdy(x0,y0,x1,y1);
		else{
			int f=rd();
			printf("%d\n",qry(x0,y0,x1,y1,f));
		}
	}
	return 0;
}
