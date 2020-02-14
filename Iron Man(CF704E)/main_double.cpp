#include <bits/stdc++.h>

using namespace std;

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

typedef long long ll;
typedef long double ldb;

const int MX = 100005;
const int oo = 1000000000;

/*struct ldb
{
	ll u, d;

	ldb (const ll &u0 = 0, const ll &d0 = 1) : u(u0), d(d0) {}
	ldb norm () const {if(d < 0) return ldb(-u, -d); return *this;}
	ldb operator + (const ldb &rh) const {return ldb(u*rh.d+d*rh.u, d*rh.d);}
	ldb operator - (const ldb &rh) const {return ldb(u*rh.d-d*rh.u, d*rh.d);}
	ldb operator * (const ldb &rh) const {return ldb(u*rh.u, d*rh.d);}
	ldb operator / (const ldb &rh) const {return ldb(u*rh.d, d*rh.u).norm();}
	bool operator < (const ldb &rh) const {return (long ldb)u*rh.d < (long ldb)d*rh.u;}
	bool operator <= (const ldb &rh) const {return (long ldb)u*rh.d <= (long ldb)d*rh.u;}
	bool operator == (const ldb &rh) const {return u*rh.d == d*rh.u;}
	bool operator != (const ldb &rh) const {return u*rh.d != d*rh.u;}
	ldb fp () const {return 1.0 * u / d;}
};*/

//ldb operator - (const ldb &t) {return ldb(-t.u, t.d);}

struct OPR
{
	int f, id, p;
	ldb t, et, v;

	OPR (const int &f0 = 0, const int &i0 = 0, const int &p0 = 0, const ldb &t0 =0, const ldb &et0 = 0, const ldb &v0 = 0) : f(f0), id(i0), p(p0), t(t0), et(et0), v(v0) {}
	bool operator < (const OPR &rh) const {return (p!=rh.p) ? (p<rh.p) : (id<rh.id);}
};

int n, m;
int fst[MX], nxt[MX*2], v[MX*2], lldb;
int ui[MX], vi[MX], ti[MX], ci[MX];

void addeg(int nu, int nv)
{
	nxt[++lldb] = fst[nu];
	fst[nu] = lldb;
	v[lldb] = nv;
}

int siz[MX], son[MX], fa[MX], top[MX], dep[MX], dfn[MX], dfc;
vector<OPR> opr[MX];

void dfs1(int x, int f)
{
	fa[x] = f, siz[x] = 1, dep[x] = dep[f]+1;
	for(int i=fst[x]; i; i=nxt[i])
	{
		int y = v[i];
		if(y != f)
		{
			dfs1(y, x);
			siz[x] += siz[y];
			if(siz[y] > siz[son[x]]) son[x] = y;
		}
	}
}

void dfs2(int x, int t)
{
	top[x] = t, dfn[x] = ++dfc;
	if(son[x]) dfs2(son[x], t);
	for(int i=fst[x]; i; i=nxt[i])
		if(v[i]!=fa[x] && v[i]!=son[x])
			dfs2(v[i], v[i]);
}

void input()
{
	read(n), read(m);
	for(int i=1; i<n; i++)
	{
		int a, b;
		read(a), read(b);
		addeg(a, b);
		addeg(b, a);
	}
	for(int i=1; i<=m; i++) read(ti[i]), read(ci[i]), read(ui[i]), read(vi[i]);
}

int dist(int s, int t)
{
	int ret = 0, ts = top[s], tt = top[t];
	while(ts != tt)
	{
		if(dep[ts] < dep[tt]) swap(ts, tt), swap(s, t);
		ret += dep[s];
		s = fa[ts];
		ts = top[s];
		ret -= dep[s];
	}
	return ret + abs(dep[s] - dep[t]);
}

void cover(int s, int t, int id, ldb v, int t0)
{
	int ts = top[s], tt = top[t];
	ldb ds = t0, dt = ds + dist(s, t)/v;
	while(ts != tt)
	{
		if(dep[ts] >= dep[tt])
		{
			ldb dur = ldb(dep[s]-dep[fa[ts]])/v;
			opr[ts].push_back(OPR(+1, id, dep[s], ds, ds+dur, -v));
			opr[ts].push_back(OPR(-1, id, dep[s], ds+dur, ds+dur, -v));
			s = fa[ts];
			ts = top[s];
			ds = ds+dur;
		}
		else
		{
			ldb dur = ldb(dep[t]-dep[fa[tt]])/v;
			opr[tt].push_back(OPR(+1, id, dep[fa[tt]], dt-dur, dt, v));
			opr[tt].push_back(OPR(-1, id, dep[fa[tt]], dt, dt, v));
			t = fa[tt];
			tt = top[t];
			dt = dt+dur;
		}
	}
	if(dep[s] >= dep[t])
	{
		ldb dur = ldb(dep[s]-dep[t])/v;
		opr[ts].push_back(OPR(+1, id, dep[s], ds, ds+dur, -v));
		opr[ts].push_back(OPR(-1, id, dep[s], ds+dur, ds+dur, -v));
	}
	else
	{
		ldb dur = ldb(dep[t]-dep[s])/v;
		opr[tt].push_back(OPR(+1, id, dep[s], ds, ds+dur, v));
		opr[tt].push_back(OPR(-1, id, dep[s], ds+dur, ds+dur, v));
	}
}

ldb ans = +oo;

ldb intersect(OPR a, OPR b)
{
	if(a.v == b.v)
	{
		if(ldb(a.p)-a.v*a.t == ldb(b.p)-a.v*a.t)
		{
			ldb st = max(a.t, b.t), et = min(a.et, b.et);
			if(st <= et) return st;
			else return ldb(+oo);
		}
		else return ldb(+oo);
	}
	else
	{
		ldb l = (ldb(a.p)-a.v*a.t) - (ldb(b.p)-b.v*b.t);
		ldb r = b.v - a.v;
		ldb t = l / r;
		ldb st = max(a.t, b.t), et = min(a.et, b.et);
		if(st<=t && t<=et) return t;
		else return ldb(+oo);
	}
}

void calculate(vector<OPR> seq)
{
	set<OPR> st;
	sort(seq.begin(), seq.end(), [](const OPR &a, const OPR &b){return (a.t!=b.t) ? (a.t<b.t) : ((a.id!=b.id) ? (a.id<b.id) : (a.f<b.f));});
	for(auto it : seq)
	{
		auto rt = st.upper_bound(it);
		if(it.f == +1)
		{
			if(rt != st.begin())
			{
				auto lt = rt; lt--;
				cmin(ans, intersect(*lt, it));
			}
			if(rt != st.end()) cmin(ans, intersect(it, *rt));
			st.insert(it);
		}
		else
		{
			if(rt != st.begin())
			{
				auto lt = rt; lt--;
				if(rt != st.end()) cmin(ans, intersect(*lt, *rt));
			}
			st.erase(it);
		}
	}
}

void work()
{
	dfs1(1, 0);
	dfs2(1, 1);
	for(int i=1; i<=m; i++) cover(ui[i], vi[i], i, ci[i], ti[i]);
	for(int i=1; i<=n; i++) calculate(opr[i]);
	if(ans > +oo-10) puts("-1");
	else printf("%.8lf\n", (double)ans);
}

int main()
{
	input();
	work();
	return 0;
}

/*
2 2
1 2
1 1 2 1
1 2 1 2

6 2
1 2
2 3
3 4
4 5
5 6
1 1 6 1
2 6 5 1
*/