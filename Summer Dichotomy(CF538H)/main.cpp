#include <bits/stdc++.h>

using namespace std;

const int MX = 100005;
const int oo = 1000050505;

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

struct INTV
{
	int l, r;

	INTV (const int &l0 = 0, const int &r0 = 0) : l(l0), r(r0) {}
	bool in (int x) const {return l<=x && x<=r;}
	INTV operator & (const INTV &t) const {return INTV(max(l, t.l), min(r, t.r));}
};

struct OPRT
{
	int p, x, f;

	OPRT (const int &p0 = 0, const int &x0 = 0, const int &f0 = 0) : p(p0), x(x0), f(f0) {}
	bool operator < (const OPRT &t) const {return p < t.p;}
};

int tmin, tmax;
int n, m;
int li[MX], ri[MX];
int fst[MX], nxt[MX*2], v[MX*2], lnum;

void addeg(int nu, int nv)
{
	nxt[++lnum] = fst[nu];
	fst[nu] = lnum;
	v[lnum] = nv;
}

void input()
{
	read(tmin), read(tmax);
	read(n), read(m);
	for(int i=1; i<=n; i++) read(li[i]), read(ri[i]);
	for(int i=1; i<=m; i++)
	{
		int a, b;
		read(a), read(b);
		addeg(a, b);
		addeg(b, a);
	}
}

void fuck()
{
	printf("IMPOSSIBLE\n");
	exit(0);
}

int vis[MX];
int mxl[2], mnr[2];
pair<vector<int>, vector<int> > cur_sub_graph;
vector<pair<INTV, INTV> > grp;
vector<OPRT> event;
vector<pair<vector<int>, vector<int> > > sub_graph;

int dfs(int x, int c)
{
	if(vis[x] && vis[x]!=c) return false;
	if(vis[x]) return 1;
	vis[x] = c;
	for(int i=fst[x]; i; i=nxt[i])
		if(!dfs(v[i], -c))
			return false;
	if(c == 1) cmax(mxl[0], li[x]), cmin(mnr[0], ri[x]), cur_sub_graph.first.push_back(x);
	else cmax(mxl[1], li[x]), cmin(mnr[1], ri[x]), cur_sub_graph.second.push_back(x);
	return true;
}

INTV old_con[MX];
multiset<int> curl, curr;
int sum[MX], num0;
int assigned[MX];

INTV calc_contribution(pair<INTV, INTV> pr, int x)
{
	if(pr.first.in(x) && pr.second.in(x))
	{
		if(pr.first.r > pr.second.r) return pr.first;
		else return pr.second;
	}
	else if(pr.first.in(x) && !pr.second.in(x)) return pr.second;
	else if(!pr.first.in(x) && pr.second.in(x)) return pr.first;
	else return INTV(0, +oo);
}

bool check_availability(int l1, int r1, int l2, int r2)
{
	if(l1>=r1 || l2>=r2) return false;
	else if(l1+l2 > tmax) return false;
	else if((r1-1)+(r2-1) < tmin) return false;
	else return true;
}

void output_answer(int x, int y)
{
	for(int i=0; i<grp.size(); i++)
	{
		if(grp[i].first.in(x) && grp[i].second.in(y))
		{
			for(auto x : sub_graph[i].first) assigned[x] = 1;
			for(auto x : sub_graph[i].second) assigned[x] = 2;
		}
		else
		{
			for(auto x : sub_graph[i].first) assigned[x] = 2;
			for(auto x : sub_graph[i].second) assigned[x] = 1;
		}
	}
	puts("POSSIBLE");
	printf("%d %d\n", x, y);
	for(int i=1; i<=n; i++) printf("%d", assigned[i]);
}

void work()
{
	for(int i=1; i<=n; i++)
	{
		if(!vis[i])
		{
			mxl[0] = mxl[1] = 0, mnr[0] = mnr[1] = +oo;
			cur_sub_graph.first.clear();
			cur_sub_graph.second.clear();
			if(!dfs(i, +1)) fuck();
			if(mxl[0] > mnr[0]) fuck();
			if(mxl[1] > mnr[1]) fuck();
			event.push_back(OPRT(mxl[0], grp.size(), +1));
			event.push_back(OPRT(mnr[0]+1, grp.size(), -1));
			event.push_back(OPRT(mxl[1], grp.size(), +1));
			event.push_back(OPRT(mnr[1]+1, grp.size(), -1));
			grp.push_back(make_pair(INTV(mxl[0], mnr[0]), INTV(mxl[1], mnr[1])));
			sub_graph.push_back(cur_sub_graph);
		}
	}
	sort(event.begin(), event.end());
	for(int i=0; i<grp.size(); i++)
	{
		old_con[i] = calc_contribution(grp[i], -1);
		curl.insert(old_con[i].l), curr.insert(old_con[i].r);
	}
	num0 = grp.size();
	for(int i=0; i+1<event.size();)
	{
		int j = i;
		while(event[i].p==event[j].p && j+1<event.size()) j++;
		int l = event[i].p, r = event[j].p;
		for(int t=i; t<j; t++)
		{
			auto e = event[t];
			curl.erase(curl.find(old_con[e.x].l));
			curr.erase(curr.find(old_con[e.x].r));
			num0 -= (sum[e.x]==0);
			sum[e.x] += e.f;
			num0 += (sum[e.x]==0);
			old_con[e.x] = calc_contribution(grp[e.x], l);
			curl.insert(old_con[e.x].l);
			curr.insert(old_con[e.x].r);
		}
		int nl, nr;
		if(!num0 && check_availability(l, r, nl = *curl.rbegin(), nr = *curr.begin()+1))
		{
			if(l+nl < tmin) nl += min(tmin-(l+nl), nr-nl-1);
			if(l+nl < tmin) l += min(tmin-(l+nl), r-l-1);
			assert(l+nl >= tmin);
			assert(l+nl <= tmax);
			output_answer(l, nl);
			return;
		}
		i = j;
	}
	puts("IMPOSSIBLE");
}

int main()
{
	input();
	work();
	return 0;
}
