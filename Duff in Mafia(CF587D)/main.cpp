#include <bits/stdc++.h>

using namespace std;

const int MX = 1000005;

typedef vector<int> veci;

template<typename T> void cmin(T &x, const T &y)
{
	if(y < x) x = y;
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

int n, m;
int u[MX], v[MX], c[MX], w[MX];
veci con[MX];

int id(int x, int b)
{
	return m*b + x;
}

struct GRAPH
{
	int fst[MX], nxt[MX], v[MX], deg[MX], lnum;
	int cnt;

	void addeg(int nu, int nv)
	{
		//cout<<nu<<" "<<nv<<endl;
		nxt[++lnum] = fst[nu];
		fst[nu] = lnum;
		v[lnum] = nv;
		deg[nv]++;
	}
} G, H;

struct BELT
{
	veci pos;

	void build_pre(veci::iterator l, veci::iterator r, GRAPH &g)
	{
		if(l == r) return;
		for(auto i=l; i!=r; i++)
		{
			pos.push_back(++g.cnt);
			g.addeg(g.cnt, *i);
		}
		for(auto i=pos.begin()+1; i!=pos.end(); i++) g.addeg(*i, *(i-1));
	}

	void build_suf(veci::iterator l, veci::iterator r, GRAPH &g)
	{
		if(l == r) return;
		for(auto i=l; i!=r; i++)
		{
			pos.push_back(++g.cnt);
			g.addeg(g.cnt, *i);
		}
		for(auto i=pos.begin()+1; i!=pos.end(); i++) g.addeg(*(i-1), *i);
	}
};

void input()
{
	read(n), read(m);
	for(int i=1; i<=m; i++)
	{
		read(u[i]), read(v[i]), read(c[i]), read(w[i]);
		con[u[i]].push_back(i);
		con[v[i]].push_back(i);
	}
}

void fucked()
{
	puts("No");
	exit(0);
}

void build()
{
	G.cnt = m*2;
	for(int i=1; i<=n; i++)
	{
		auto cmp = [=](int a, int b){return c[a] < c[b];};
		sort(con[i].begin(), con[i].end(), cmp);
		for(auto x=con[i].begin(); x!=con[i].end(); x++)
		{
			if(x!=con[i].begin() && c[*x]==c[*(x-1)]) continue;
			auto eqr = equal_range(con[i].begin(), con[i].end(), *x, cmp);
			if(eqr.second-eqr.first > 2) fucked();
			if(eqr.second-eqr.first == 2)
			{
				auto a = eqr.first, b = a+1;
				G.addeg(id(*a, 0), id(*b, 1));
				G.addeg(id(*b, 0), id(*a, 1));
			}
		}
		BELT pre, suf;
		pre.build_pre(con[i].begin(), con[i].end(), G);
		suf.build_suf(con[i].begin(), con[i].end(), G);
		for(int a=0; a<con[i].size(); a++)
		{
			if(a) G.addeg(id(con[i][a], 1), pre.pos[a-1]);
			if(a+1 < con[i].size()) G.addeg(id(con[i][a], 1), suf.pos[a+1]);
		}
	}
}

int dfn[MX], low[MX], bel[MX];

bool check(int lim)
{
	H = G;
	for(int i=1; i<=m; i++)
		if(w[i] > lim)
			H.addeg(id(i, 1), id(i, 0));
	int dfc = 0, col = 0;
	stack<int> stk;
	memset(dfn, 0, sizeof(dfn));
	memset(bel, 0, sizeof(bel));
	function<void(int)> tarjan = [&](int x)
	{
		low[x] = dfn[x] = ++dfc;
		stk.push(x);
		for(int i=H.fst[x]; i; i=H.nxt[i])
		{
			int y = H.v[i];
			if(!dfn[y]) tarjan(y), cmin(low[x], low[y]);
			else if(!bel[y]) cmin(low[x], dfn[y]);
		}
		if(low[x] == dfn[x])
		{
			col++;
			while(stk.top() != x)
			{
				bel[stk.top()] = col;
				stk.pop();
			}
			bel[stk.top()] = col;
			stk.pop();
		}
	};
	for(int i=1; i<=H.cnt; i++)
		if(!dfn[i])
			tarjan(i);
	/*for(int i=1; i<=m; i++)
		cout<<bel[id(i, 0)]<<" "<<bel[id(i, 1)]<<endl;*/
	for(int i=1; i<=m; i++)
		if(bel[id(i, 0)] == bel[id(i, 1)])
			return false;
	return true;
}

void work()
{
	int l = 0, r = 1000000005, mid, ans;
	while(l < r)
	{
		mid = (l+r) / 2;
		if(check(mid)) ans = r = mid;
		else ans = l = mid+1;
	}
	if(ans > 1e9) fucked();
	puts("Yes");
	check(ans);
	vector<int> usd;
	for(int i=1; i<=m; i++)
		if(bel[id(i, 1)] < bel[id(i, 0)])
			usd.push_back(i);
	printf("%d %d\n", ans, (int)usd.size());
	for(auto i : usd) printf("%d ", i);
}

int main()
{
	input();
	build();
	work();
	return 0;
}

/*
5 7
2 1 3 7
3 1 1 6
5 4 1 8
4 5 1 1
3 2 2 3
4 5 2 5
2 3 2 4
*/