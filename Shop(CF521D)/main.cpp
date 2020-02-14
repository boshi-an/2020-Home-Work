#include <bits/stdc++.h>

using namespace std;

const int MX = 100005;

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

struct NODE
{
	double x;
	int id;
	int tp;
	int ps;

	NODE (const double &x0 = 0, const int &i0 = 0, const int &t0 = 0, const int &p0 = 0) : x(x0), id(i0), tp(t0), ps(p0) {}
	bool operator < (const NODE &t) const {return x > t.x;}
};

int k, n, m;
int ai[MX], ti[MX];
vector<NODE> mdf[MX], add[MX], mul[MX];
vector<NODE> opr;

void input()
{
	read(k), read(n), read(m);
	for(int i=1; i<=k; i++) read(ai[i]);
	for(int i=1; i<=n; i++)
	{
		int t, p, b;
		read(t), read(p), read(b);
		if(t == 1) mdf[p].push_back(NODE(b-ai[p], i, t, p));
		else if(t == 2) add[p].push_back(NODE(b, i, t, p));
		else mul[p].push_back(NODE(b, i, t, p));
	}
	for(int i=1; i<=k; i++)
		if(mdf[i].size())
			add[i].push_back(*min_element(mdf[i].begin(), mdf[i].end()));
}

void work()
{
	for(int i=1; i<=k; i++)
	{
		sort(add[i].begin(), add[i].end());
		sort(mul[i].begin(), mul[i].end());
		while(add[i].size() && add[i].back().x<0) add[i].pop_back();
		double cur_sum = ai[i];
		for(auto x : add[i])
		{
			opr.push_back(NODE(1.0+x.x/cur_sum, x.id, x.tp, x.ps));
			cur_sum += x.x;
		}
		for(auto x : mul[i]) opr.push_back(x);
	}
	sort(opr.begin(), opr.end());
	//for(auto a : opr) cout<<a.x<<" "<<a.id<<endl;
	auto p = opr.begin();
	while(p!=opr.end() && p->x>0) p++;
	cmin(m, (int)(p-opr.begin()));
	sort(opr.begin(), opr.begin()+m, [](NODE a, NODE b){return a.tp < b.tp;});
	printf("%d\n", m);
	for(int i=0; i<m; i++) printf("%d ", opr[i].id);
	putchar('\n');
}

int main()
{
	input();
	work();
	return 0;
}