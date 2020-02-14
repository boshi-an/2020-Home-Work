#include <bits/stdc++.h>

using namespace std;

const int ME = 1205;
const int MX = 105;
const int oo = 1231231231;

template<typename T> void cmax(T &x, const T &y)
{
	if(y > x) x = y;
}

template<typename T> void read(T &x)
{
	x = 0;
	char c = getchar();
	bool f = 0;
	while(!isdigit(c) && c!='-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(isdigit(c)) x = x*10+c-'0', c = getchar();
	if(f) x = -x;
}

struct EDGE
{
	int u, v, f, c, n;
	
	EDGE (const int &u0 = 0, const int &v0 = 0, const int &f0 = 0, const int &c0 = 0, const int &n0 = 0) : u(u0), v(v0), f(f0), c(c0), n(n0) {}
};

struct GRAPH
{
	EDGE e[ME];
	int fst[MX], lnum;
	
	GRAPH () {memset(fst, 0xff, sizeof(fst)); lnum = -1;}
	
	void addeg(int nu, int nv, int nf, int nc)
	{
		e[++lnum] = EDGE(nu, nv, nf, nc, fst[nu]), fst[nu] = lnum;
		e[++lnum] = EDGE(nv, nu, 0, -nc, fst[nv]), fst[nv] = lnum;
	}
	
	int dis[MX], que[MX], inq[MX], cur[MX], pre[MX], vis[MX];
	
	int spfa(int n)
	{
		int h = n, t = 1;
		memset(vis, 0, sizeof(vis));
		memset(dis, 0, sizeof(dis));
		memset(inq, 0, sizeof(inq));
		memset(pre, 0xff, sizeof(pre));
		for(int i=1; i<=n; i++) que[i] = i;
		while(h >= t)
		{
			int x = que[(t++)%MX];
			inq[x] = 0;
			if(vis[x] >= n) return x;
			for(int i=fst[x]; ~i; i=e[i].n)
			{
				int y = e[i].v;
				if(dis[y]>dis[x]+e[i].c && e[i].f)
				{
					dis[y] = dis[x]+e[i].c;
					pre[y] = i;
					if(!inq[y])
					{
						que[(++h)%MX] = y;
						vis[y]++;
						inq[y] = 1;
					}
				}
			}
		}
		return 0;
	}
	
	int costf(int n)
	{
		int cost = 0;
		while(1)
		{
			int beg = spfa(n);
			if(!beg) break;
			memset(vis, 0, sizeof(vis));
			int x = beg;
			while(!vis[x]) vis[x] = 1, x = e[pre[x]].u;
			beg = x;
			int nc = 0, nf = +oo;
			do
			{
				nf = min(nf, e[pre[x]].f);
				nc += e[pre[x]].c;
				x = e[pre[x]].u;
			} while (x != beg);
			do
			{
				e[pre[x]].f -= nf;
				e[pre[x]^1].f += nf;
				x = e[pre[x]].u;
			} while (x != beg);
			cost += nc*nf;
		}
		return cost;
	}
} G;

int n, m;

int main()
{
	int ans = 0;
	read(n), read(m);
	for(int i=1; i<=m; i++)
	{
		int u, v, c, f;
		read(u), read(v), read(c), read(f);
		ans += f;
		if(f <= c)
		{
			G.addeg(u, v, f, -1);
			G.addeg(u, v, c-f, 1);
			G.addeg(u, v, +oo, 2);
		}
		else
		{
			G.addeg(u, v, c, -1);
			G.addeg(u, v, f-c, 0);
			G.addeg(u, v, +oo, 2);
		}
	}
	G.addeg(n, 1, +oo, 0);
	printf("%d\n", ans + G.costf(n));
	return 0;
}