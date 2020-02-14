#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MV = 815;
const int ME = 1200006;
const ll oo = 1e18;

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

struct edge
{
	int u, v, f;
	ll c;
	int n;

	edge (const int &u0 = 0, const int &v0 = 0, const ll &f0 = 0, const ll &c0 = 0, const int &n0 = 0) : u(u0), v(v0), f(f0), c(c0), n(n0) {}
};

struct GRAPH
{
	edge e[ME];
	int fst[MV], lnum;

	void init() {memset(fst, 0xff, sizeof(fst)); lnum = -1;}
	
	GRAPH () {init();}
	
	void addeg(int nu, int nv, ll nc, int nf)
	{
		e[++lnum] = edge(nu, nv, nf, nc, fst[nu]), fst[nu] = lnum;
		e[++lnum] = edge(nv, nu, 0, -nc, fst[nv]), fst[nv] = lnum;
	}
	
	int que[MV], inq[MV], cur[MV];
	ll dis[MV];
	
	bool spfa(int frm, int tar)
	{
		int h = 1, t = 1, x, y;
		memset(dis, 0x9f, sizeof(dis));
		dis[frm] = 0;
		que[h] = frm;
		inq[frm] = 1;
		while(h >= t)
		{
			x = que[(t++)%MV];
			inq[x] = 0;
			for(int i=fst[x]; ~i; i=e[i].n)
			{
				y = e[i].v;
				if(e[i].f && dis[y]<dis[x]+e[i].c)
				{
					dis[y] = dis[x] + e[i].c;
					if(!inq[y]) que[(++h)%MV] = y, inq[y] = 1;
				}
			}
		}
		return (dis[tar] > -oo);
	}
	
	int dinic(int x, int t, int f)
	{
		if(x == t) return f;
		int a, y, now = 0;
		inq[x] = 1;
		for(int &i=cur[x]; ~i; i=e[i].n)
		{
			y = e[i].v;
			if(dis[y]==dis[x]+e[i].c && e[i].f && !inq[y])
			{
				a = dinic(y, t, min(e[i].f, f-now));
				now += a;
				e[i].f -= a;
				e[i^1].f += a;
				if(now == f) break;
			}
		}
		inq[x] = 0;
		return now;
	}
	
	pair<int, ll> costf(int s, int t)
	{
		ll cost = 0;
		int flow = 0;
		while(spfa(s, t))
		{
			memmove(cur, fst, sizeof(cur));
			int new_flow = dinic(s, t, ME);
			cost += dis[t] * new_flow;
			flow += new_flow;
		}
		return make_pair(flow, cost);
	}
} G;

int n, m;
int lx[MV], rx[MV];
int ly[MV], ry[MV];
int px[MV], py[MV];
ll pv[MV];
char qc[MV];
int qa[MV], qb[MV];
int global_s, global_t;

void input()
{
	read(n);
	for(int i=1; i<=n; i++) read(px[i]), read(py[i]), read(pv[i]);
	read(m);
	for(int i=1; i<=n; i++) lx[i] = 1, rx[i] = 100, ly[i] = 1, ry[i] = 100;
	for(int i=1; i<=m; i++)
	{
		qc[i] = getchar();
		while(!isalpha(qc[i])) qc[i] = getchar();
		read(qa[i]), read(qb[i]);
	}
}

void build(int num)
{
	for(int i=1; i<=num; i++) lx[i] = ly[i] = 1, rx[i] = ry[i] = 100;
	for(int i=1; i<=m; i++)
	{
		if(qb[i] > num) continue;
		if(qc[i] == 'L') cmax(lx[qb[i]+1], qa[i]+1);
		if(qc[i] == 'R') cmin(rx[num-qb[i]], qa[i]-1);
		if(qc[i] == 'D') cmax(ly[qb[i]+1], qa[i]+1);
		if(qc[i] == 'U') cmin(ry[num-qb[i]], qa[i]-1);
	}
	for(int i=2; i<=num; i++) cmax(lx[i], lx[i-1]), cmax(ly[i], ly[i-1]);
	for(int i=num-1; i>=1; i--) cmin(rx[i], rx[i+1]), cmin(ry[i], ry[i+1]);
	G.init();
	for(int i=1; i<=num; i++)
	{
		for(int j=1; j<=n; j++)
		{
			if(lx[i]<=px[j] && px[j]<=rx[i]) G.addeg(i, num*2+j, 0, 1);
			if(ly[i]<=py[j] && py[j]<=ry[i]) G.addeg(num*2+n+j, num+i, 0, 1);
		}
	}
	for(int i=1; i<=n; i++) G.addeg(num*2+i, num*2+n+i, pv[i], 1);
	global_s = num*2+n*2+1, global_t = global_s+1;
	for(int i=1; i<=num; i++) G.addeg(global_s, i, 0, 1), G.addeg(num+i, global_t, 0, 1);
}

void work()
{
	ll ans = 0;
	for(int i=1; i<=n; i++)
	{
		build(i);
		auto ret = G.costf(global_s, global_t);
		if(ret.first != i) break;
		else cmax(ans, ret.second);
	}
	printf("%lld\n", ans);
}

int main()
{
	input();
	work();
	return 0;
}