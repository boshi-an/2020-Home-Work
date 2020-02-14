#include <algorithm>
#include <iostream>
#include <assert.h>
#include <cstdio>

using namespace std;

const int MX = 300005;

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
	int u, v, i, w, wi;

	EDGE (const int &u0 = 0, const int &v0 = 0, const int &i0 = 0, const int &w0 = 0) : u(u0), v(v0), i(i0), w(w0) {}
};

struct UNION
{
	int cnt[2];
	int fa[MX], siz[MX];
	int stk[MX], top;

	void init(int n)
	{
		cnt[0] = cnt[1] = top = 0;
		for(int i=1; i<=n; i++) fa[i] = i, siz[i] = 1, cnt[1]++;
	}

	int root(int x) const
	{
		return x==fa[x] ? x : root(fa[x]);
	}

	void comb(int x, int y)
	{
		x = root(x), y = root(y);
		if(x == y) return;
		else
		{
			if(siz[x] > siz[y]) swap(x, y);
			cnt[siz[x]&1]--;
			cnt[siz[y]&1]--;
			siz[y] += siz[x];
			cnt[siz[y]&1]++;
			fa[x] = y;
			stk[++top] = x;
		}
	}

	void back_up(int bot)
	{
		while(top > bot)
		{
			int x = stk[top--];
			cnt[siz[fa[x]]&1]--;
			siz[fa[x]] -= siz[x];
			cnt[siz[fa[x]]&1]++;
			cnt[siz[x]&1]++;
			fa[x] = x;
		}
	}

	bool legal() const
	{
		return (cnt[1]==0);
	}
} U;

int n, m;
EDGE ei[MX], ew[MX];
int rak[MX];

auto cmpi = [](const EDGE &a, const EDGE &b){return a.i<b.i;};
auto cmpw = [](const EDGE &a, const EDGE &b){return a.w<b.w;};

void input()
{
	read(n), read(m);
	for(int i=1; i<=m; i++)
	{
		int a, b, c;
		read(a), read(b), read(c);
		ew[i] = ei[i] = EDGE(a, b, i, c);
	}
	sort(ei+1, ei+m+1, cmpi);
	sort(ew+1, ew+m+1, cmpw);
	for(int i=1; i<=m; i++) rak[ew[i].i] = i;
	for(int i=1; i<=m; i++) ei[i].wi = rak[i];
}

int ans[MX];
bool usd[MX];
int curx, cury;

void divide(int il, int ir, int wl, int wr)
{
	if(il > ir) return;
	//cout<<il<<" "<<ir<<" "<<wl<<" "<<wr<<" "<<curx<<" "<<cury<<endl;
	//assert(curx==il-1 && cury==wl-1);
	int im = (il+ir) / 2;
	int top1 = U.top, x1 = curx;
	while(curx < im)
	{
		curx++;
		if(ei[curx].wi <= cury) U.comb(ei[curx].u, ei[curx].v);
	}
	int top2 = U.top, y2 = cury;
	while(cury<wr && !U.legal())
	{
		cury++;
		if(ew[cury].i <= curx) U.comb(ew[cury].u, ew[cury].v);
	}
	if(!U.legal()) ans[im] = m+1;
	else ans[im] = cury;
	U.back_up(top2), cury = y2;
	divide(im+1, ir, wl, ans[im]);
	U.back_up(top1), curx = x1;
	int top3 = U.top, y3 = cury;
	while(cury+1 < ans[im])
	{
		cury++;
		if(ew[cury].i <= curx) U.comb(ew[cury].u, ew[cury].v);
	}
	divide(il, im-1, ans[im], wr);
	U.back_up(top3), cury = y3;
}

int main()
{
	input();
	U.init(n);
	divide(1, m, 1, m);
	for(int i=1; i<=m; i++) printf("%d\n", ans[i]==m+1 ? -1 : ew[ans[i]].w);
	return 0;
}