#include <bits/stdc++.h>

using namespace std;

const int MX = 500005;

template<typename T> void read(T &x)
{
	char c = getchar(); x = 0;
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) x = x*10+c-'0', c = getchar();
}

int n, m, k, q;

struct UNION
{
	int fa[MX], siz[MX], stk[MX], top;
	bool val[MX];

	void init(int n)
	{
		for(int i=1; i<=n; i++)
		{
			fa[i] = i;
			siz[i] = 1;
			val[i] = 0;
		}
		top = 0;
	}

	pair<int, bool> id(int x)
	{
		if(x == fa[x]) return make_pair(x, 0);
		else
		{
			auto tmp = id(fa[x]);
			tmp.second ^= val[x];
			return tmp;
		}
	}

	void comb(int x, int y)
	{
		auto fx = id(x), fy = id(y);
		assert(fx != fy);
		if(fx.first == fy.first) return;
		if(siz[fx.first] > siz[fy.first]) swap(fx, fy);
		val[fx.first] = fx.second ^ fy.second ^ 1;
		siz[fy.first] += siz[fx.first];
		fa[fx.first] = fy.first;
		stk[++top] = fx.first;
	}

	void rev(int tar)
	{
		while(top > tar)
		{
			int x = stk[top--];
			siz[fa[x]] -= siz[x];
			fa[x] = x;
		}
	}
} U[51];

struct EDGE
{
	int u, v, c;

	EDGE (const int &u0 = 0, const int &v0 = 0, const int &c0 = 0) : u(u0), v(v0), c(c0) {}
};

struct NEXT_INTV
{
	int a, b, r, c, id;
	
	NEXT_INTV (const int &a0 = 0, const int &b0 = 0, const int &r0 = 0, const int &c0 = 0, const int &id0 = 0) : a(a0), b(b0), r(r0), c(c0), id(id0) {}
};

struct SEGT
{
	#define ls (a<<1)
	#define rs ((a<<1)|1)
	#define mid ((l+r)/2)

	vector<EDGE> tre[MX*4];
	int lst[MX];

	void add(int a, int l, int r, int ql, int qr, const EDGE &x)
	{
		if(ql<=l && r<=qr) tre[a].push_back(x);
		else if(ql>r || qr<l) return ;
		else add(ls, l, mid, ql, qr, x), add(rs, mid+1, r, ql, qr, x);
	}

	void dfs(int a, int l, int r, NEXT_INTV *arr)
	{
		int lim[51];
		for(int i=1; i<=50; i++) lim[i] = U[i].top;
		for(auto e : tre[a]) if(e.c) U[e.c].comb(e.u, e.v);
		if(l == r)
		{
			auto nu = U[arr[l].c].id(arr[l].a);
			auto nv = U[arr[l].c].id(arr[l].b);
			if(nu == nv)
			{
				puts("NO");
				add(1, 1, q, l+1, arr[l].r, EDGE(arr[l].a, arr[l].b, lst[arr[l].id]));
			}
			else
			{
				puts("YES");
				add(1, 1, q, l+1, arr[l].r, EDGE(arr[l].a, arr[l].b, arr[l].c));
				lst[arr[l].id] = arr[l].c;
			}
		}
		else dfs(ls, l, mid, arr), dfs(rs, mid+1, r, arr);
		for(int i=1; i<=50; i++) U[i].rev(lim[i]);
	}

	#undef ls
	#undef rs
	#undef mid
} T;

int u[MX], v[MX], col[MX], lst[MX];
NEXT_INTV nxt[MX];

void input()
{
	read(n), read(m), read(k), read(q);
	for(int i=1; i<=m; i++) read(u[i]), read(v[i]), col[i] = 0;
	for(int i=1; i<=q; i++)
	{
		int e, c;
		read(e), read(c);
		if(col[e]) nxt[lst[e]] = NEXT_INTV(u[e], v[e], i-1, col[e], e);
		lst[e] = i;
		col[e] = c;
	}
	for(int i=1; i<=m; i++)
		if(col[i])
			nxt[lst[i]] = NEXT_INTV(u[i], v[i], q, col[i], i);
}

int main()
{
	input();
	for(int i=1; i<=50; i++) U[i].init(n);
	T.dfs(1, 1, q, nxt);
	return 0;
}