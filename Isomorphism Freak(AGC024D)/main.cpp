#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 105;

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

int n;
int fst[MX], nxt[MX*2], u[MX*2], v[MX*2], lnum;

void addeg(int nu, int nv)
{
	nxt[++lnum] = fst[nu];
	fst[nu] = lnum;
	u[lnum] = nu;
	v[lnum] = nv;
}

void input()
{
	read(n);
	for(int i=1; i<n; i++)
	{
		int a, b;
		read(a), read(b);
		addeg(a, b);
		addeg(b, a);
	}
}

int dis[MX], mxdeg[MX];
int mxp;
vector<int> cur, dia;

void dfs(int x, int f, int d)
{
	cur.push_back(x);
	if(d > dis[mxp]) mxp = x, dia = cur;
	dis[x] = d;
	for(int i=fst[x]; i; i=nxt[i])
		if(v[i] != f)
			dfs(v[i], x, d+1);
	cur.pop_back();
};

ll calc(int x, int y)
{
	mxp = 0;
	dfs(x, y, 1);
	dfs(y, x, 1);
	ll leaf = 1;
	memset(mxdeg, 0, sizeof(mxdeg));
	for(int x=1; x<=n; x++)
	{
		int deg = 0;
		for(int i=fst[x]; i; i=nxt[i])
		{
			int y = v[i];
			if(dis[y] == dis[x]+1) deg++;
		}
		cmax(mxdeg[dis[x]], deg);
	}
	for(int i=1; i<=n; i++)
		if(mxdeg[i])
			leaf *= mxdeg[i];
	if(x != y) leaf *= 2;
	return leaf;
}

void work()
{
	ll ans_len = n+1, ans_leaf = 0;
	for(int i=1; i<=n; i++)
	{
		ll cur_leaf = calc(i, i);
		if(dis[mxp] < ans_len) ans_len = dis[mxp], ans_leaf = cur_leaf;
		else if(dis[mxp] == ans_len) cmin(ans_leaf, cur_leaf);
	}
	for(int i=1; i<=lnum; i+=2)
	{
		ll cur_leaf = calc(u[i], v[i]);
		if(dis[mxp] < ans_len) ans_len = dis[mxp], ans_leaf = cur_leaf;
		else if(dis[mxp] == ans_len) cmin(ans_leaf, cur_leaf);
	}
	printf("%lld %lld\n", ans_len, ans_leaf);
}

int main()
{
	input();
	work();
	return 0;
}
