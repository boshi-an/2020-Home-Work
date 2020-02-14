#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 2005;
const ll MOD = 1000000007;

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

struct EDGE
{
	int u, v, w;

	EDGE (const int &u0 = 0, const int &v0 = 0, const int &w0 = 0) : u(u0), v(v0), w(w0) {}

	bool operator < (const EDGE &t) const {return w < t.w;}
};

struct UNION
{
	int fa[MX];

	UNION () {for(int i=1; i<MX; i++) fa[i] = i;}

	int id(int x) {return x==fa[x] ? x : fa[x]=id(fa[x]);}
};

int n, m;
ll X, val[MX];
EDGE e[MX];

ll qpow(ll x, ll t)
{
	ll ret = 1;
	while(t)
	{
		if(t & 1) ret = ret * x % MOD;
		x = x * x % MOD;
		t >>= 1;
	}
	return ret;
}

ll mst(int force)
{
	ll ret = 0;
	UNION u;
	u.fa[e[force].u] = e[force].v, ret += e[force].w;
	for(int i=1; i<=m; i++)
	{
		if(u.id(e[i].u) != u.id(e[i].v))
		{
			u.fa[u.id(e[i].u)] = u.id(e[i].v);
			ret += e[i].w;
		}
	}
	return ret;
}

void input()
{
	read(n), read(m), read(X);
	for(int i=1; i<=m; i++)
	{
		int a, b, c;
		read(a), read(b), read(c);
		e[i] = EDGE(a, b, c);
	}
	sort(e+1, e+m+1);
}

void work()
{
	int sma = 0, big = 0, eqa = 0;
	for(int i=1; i<=m; i++) val[i] = mst(i);
	for(int i=1; i<=m; i++)
	{
		sma += (val[i]<X);
		eqa += (val[i]==X);
		big += (val[i]>X);
	}
	if(val[1] > X) printf("0\n");
	else if(val[1] == X) printf("%lld\n", (qpow(2, eqa)-2+MOD)*qpow(2, big)%MOD);
	else printf("%lld\n", 2*(qpow(2, eqa)-1)*qpow(2, big)%MOD);
}

int main()
{
	input();
	work();
	return 0;
}
