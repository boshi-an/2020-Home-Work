#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 2003, ME = 200005;

template <typename T> void cmin(T &x, const T &y)
{
	if(y < x) x = y;
}

template <typename T> void cmax(T &x, const T &y)
{
	if(y > x) x = y;
}

template <typename T> void read(T &x)
{
	x = 0; char c = getchar(); bool f = 0;
	while(!isdigit(c) && c!='-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(isdigit(c)) x = x*10+c-'0', c = getchar();
	if(f) x = -x;
}

struct GRAPH
{
	int fst[MX], nxt[ME], v[ME], w[ME], lnum;

	void addeg(int nu, int nv, int nw)
	{
		nxt[++lnum] = fst[nu];
		fst[nu] = lnum;
		v[lnum] = nv;
		w[lnum] = nw;
	}

	priority_queue<pair<ll, int> > que;

	void dijkstra(int s, ll *dis, int num)
	{
		fill(dis+1, dis+num+1, 1e18);
		dis[s] = 0;
		que.push(make_pair(0, s));
		while(!que.empty())
		{
			auto x = que.top();
			que.pop();
			if(-x.first != dis[x.second]) continue;
			for(int i=fst[x.second]; i; i=nxt[i])
			{
				auto y = make_pair(x.first-w[i], v[i]);
				if(-y.first < dis[y.second])
				{
					dis[y.second] = -y.first;
					que.push(y);
				}
			}
		}
	}
} G;

int n, m, s, t;
ll ds[MX], dt[MX], pi[MX];
int num[MX][MX];
int nf[MX][MX], ng[MX][MX];
ll sum[MX][MX];
ll f[MX][MX], g[MX][MX], mxf[MX][MX], mxg[MX][MX];

void input()
{
	int a, b, c;
	read(n), read(m);
	read(s), read(t);
	for(int i=1; i<=n; i++) read(pi[i]);
	for(int i=1; i<=m; i++)
	{
		read(a), read(b), read(c);
		G.addeg(a, b, c);
		G.addeg(b, a, c);
	}
}

void discrete(ll *seq, int tot)
{
	static ll rel[MX];
	int num = 0;
	for(int i=1; i<=tot; i++) rel[++num] = seq[i];
	sort(rel+1, rel+num+1);
	num = unique(rel+1, rel+num+1) - rel - 1;
	for(int i=1; i<=tot; i++) seq[i] = lower_bound(rel+1, rel+num+1, seq[i]) - rel;
}

void work()
{
	G.dijkstra(s, ds, n);
	G.dijkstra(t, dt, n);
	discrete(ds, n);
	discrete(dt, n);
	for(int i=1; i<=n; i++) sum[ds[i]][dt[i]] += pi[i], num[ds[i]][dt[i]]++;
	for(int i=n; i>=1; i--)
		for(int j=n; j>=1; j--)
		{
			sum[i][j] += sum[i+1][j] + sum[i][j+1] - sum[i+1][j+1];
			num[i][j] += num[i+1][j] + num[i][j+1] - num[i+1][j+1];
			if(num[i][j]-num[i][j+1]) ng[i][j] = j+1;
			else ng[i][j] = ng[i][j+1];
			if(num[i][j]-num[i+1][j]) nf[i][j] = i+1;
			else nf[i][j] = nf[i+1][j];
		}
	memset(f, 0x9f, sizeof(f));
	memset(g, 0x9f, sizeof(g));
	for(int i=1; i<=n+1; i++)
		for(int j=1; j<=n+1; j++)
			if(!num[i][j])
				f[i][j] = g[i][j] = 0;
	memmove(mxf, f, sizeof(mxf));
	memmove(mxg, g, sizeof(mxg));
	for(int i=n; i>=1; i--)
	{
		for(int j=n; j>=1; j--)
		{
			if(ng[i][j])
			{
				f[i][j] = mxg[i][ng[i][j]] + sum[i][j];
				mxf[i][j] = max(mxf[i+1][j], -f[i][j]-sum[i][j]);
			}
			else mxf[i][j] = mxf[i+1][j];
			if(nf[i][j])
			{
				g[i][j] = mxf[nf[i][j]][j] + sum[i][j];
				mxg[i][j] = max(mxg[i][j+1], -g[i][j]-sum[i][j]);
			}
			else mxg[i][j] = mxg[i][j+1];
		}
	}
	if(g[1][1] == 0) puts("Flowers");
	else if(g[1][1] > 0) puts("Break a heart");
	else puts("Cry");
	//printf("%lld\n", g[1][1]);
}

int main()
{
	input();
	work();
	return 0;
}
