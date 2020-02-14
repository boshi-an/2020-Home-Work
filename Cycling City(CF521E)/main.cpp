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

	GRAPH ()
	{
		memset(fst, 0xff, sizeof(fst));
		lnum = -1;
	}

	void addeg(int nu, int nv)
	{
		nxt[++lnum] = fst[nu];
		fst[nu] = lnum;
		u[lnum] = nu;
		v[lnum] = nv;
	}

	int bel[MX], dfn[MX], low[MX], stk[MX], top, dfc, col;
	vector<int> scc[MX];
	vector<int> scc_e[MX];

	void tarjan(int x, int fe)
	{
		low[x] = dfn[x] = ++dfc;
		for(int i=fst[x]; ~i; i=nxt[i])
		{
			if((i^1) == fe) continue;
			int y = v[i];
			if(!dfn[y])
			{
				stk[++top] = i;
				tarjan(y, i);
				cmin(low[x], low[y]);
				if(low[y] >= dfn[x])
				{
					col++;
					while(stk[top] != i)
					{
						int e = stk[top--];
						if(bel[u[e]] != col) bel[u[e]] = col, scc[col].push_back(u[e]);
						if(bel[v[e]] != col) bel[v[e]] = col, scc[col].push_back(v[e]);
						scc_e[col].push_back(e);
						scc_e[col].push_back(e^1);
					}
					int e = stk[top--];
					if(bel[u[e]] != col) bel[u[e]] = col, scc[col].push_back(u[e]);
					if(bel[v[e]] != col) bel[v[e]] = col, scc[col].push_back(v[e]);
					scc_e[col].push_back(e);
					scc_e[col].push_back(e^1);
				}
			}
			else if(dfn[y] < dfn[x]) stk[++top] = i, cmin(low[x], dfn[y]);
		}
	}

	void init()
	{
		for(int i=0; i<=lnum; i++) fst[u[i]] = -1;
		lnum = -1;
	}
} G, H;

int n, m;

void input()
{
	G.init();
	read(n), read(m);
	for(int i=1; i<=m; i++)
	{
		int a, b;
		read(a), read(b);
		G.addeg(a, b);
		G.addeg(b, a);
	}
}

int deg[MX], pre[MX];
vector<int> stk_e, cyc_e;
bool vis[MX], usd[MX];
bool ban[MX*2];

bool get_loop(int x, int f)
{
	if(vis[x])
	{
		cyc_e.clear();
		while(H.u[stk_e.back()] != x) cyc_e.push_back(stk_e.back()^1), stk_e.pop_back();
		cyc_e.push_back(stk_e.back()^1), stk_e.pop_back();
		return true;
	}
	vis[x] = 1;
	for(int i=H.fst[x]; ~i; i=H.nxt[i])
		if(H.v[i] != f)
		{
			stk_e.push_back(i);
			if(get_loop(H.v[i], x))
				return true;
		}
	assert(0);
	return false;
}

void get_path(int x)
{
	queue<int> que;
	que.push(x);
	usd[x] = 1;
	while(que.size())
	{
		x = que.front();
		que.pop();
		for(int i=H.fst[x]; ~i; i=H.nxt[i])
		{
			int y = H.v[i];
			if(!usd[y] && !ban[i])
			{
				pre[y] = i;
				que.push(y);
				usd[y] = 1;
			}
		}
	}
}

vector<vector<int> > ans;
vector<int> stk;

bool print_path(int x, int f, int t)
{
	stk.push_back(x);
	if(x == t)
	{
		ans.push_back(stk);
		assert(ans.size() <= 2);
		stk.pop_back();
		return (ans.size() == 2);
	}
	for(int i=H.fst[x]; ~i; i=H.nxt[i])
	{
		int y = H.v[i];
		if(y!=f && vis[x] && vis[y] && ban[i])
			if(print_path(y, x, t))
				return true;
	}
	stk.pop_back();
	return false;
}

void work()
{
	for(int i=1; i<=n; i++)
		if(!G.dfn[i])
			G.tarjan(i, -2);
	for(int i=1; i<=G.col; i++)
	{
		vector<int> scc_e = G.scc_e[i], scc = G.scc[i];
		sort(scc_e.begin(), scc_e.end());
		scc_e.erase(unique(scc_e.begin(), scc_e.end()), scc_e.end());
		sort(scc_e.begin(), scc_e.end(), [](int a, int b){return (a&1) < (b&1);});
		while(scc_e.back()&1) scc_e.pop_back();
		H.init();
		for(auto e : scc_e) H.addeg(G.u[e], G.v[e]), H.addeg(G.v[e], G.u[e]);
		if(scc_e.size() <= scc.size()) continue;

		stk_e.clear();
		for(auto x : scc) vis[x] = 0;
		assert(get_loop(*scc.begin(), 0));

		int s, t;
		stk_e.clear();
		for(auto x : scc) vis[x] = 0, deg[x] = 0, usd[x] = 0, pre[x] = -2;
		for(auto e : scc_e) deg[G.v[e]]++, deg[G.u[e]]++;
		for(auto e : cyc_e) ban[e] = ban[e^1] = 1, vis[H.u[e]] = vis[H.v[e]] = 1;
		for(auto x : scc)
		{
			if(deg[x]>2 && vis[x])
			{
				s = x;
				get_path(x);
				for(auto y : scc)
					if(usd[y] && vis[y] && x!=y)
					{
						t = y;
						break;
					}
				break;
			}
		}
		print_path(s, s, t);
		vector<int> mid;
		int x = t;
		while(pre[t] >= 0) mid.push_back(t), t = H.u[pre[t]];
		mid.push_back(t);
		reverse(mid.begin(), mid.end());
		ans.push_back(mid);
		assert(ans.size() == 3);
		puts("YES");
		for(auto seq : ans)
		{
			printf("%d ", (int)seq.size());
			for(auto x : seq) printf("%d ", x);
			putchar('\n');
		}
		return;
	}
	puts("NO");
}

int main()
{
	input();
	work();
	return 0;
}
