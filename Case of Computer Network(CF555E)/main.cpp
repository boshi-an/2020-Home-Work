#include <bits/stdc++.h>

using namespace std;

const int MX = 200005;

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
	int fst[MX], nxt[MX*2], u[MX*2], v[MX*2], lnum;

	void init()
	{
		memset(fst, 0xff, sizeof(fst));
		lnum= -1;
	}

	void addeg(int nu, int nv)
	{
		nxt[++lnum] = fst[nu];
		fst[nu] = lnum;
		u[lnum] = nu;
		v[lnum] = nv;
	}

	int col[MX], dfn[MX], low[MX], stk[MX], ins[MX], top, dfc, cnt;

	void gcon(int x, int fi)
	{
		dfc++;
		dfn[x] = low[x] = dfc;
		stk[++top] = x;
		ins[x] = 1;
		for(int i=fst[x]; ~i; i=nxt[i])
		{
			if(i == (fi^1)) continue;
			int y = v[i];
			if(!dfn[y]) gcon(y, i), cmin(low[x], low[y]);
			else if(ins[y]) cmin(low[x], dfn[y]);
		}
		if(low[x] == dfn[x])
		{
			cnt++;
			while(stk[top] != x)
			{
				int y = stk[top--];
				col[y] = cnt;
				ins[y] = 0;
			}
			int y = stk[top--];
			col[y] = cnt;
			ins[y] = 0;
		}
	}

	int fa[MX][20], dep[MX];

	void dfs(int x, int f)
	{
		fa[x][0] = f;
		dep[x] = dep[f] + 1;
		for(int i=1; i<20; i++) fa[x][i] = fa[fa[x][i-1]][i-1];
		for(int i=fst[x]; ~i; i=nxt[i])
			if(v[i] != f)
				dfs(v[i], x);
	}

	int lca(int x, int y)
	{
		if(dep[x] < dep[y]) swap(x, y);
		for(int i=19; i>=0; i--)
			if(dep[fa[x][i]] >= dep[y])
				x = fa[x][i];
		if(x == y) return x;
		for(int i=19; i>=0; i--)
			if(fa[x][i] != fa[y][i])
				x = fa[x][i], y = fa[y][i];
		return fa[x][0];
	}

	int tag[MX];

	void gsum(int x, int f)
	{
		for(int i=fst[x]; ~i; i=nxt[i])
			if(v[i] != f)
				gsum(v[i], x), tag[x] += tag[v[i]];
	}

	GRAPH () {init();}
} G, H, UP, DN;

int n, m, q;
int si[MX], di[MX];

void input()
{
	int a, b;
	read(n), read(m), read(q);
	for(int i=1; i<=m; i++)
	{
		read(a), read(b);
		G.addeg(a, b);
		G.addeg(b, a);
	}
	for(int i=1; i<=q; i++) read(si[i]), read(di[i]);
}

bool fucked;
bool vis[MX];

void check(int x, int f)
{
	vis[x] = 1;
	for(int i=H.fst[x]; ~i; i=H.nxt[i])
	{
		int y = H.v[i];
		if(y == f) continue;
		check(y, x);
		//cout<<y<<" "<<DN.tag[y]<<" "<<UP.tag[y]<<endl;
		if(DN.tag[y] && UP.tag[y]) fucked = 1;
	}
}

void work()
{
	for(int i=1; i<=n; i++)
		if(!G.dfn[i])
			G.gcon(i, -1);
	//for(int i=1; i<=n; i++) cout<<i<<" "<<G.col[i]<<endl;
	for(int i=0; i<=G.lnum; i++)
		if(G.col[G.u[i]] != G.col[G.v[i]])
			H.addeg(G.col[G.u[i]], G.col[G.v[i]]);
	memset(H.fa[0], 0, sizeof(H.fa[0]));
	H.dep[0] = 0;
	for(int i=1; i<=G.cnt; i++)
		if(!H.dep[i])
			H.dfs(i, 0);
	DN = UP = H;
	for(int i=1; i<=q; i++)
	{
		int a = G.col[si[i]], b = G.col[di[i]];
		int l = H.lca(a, b);
		if(l == 0) fucked = 1;
		UP.tag[a]++, DN.tag[b]++, UP.tag[l]--, DN.tag[l]--;
	}
	for(int i=1; i<=G.cnt; i++)
		if(!vis[i])
		{
			UP.gsum(i, 0);
			DN.gsum(i, 0);
			check(i, 0);
		}
	if(!fucked) puts("Yes");
	else puts("No");
}

int main()
{
	input();
	work();
	return 0;
}
