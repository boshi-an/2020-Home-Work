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

int n;
double val[MX];
int fst[MX], nxt[MX*2], v[MX*2], w[MX*2], lnum;

void addeg(int nu, int nv, int nw)
{
	nxt[++lnum] = fst[nu];
	fst[nu] = lnum;
	v[lnum] = nv;
	w[lnum] = nw;
}

void input()
{
	read(n);
	for(int i=1; i<=n; i++) read(val[i]);
	for(int i=1; i<n; i++)
	{
		int a, b, c;
		read(a), read(b), read(c);
		addeg(a, b, c);
		addeg(b, a, c);
	}
}

int siz[MX], msiz[MX], cen;
bool ban[MX];
pair<double, int> ans(1e28, 0);

void gsize(int x, int f)
{
	siz[x] = 1, msiz[x] = 0;
	for(int i=fst[x]; i; i=nxt[i])
	{
		int y = v[i];
		if(!ban[y] && y!=f)
		{
			gsize(y, x);
			siz[x] += siz[y];
			cmax(msiz[x], siz[y]);
		}
	}
}

void gcent(int x, int f, int s)
{
	cmax(msiz[x], s-siz[x]);
	if(!cen || msiz[x]<msiz[cen]) cen = x;
	for(int i=fst[x]; i; i=nxt[i])
	{
		int y = v[i];
		if(!ban[y] && y!=f) gcent(y, x, s);
	}
}

double calc(int x, int f, int d, double p)
{
	double ret = pow(d, p)*val[x];
	for(int i=fst[x]; i; i=nxt[i])
		if(v[i] != f)
			ret += calc(v[i], x, d+w[i], p);
	return ret;
}

int divide(int x)
{
	gsize(x, 0);
	gcent(x, 0, siz[x]);
	x = cen;
	ban[x] = 1;
	double der = calc(x, 0, 0, 0.5);
	cmin(ans, make_pair(calc(x, 0, 0, 1.5), x));
	for(int i=fst[x]; i; i=nxt[i])
	{
		if(ban[v[i]]) continue;
		double sub = calc(v[i], x, w[i], 0.5);
		if(sub > der-sub) return divide(v[i]);
	}
	return x;
}

int main()
{
	input();
	divide(1);
	printf("%d %.8lf\n", ans.second, ans.first);
	return 0;
}
