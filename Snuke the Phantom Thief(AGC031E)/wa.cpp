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
	const int maxn = 1011, maxe = 100011;
	int head[maxn], nxt[maxe], to[maxe], cap[maxe];
	ll cost[maxe], tot;
	ll ftot;
	void init()
	{
		ftot = 0;
		tot = 1;
		memset(head, 0, sizeof(head));
	}
	void add_edge(int x, int y, int c, ll w)
	{
//		cerr<<"add_edge:"<<x<<","<<y<<" "<<c<<" "<<w<<endl;
		nxt[++tot] = head[x];
		head[x] = tot;
		to[tot] = y;
		cap[tot] = c;
		cost[tot] = w;
		swap(x, y);
		nxt[++tot] = head[x];
		head[x] = tot;
		to[tot] = y;
		cap[tot] = 0;
		cost[tot] = -w;
		assert(tot<maxe);
	}
	int q[maxn], qb, qe;
	ll dis[maxn];
	bool inq[maxn];
	int qnxt(int x) {return (x+1)%maxn;}
	int qpre(int x) {return (x-1+maxn)%maxn;}
	void balance()
	{
		if (qb!=qe&&dis[q[qpre(qe)]]<dis[q[qb]])
		{
			swap(q[qpre(qe)], q[qb]);
		}
	}
	void spfa(int S, int N)
	{
		inq[S] = 1;
		for (int i=0; i<=N; i++) dis[i] = inf;
		dis[S] = 0;
		qb = qe = 0;
		q[qe++] = S;
		while (qb<qe)
		{
			int x = q[qb];
			inq[x] = 0;
			qb = qnxt(qb);
			balance();
			for (int i = head[x]; i; i=nxt[i])
			{
				if (cap[i]&&dis[to[i]]>dis[x]+cost[i])
				{
					dis[to[i]] = dis[x]+cost[i];
					if (!inq[to[i]])
					{
						inq[to[i]] = 1;
						q[qe] = to[i];
						qe = qnxt(qe);
						balance();
					}
				}
			}
		}
//		for (int i=1; i<=N; i++) cerr<<dis[i]<<" "; cerr<<endl;
	}
	
	bool vis[maxn];
	int dfs(int x, int T, int f)
	{
		if (x==T) return f;
		vis[x] = 1;
		int of = f;
		for (int i=head[x]; i; i=nxt[i])
		{
			if (!vis[to[i]]&&cap[i]&&dis[to[i]]==dis[x]+cost[i])
			{
				int u = to[i];
				int d = dfs(u, T, min(f, cap[i]));
				cap[i] -= d;
				cap[i^1] += d;
				f -= d;
				if (!f) return of;
			}
		}
		return of-f;
	}
	ll min_cost_max_flow(int S, int T, int K)
	{
		ll ans = 0;
		while (true)
		{
			spfa(S, T);
			if (dis[T]>=inf) return ans;
			while (true)
			{
				memset(vis, 0, sizeof(vis));
				int f = dfs(S, T, K);
				ftot += f;
				ans += 1ll*f*dis[T];
				if (f==0) break;
			}
		}
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
/*	for (int i=1; i<=K; i++)
	{
		cerr<<"("<<segx[i].FF<<","<<segx[i].SS<<") ("<<segy[i].FF<<","<<segy[i].SS<<")"<<endl;
	}
*/	
	int S = 2*K+2*n+1, T = S+1;
//	cerr<<"S="<<S<<" T="<<T<<endl;
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
	ll ans = F::min_cost_max_flow(S, T, K);
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
