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

const int MX = 100005;
const int oo = 1000000000;

struct NUM
{
	ll u, d;

	NUM (const ll &u0 = 0, const ll &d0 = 1) : u(u0), d(d0) {}
	NUM norm () const {ll g = abs(__gcd(u, d)); if(d < 0) return NUM(-u/g, -d/g); return NUM(u/g, d/g);}
	NUM operator + (const NUM &rh) const {return NUM(u*rh.d+d*rh.u, d*rh.d).norm();}
	NUM operator - (const NUM &rh) const {return NUM(u*rh.d-d*rh.u, d*rh.d).norm();}
	NUM operator * (const NUM &rh) const {return NUM(u*rh.u, d*rh.d).norm();}
	NUM operator / (const NUM &rh) const {return NUM(u*rh.d, d*rh.u).norm();}
	bool operator < (const NUM &rh) const {return u*rh.d < d*rh.u;}
	bool operator <= (const NUM &rh) const {return u*rh.d <= d*rh.u;}
	bool operator == (const NUM &rh) const {return u*rh.d == d*rh.u;}
	bool operator != (const NUM &rh) const {return u*rh.d != d*rh.u;}
	double fp () const {return 1.0 * u / d;}
};

NUM operator - (const NUM &t) {return NUM(-t.u, t.d);}

NUM global_time;

struct OPR
{
	int f, id, p;
	NUM t, et, v;

	OPR (const int &f0 = 0, const int &i0 = 0, const int &p0 = 0, const NUM &t0 = NUM(), const NUM &et0 = NUM(), const NUM &v0 = NUM()) : f(f0), id(i0), p(p0), t(t0), et(et0), v(v0) {}
	bool operator < (const OPR &rh) const
	{
		NUM lhp = NUM(p) + (global_time-t)*v;
		NUM rhp = NUM(rh.p) + (global_time-rh.t)*rh.v;
		if(lhp == rhp) return id < rh.id;
		else return lhp < rhp;
	}
	NUM ct () const {return (f==+1) ? (t) : (et);}
};

int n, m;
int fst[MX], nxt[MX*2], v[MX*2], lnum;
int ui[MX], vi[MX], ti[MX], ci[MX];

void addeg(int nu, int nv)
{
	nxt[++lnum] = fst[nu];
	fst[nu] = lnum;
	v[lnum] = nv;
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

void cover(int s, int t, int id, NUM v, int t0)
{
	int ts = top[s], tt = top[t];
	NUM ds(t0, 1), dt = ds + NUM(dist(s, t))/v;
	while(ts != tt)
	{
		if(dep[ts] >= dep[tt])
		{
			NUM dur = NUM(dep[s]-dep[fa[ts]])/v;
			opr[ts].push_back(OPR(+1, id, dep[s], ds, ds+dur, -v));
			opr[ts].push_back(OPR(-1, id, dep[s], ds, ds+dur, -v));
			s = fa[ts];
			ts = top[s];
			ds = ds+dur;
		}
		else
		{
			NUM dur = NUM(dep[t]-dep[fa[tt]])/v;
			opr[tt].push_back(OPR(+1, id, dep[fa[tt]], dt-dur, dt, v));
			opr[tt].push_back(OPR(-1, id, dep[fa[tt]], dt-dur, dt, v));
			t = fa[tt];
			tt = top[t];
			dt = dt-dur;
		}
	}
	if(dep[s] >= dep[t])
	{
		NUM dur = NUM(dep[s]-dep[t])/v;
		opr[ts].push_back(OPR(+1, id, dep[s], ds, ds+dur, -v));
		opr[ts].push_back(OPR(-1, id, dep[s], ds, ds+dur, -v));
	}
	else
	{
		NUM dur = NUM(dep[t]-dep[s])/v;
		opr[tt].push_back(OPR(+1, id, dep[s], ds, ds+dur, v));
		opr[tt].push_back(OPR(-1, id, dep[s], ds, ds+dur, v));
	}
}

NUM ans(+oo, 0);

NUM intersect(OPR a, OPR b)
{
	if(a.v == b.v)
	{
		if(NUM(a.p)-a.v*a.t == NUM(b.p)-b.v*b.t)
		{
			NUM st = max(a.t, b.t), et = min(a.et, b.et);
			if(st <= et) return st;
			else return NUM(+oo);
		}
		else return NUM(+oo);
	}
	else
	{
		NUM l = (NUM(a.p)-a.v*a.t) - (NUM(b.p)-b.v*b.t);
		NUM r = b.v - a.v;
		NUM t = l / r;
		NUM st = max(a.t, b.t), et = min(a.et, b.et);
		if(st<=t && t<=et) return t;
		else return NUM(+oo);
	}
}

void calculate(vector<OPR> seq)
{
	set<OPR> st;
	sort(seq.begin(), seq.end(), [](const OPR &a, const OPR &b){return (a.ct()!=b.ct()) ? (a.ct()<b.ct()) : (a.f>b.f);});
	for(auto it : seq)
	{
		global_time = it.ct();
		if(ans <= global_time) return;
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
			auto mid = st.find(it);
			assert(mid != st.end());
			if(mid != st.begin())
			{
				auto lt = mid, rt = mid; lt--, rt++;
				if(rt != st.end()) cmin(ans, intersect(*lt, *rt));
			}
			st.erase(mid);
		}
	}
}

void work()
{
	dfs1(1, 0);
	dfs2(1, 1);
	for(int i=1; i<=m; i++) cover(ui[i], vi[i], i, NUM(ci[i]), ti[i]);
	for(int i=1; i<=n; i++) calculate(opr[i]);
	if(ans.fp() > +oo-10) puts("-1");
	else printf("%.8lf\n", ans.fp());
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