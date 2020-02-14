#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ldb;

const ll M = 100000;

template <typename T> void read(T &x)
{
	x = 0; char c = getchar(); bool f = 0;
	while(!isdigit(c) && c!='-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(isdigit(c)) x = x*10+c-'0', c = getchar();
	if(f) x = -x;
}

struct vec
{
	ll x, y;
	vec (const ll &x0 = 0, const ll &y0 = 0) : x(x0), y(y0) {}
	vec operator + (const vec &t) const {return vec(x+t.x, y+t.y);}
	vec operator - (const vec &t) const {return vec(x-t.x, y-t.y);}
	bool operator < (const vec &t) const {return (x!=t.x) ? (x<t.x) : (y<t.y);}
	ldb len () const {return sqrt((ldb)(x*x + y*y));}
};

ll crs(const vec &a, const vec &b)
{
	return a.x*b.y - a.y*b.x;
}

ll dot(const vec &a, const vec &b)
{
	return a.x*b.x + a.y*b.y;
}

int n;
vector<vec> pos;

void input()
{
	read(n);
	for(int i=1; i<=n; i++)
	{
		ll x, y, v;
		read(x), read(y), read(v);
		if(x-v >= 0) pos.emplace_back(vec(x-v, y));
		else pos.emplace_back(vec(0ll, min(M, y+(v-x)))), pos.emplace_back(vec(0ll, max(0ll, y-(v-x))));
		if(x+v <= M) pos.emplace_back(vec(x+v, y));
		else pos.emplace_back(vec(M, min(M, y+(x+v-M)))), pos.emplace_back(vec(M, max(0ll, y-(x+v-M))));
		if(y-v >= 0) pos.emplace_back(vec(x, y-v));
		else pos.emplace_back(vec(min(M, x+(v-y)), 0ll)), pos.emplace_back(vec(max(0ll, x-(v-y)), 0ll));
		if(y+v <= M) pos.emplace_back(vec(x, y+v));
		else pos.emplace_back(vec(min(M, x+(y+v-M)), M)), pos.emplace_back(vec(max(0ll, x-(y+v-M)), M));
	}
}

vector<vec> convex(vector<vec> src)
{
	vector<vec> stk;
	sort(src.begin(), src.end());
	for(auto i=src.begin(); i!=src.end(); i++)
	{
		while(stk.size()>=2 && crs(stk.end()[-1]-stk.end()[-2], *i-stk.end()[-2])<=0) stk.pop_back();
		stk.emplace_back(*i);
	}
	int top = stk.size();
	for(auto i=src.rbegin()+1; i!=src.rend(); i++)
	{
		while(stk.size()>top && crs(stk.end()[-1]-stk.end()[-2], *i-stk.end()[-2])<=0) stk.pop_back();
		stk.emplace_back(*i);
	}
	stk.pop_back();
	return stk;
}

double get_cos_theta(vec a, vec b)
{
	return 1.0 * dot(a, b) / sqrt(dot(a, a)) / sqrt(dot(b, b));
}

void work()
{
	vector<vec> con = convex(pos);
	double max_rad = -M;
	vec ans_a, ans_b, ans_c;
	for(int i=0; i<con.size(); i++)
	{
		vec a = con[i], b = con[(i+1)%con.size()], c = con[(i+2)%con.size()];
		double sin_theta = crs(a-c, b-c) / (a-c).len() / (b-c).len();
		double r = (a-b).len() / 2 / sin_theta;
		if(r > max_rad) max_rad = r, ans_a = a, ans_b = b, ans_c = c;
	}
	printf("%lld %lld\n", ans_a.x, ans_a.y);
	printf("%lld %lld\n", ans_b.x, ans_b.y);
	printf("%lld %lld\n", ans_c.x, ans_c.y);
}

int main()
{
	input();
	work();
	return 0;
}