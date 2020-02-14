#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 100005;
const int MOD = 1000000007;

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

struct FEN
{
	int sum[MX];

	void add(int p, int x)
	{
		for(int i=p+1; i<MX; i+=i&-i) sum[i] += x, sum[i] %= MOD;
	}

	int qur(int p)
	{
		int ret = 0;
		for(int i=p+1; i; i-=i&-i) ret += sum[i], ret %= MOD;
		return ret;
	}
} F;

struct vec
{
	int x, y;

	vec (const ll &x0 = 0, const ll &y0 = 0) : x(x0), y(y0) {}
};

int n, m;
int ext[MX], rob[MX];
vec pot[MX];
vector<int> seq[MX];

void input()
{
	read(n), read(m);
	for(int i=1; i<=n; i++) read(rob[i]);
	for(int i=1; i<=m; i++) read(ext[i]);
}

void discrete()
{
	int tmp[MX];
	int num = 0;
	for(int i=1; i<=n; i++) tmp[++num] = pot[i].x;
	sort(tmp+1, tmp+num+1);
	num = unique(tmp+1, tmp+num+1) - tmp - 1;
	for(int i=1; i<=n; i++) pot[i].x = lower_bound(tmp+1, tmp+num+1, pot[i].x) - tmp;
	num = 0;
	for(int i=1; i<=n; i++) tmp[++num] = pot[i].y;
	sort(tmp+1, tmp+num+1);
	num = unique(tmp+1, tmp+num+1) - tmp - 1;
	for(int i=1; i<=n; i++) pot[i].y = lower_bound(tmp+1, tmp+num+1, pot[i].y) - tmp;
}

void work()
{
	int l = 1, r = n;
	while(l<=n && rob[l]<ext[1]) l++;
	while(r>=1 && rob[r]>ext[m]) r--;
	if(l > r) puts("1"), exit(0);
	else memmove(rob+1, rob+l, sizeof(int)*(r-l+1)), n = r-l+1;
	for(int i=1; i<=n; i++)
	{
		auto rt = upper_bound(ext+1, ext+m+1, rob[i]);
		auto lt = rt; lt--;
		pot[i] = vec(rob[i]-*lt, *rt-rob[i]);
	}
	discrete();
	for(int i=1; i<=n; i++) seq[pot[i].x].push_back(pot[i].y);
	for(int i=1; i<=n; i++)
	{
		sort(seq[i].begin(), seq[i].end());
		seq[i].erase(unique(seq[i].begin(), seq[i].end()), seq[i].end());
	}
	F.add(0, 1);
	for(int i=1; i<=n; i++)
		for(int j=seq[i].size()-1; j>=0; j--)
			F.add(seq[i][j], F.qur(seq[i][j]-1));
	printf("%d\n", F.qur(n));
}

int main()
{
	input();
	work();
	return 0;
}
