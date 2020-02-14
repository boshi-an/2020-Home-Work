//by yjz
#include<bits/stdc++.h>
using namespace std;
#define FF first
#define SS second
#define PB push_back
#define MP make_pair
#define foreach(it,s) for(__typeof((s).begin()) it=(s).begin();it!=(s).end();it++)
#ifndef LOCAL
#define cerr if(0)cout
#endif
typedef long long ll;
const int mod = 1e9+7;
//My i/o stream
struct fastio
{
	char s[100000];
	int it, len;
	fastio() {it=len=0;}
	inline char get()
	{
		if (it<len) return s[it++]; it=0;
		len=fread(s, 1, 100000, stdin);
		if (len==0) return EOF; else return s[it++];
	}
	bool notend()
	{
		char c=get();
		while (c==' '||c=='\n') c=get();
		if (it>0) it--;
		return c!=EOF;
	}
}_buff;
#define geti(x) x=getnum()
#define getii(x,y) geti(x),geti(y)
#define getiii(x,y,z) getii(x,y),geti(z)
#define puti(x) putnum(x),putchar(' ')
#define putii(x,y) puti(x),puti(y)
#define putiii(x,y,z) putii(x,y),puti(z)
#define putsi(x) putnum(x),putchar('\n')
#define putsii(x,y) puti(x),putsi(y)
#define putsiii(x,y,z) putii(x,y),putsi(z)
inline ll getnum()
{
	ll r=0; bool ng=0; char c; c=_buff.get();
	while (c!='-'&&(c<'0'||c>'9')) c=_buff.get();
	if (c=='-') ng=1, c=_buff.get();
	while (c>='0'&&c<='9') r=r*10+c-'0', c=_buff.get();
	return ng?-r:r;
}
template <class T> inline void putnum(T x)
{
	if (x<0) putchar('-'), x=-x;
	register short a[20]={}, sz=0;
	while (x) a[sz++]=x%10, x/=10;
	if(sz==0) putchar('0');
	for (int i=sz-1; i>=0; i--) putchar('0'+a[i]);
}
inline char getreal() {char c=_buff.get(); while (c<=32) c=_buff.get(); return c;}
ll qpow(ll x, ll k) {return k==0? 1: 1ll*qpow(1ll*x*x%mod,k>>1)*(k&1?x:1)%mod;}
const ll inf = 4e18;
namespace F
{
	const int maxn=2011,maxm=200011*2;
	int head[maxn],nxt[maxm],cap[maxm],to[maxm],tot;
	ll cost[maxm];
	ll ftot=0;
	ll base_ans;
	void init()
	{
		memset(head,0,sizeof(head));
		tot=1;ftot=0;
		base_ans=0;
	}
	void add_edge(int x,int y,int c,ll w)
	{
//		cerr<<"adde:"<<x<<","<<y<<" "<<c<<" "<<w<<endl;
		nxt[++tot]=head[x];
		head[x]=tot;
		to[tot]=y;
		cap[tot]=c;
		cost[tot]=w;
		nxt[++tot]=head[y];
		head[y]=tot;
		to[tot]=x;
		cap[tot]=0;
		cost[tot]=-w;
	}
	ll dis[maxn];
	bool inq[maxn];
	int q[maxn],qb,qe;
	bool vis[maxn];
	void spfa(int S,int T,int N)
	{
		for(int i=0;i<=N;i++)dis[i]=4e18;
		qb=qe=0;
		q[qe++]=S;dis[S]=0;inq[S]=1;
		while(qb!=qe)
		{
			int x=q[qb++];inq[x]=0;
			if(qb==maxn)qb=0;
			for(int i=head[x];i;i=nxt[i])
			{
				int u=to[i];
				if(cap[i]&&dis[u]>dis[x]+cost[i])
				{
					dis[u]=dis[x]+cost[i];
					if(!inq[u])
					{
						inq[u]=1;
						if(qb==qe||dis[u]>dis[q[qb]])
						{
							q[qe++]=u;
							if(qe==maxn)qe=0;
						}
						else
						{
							qb--;
							if(qb<0)qb=maxn-1;
							q[qb]=u;
						}
					}
				}
			}
		}
	}
	int dfs(int x,int T,int f)
	{
		if(x==T)return f;
		int of=f;
		vis[x]=1;
		for(int i=head[x];i;i=nxt[i])
		{
			int u=to[i];
			if(dis[x]+cost[i]==dis[u]&&cap[i]>0&&!vis[u])
			{
				int d=dfs(u,T,min(f,cap[i]));
				if(d>0)
				{
					f-=d;
					cap[i]-=d;
					cap[i^1]+=d;
					if(f==0)return of;
				}
			}
		}
		return of-f;
	}
	ll MinCostFlow(int S,int T,int K,bool mini,int N=-1)
	{
		if(N==-1)N=maxn-1;
		ll ans=0;
		while(K>0)
		{
			spfa(S,T,N);
			if(dis[T]>3e18)break;
			if(dis[T]>0&&mini)break;
			int flow=0;
			do
			{
				for(int i=0;i<=N;i++)vis[i]=0;
				K-=flow;
				ftot+=flow;
				ans+=flow*dis[T];
			}while(flow=dfs(S,T,K));
		}
		return ans;
	}
	bool modlabel(int N)
	{
		ll mn=5e18;
		for(int i=0;i<=N;i++)if(vis[i])
			for(int j=head[i];j;j=nxt[j])if(!vis[to[j]]&&cap[j])
				mn=min(mn,cost[j]-(dis[to[j]]-dis[i]));
		for(int i=0;i<=N;i++)if(!vis[i])dis[i]+=mn;
		return mn<4e18;
	}
	ll MinCostFlow_zkw(int S,int T,int K,bool mini,int N=-1)
	{
		if(N==-1)N=maxn-1;
		spfa(S,T,N);
		ll ans=0;
		do
		{
			if(dis[T]>0&&mini)break;
			int f=0;
			do
			{
				ans+=dis[T]*f;
				K-=f;ftot+=f;
				if(K==0)break;
				for(int i=0;i<=N;i++)vis[i]=0;
			}while(f=dfs(S,T,K));
		}while(K>0&&modlabel(N));
		return ans;
	}
};
int n;
int tid[256];
pair<int,int> a[88];
ll w[88];
vector<pair<int,int> > M[4];
pair<int,int> segx[88], segy[88];
ll solve(int K)
{
//	cerr<<"solve: "<<K<<endl;
	for (int i=1; i<=K; i++) segx[i] = segy[i] = MP(0, 100);
	for (auto x : M[0])
	{
		for (int i=x.SS+1; i<=K; i++)
		{
			segx[i].FF = max(segx[i].FF, x.FF+1);
		}
	}
	for (auto x : M[1])
	{
		for (int i=K-x.SS; i>=1; i--)
		{
			segx[i].SS = min(segx[i].SS, x.FF-1);
		}
	}
	for (auto x : M[2])
	{
		for (int i=x.SS+1; i<=K; i++)
		{
			segy[i].FF = max(segy[i].FF, x.FF+1);
		}
	}
	for (auto x : M[3])
	{
		for (int i=K-x.SS; i>=1; i--)
		{
			segy[i].SS = min(segy[i].SS, x.FF-1);
		}
	}
	int S = 2*K+2*n+1, T = S+1;
	F::init();
	for (int i=1; i<=K; i++)
	{
		F::add_edge(S, i, 1, 0);
		F::add_edge(i+K, T, 1, 0);
		for (int j=1; j<=n; j++)
		{
			if (segx[i].FF<=a[j].FF&&a[j].FF<=segx[i].SS)
			{
				F::add_edge(i, j+2*K, 1, 0);
			}
			if (segy[i].FF<=a[j].SS&&a[j].SS<=segy[i].SS)
			{
				F::add_edge(j+2*K+n, i+K, 1, 0);
			}
		}
	}
	for (int i=1; i<=n; i++) F::add_edge(i+2*K, i+2*K+n, 1, -w[i]);
	ll ans = F::MinCostFlow(S, T, K, 0, T);
//	cerr<<"F::ftot="<<F::ftot<<endl;
	if (F::ftot<K) return 0;
//	cerr<<"ans="<<ans<<endl;
	return -ans;
}
int main()
{
	tid['L'] = 0;
	tid['R'] = 1;
	tid['D'] = 2;
	tid['U'] = 3;
	geti(n);
	for (int i=1; i<=n; i++)
	{
		ll x, y, v;
		getiii(x, y, v);
		a[i] = MP(x, y);
		w[i] = v;
	}
	int m;
	geti(m);
	for (int i=1; i<=m; i++)
	{
		char t;
		int a, b;
		t = getreal();
		getii(a, b);
		M[tid[t]].PB(MP(a, b));
	}
	ll ans = 0;
	for (int K=1; K<=n; K++)
	{
		ans = max(ans, solve(K));
	}
	cout<<ans<<endl;
	return 0;
}