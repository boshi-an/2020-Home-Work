#include <bits/stdc++.h>
#define mov(x) (1<<(x))

using namespace std;

typedef long long ll;

const int MX = 1005;

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

struct vec
{
	ll x, y;

	vec (const ll &x0 = 0, const ll &y0 = 0) : x(x0), y(y0) {}
	vec operator + (const vec &t) const {return vec(x+t.x, y+t.y);}
	vec operator - (const vec &t) const {return vec(x-t.x, y-t.y);}
};

ll dot(vec a, vec b)
{
	return a.x*b.x + a.y*b.y;
}

ll crs(vec a, vec b)
{
	return a.x*b.y - a.y*b.x;
}

int n, m;
vec pos[MX], mon[MX];
vector<int> onl[8][MX];

void input()
{
	read(n), read(m);
	for(int i=1; i<=n; i++) read(pos[i].x), read(pos[i].y);
	for(int i=1; i<=m; i++) read(mon[i].x), read(mon[i].y);
}

vector<int> get_online(vec a, vec b)
{
	vector<int> ret;
	for(int i=1; i<=m; i++)
		if(crs(mon[i]-a, b-a)==0 && dot(mon[i]-a, b-a)>0 && dot(mon[i]-b, a-b)>0)
			ret.push_back(i);
	return ret;
}

bool dfs(vector<int> need, vector<int> have)
{
	if(!need.size()) return true;
	sort(need.begin(), need.end());
	need.erase(unique(need.begin(), need.end()), need.end());
	if(need.size() > have.size()) return false;
	for(int t=0; t<need.size(); t++)
	{
		rotate(need.begin(), need.begin()+1, need.end());
		for(auto i : have)
		{
			vector<int> next = need, rema;
			next.pop_back();
			for(auto x : onl[i][need.back()]) next.push_back(x);
			for(auto x : have) if(x != i) rema.push_back(x);
			if(dfs(next, rema)) return true;
		}
	}
	return false;
}

void work()
{
	int ans = 0;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			onl[i][j] = get_online(pos[i], mon[j]);
	vector<int> have;
	for(int i=1; i<=n; i++) have.push_back(i);
	for(int i=1; i<=m; i++)
	{
		vector<int> need;
		need.push_back(i);
		ans += dfs(need, have);
	}
	printf("%d\n", ans);
}

int main()
{
	input();
	work();
	return 0;
}