#include <bits/stdc++.h>
#define mov(x) (1<<(x))

using namespace std;

typedef long long ll;

const int MX = 300003;
const ll B1 = 131;
const ll M1 = 998244353;
const ll B2 = 1331;
const ll M2 = 1000000007;

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

ll qpow(ll x, ll t, ll p)
{
	ll ans = 1;
	while(t)
	{
		if(t & 1) ans = ans * x % p;
		x = x * x % p;
		t >>= 1;
	}
	return ans;
}

ll inv(ll x, ll p)
{
	return qpow(x, p-2, p);
}

struct VAL
{
	ll h1, h2;
	
	VAL (const ll &a0 = 0, const ll &b0 = 0) : h1(a0), h2(b0) {}
	VAL operator + (const VAL &t) const {return VAL((h1+t.h1)%M1, (h2+t.h2)%M2);}
	VAL operator - (const VAL &t) const {return VAL((h1-t.h1+M1)%M1, (h2-t.h2+M2)%M2);}
	VAL operator * (const VAL &t) const {return VAL(h1*t.h1%M1, h2*t.h2%M2);}
	bool operator == (const VAL &t) const {return h1==t.h1 && h2==t.h2;}
};

struct INTV
{
	int l, r;

	INTV (const int &l0 = 0, const int &r0 = 0) : l(l0), r(r0) {}
	int len () const {return abs(r-l)+1;}
	INTV pre(int x)
	{
		if(l < r) return INTV(l, l+x-1);
		else return INTV(l, l-x+1);
	}
	void cut(int x)
	{
		if(l < r) l += x;
		else l -= x;
	}
};

int n, m;
int fst[MX], nxt[MX*2], v[MX*2], lnum;
char str[MX];

void addeg(int nu, int nv)
{
	nxt[++lnum] = fst[nu];
	fst[nu] = lnum;
	v[lnum] = nv;
}

void input()
{
	read(n);
	scanf("%s", str+1);
	for(int i=1; i<n; i++)
	{
		int a, b;
		read(a), read(b);
		addeg(a, b);
		addeg(b, a);
	}
	read(m);
}

int dep[MX];
VAL has[MX], rev[MX];
VAL pwb[MX], pwr[MX];
int fa[MX], siz[MX], son[MX], top[MX], dfn[MX], rak[MX], dfc;

void dfs1(int x, int f)
{
	fa[x] = f;
	siz[x] = 1;
	dep[x] = dep[f]+1;
	for(int i=fst[x]; i; i=nxt[i])
	{
		int y = v[i];
		if(y == f) continue;
		dfs1(y, x);
		siz[x] += siz[y];
		if(siz[y] > siz[son[x]]) son[x] = y;
	}
}

void dfs2(int x, int f, int t)
{
	dfn[x] = ++dfc;
	rak[dfc] = x;
	top[x] = t;
	if(son[x]) dfs2(son[x], x, t);
	for(int i=fst[x]; i; i=nxt[i])
		if(v[i]!=f && v[i]!=son[x])
			dfs2(v[i], x, v[i]);
}

void init()
{
	pwb[0] = VAL(1, 1), pwb[1] = VAL(B1, B2);
	pwr[0] = VAL(1, 1), pwr[1] = VAL(inv(B1, M1), inv(B2, M2));
	for(int i=1; i<=n; i++) pwb[i] = pwb[i-1] * pwb[1], pwr[i] = pwr[i-1] * pwr[1];
	dfs1(1, 0);
	dfs2(1, 0, 1);
	for(int i=1; i<=n; i++)
	{
		has[i] = has[i-1] + VAL(str[rak[i]], str[rak[i]])*pwb[i];
		rev[i] = rev[i-1] + VAL(str[rak[i]], str[rak[i]])*pwr[i];
	}
}

VAL get_has(INTV x)
{
	if(x.l <= x.r) return (has[x.r]-has[x.l-1]) * pwr[x.l];
	else return (rev[x.l]-rev[x.r-1]) * pwb[x.l];
}

vector<INTV> get_intv(int x, int y)
{
	vector<INTV> ret, tmp;
	int fx = top[x], fy = top[y];
	while(fx != fy)
	{
		if(dep[fx] > dep[fy])
		{
			ret.push_back(INTV(dfn[x], dfn[fx]));
			x = fa[fx];
			fx = top[x];
		}
		else
		{
			tmp.push_back(INTV(dfn[fy], dfn[y]));
			y = fa[fy];
			fy = top[y];
		}
	}
	ret.push_back(INTV(dfn[x], dfn[y]));
	for(auto i=tmp.rbegin(); i!=tmp.rend(); i++) ret.push_back(*i);
	return ret;
}

pair<INTV, INTV> get_next(vector<INTV>::iterator &a, vector<INTV>::iterator &b)
{
	pair<INTV, INTV> ret;
	if(a->len() == b->len()) ret.first = *a, ret.second = *b, a++, b++;
	else if(a->len() < b->len()) ret.first = *a, ret.second = b->pre(a->len()), b->cut(a->len()), a++;
	else ret.first = a->pre(b->len()), ret.second = *b, a->cut(b->len()), b++;
	return ret;
}

int get_lcp(INTV a, INTV b)
{
	assert(a.len() == b.len());
	int l = 0, r = a.len(), mid = 0, ans = 0;
	while(l < r)
	{
		mid = (l+r+1) / 2;
		if(get_has(a.pre(mid)) == get_has(b.pre(mid))) ans = l = mid;
		else ans = r = mid-1;
	}
	return ans;
}

int get_lcp(vector<INTV> a, vector<INTV> b)
{
	auto p = a.begin(),  q = b.begin();
	int ret = 0;
	while(p!=a.end() && q!=b.end())
	{
		auto tmp = get_next(p, q);
		if(get_has(tmp.first) == get_has(tmp.second)) ret += tmp.first.len();
		else return ret + get_lcp(tmp.first, tmp.second);
	}
	return ret;
}

void work()
{
	int a, b, c, d;
	for(int i=1; i<=m; i++)
	{
		read(a), read(b), read(c), read(d);
		auto s1 = get_intv(a, b), s2 = get_intv(c, d);
		printf("%d\n", get_lcp(s1, s2));
	}
}

int main()
{
	input();
	init();
	work();
	return 0;
}

/*
6 
bbbabb 
2 1 
3 2 
4 3 
5 2
6 5
6
2 5 3 1
1 5 2 3
5 6 5 6
6 3 4 1
6 2 3 4
2 2 4 5
*/