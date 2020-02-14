#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 25005;
const int MK = 404;
const ll MOD = 1000000007;

template <typename T> void add(T &x, const T &y)
{
	x = (x+y) % MOD;
}

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

ll qpow(ll x, ll t)
{
	ll ret = 1;
	while(t)
	{
		if(t & 1) ret = ret*x % MOD;
		x = x*x % MOD;
		t >>= 1;
	}
	return ret;
}

int n, k, m;
int seq[MX];

void input()
{
	read(n), read(k), read(m);
	for(int i=1; i<=m; i++) read(seq[i]);
}

int pre[MX], lst[MX];
ll lft[MX], rgt[MX], f[2][MK], g[2][MK];

int count_illegal(int *s, ll *tar)
{
	bool flg = 0;
	for(int i=1; i<=k; i++) lst[i] = 0;
	int mx = 0;
	for(int i=1; i<=m; i++)
	{
		cmax(mx, pre[i] = lst[seq[i]]);
		lst[seq[i]] = i;
		if(i-mx == k) flg = 1;
	}
	int cur = 0;
	memset(f[cur], 0, sizeof(f[cur]));
	f[cur][m-mx] = 1;
	tar[0] = 1;
	for(int i=1; i<=n; i++)
	{
		cur ^= 1;
		ll sum = 0;
		for(int j=k-1; j>=1; j--)
		{
			add(sum, f[cur^1][j]);
			f[cur][j] = (sum + f[cur^1][j-1]*(k-j+1)) % MOD;
			add(tar[i], f[cur][j]);
		}
	}
	if(flg) return 1;
	else if(!mx) return -1;
	else return 0;
}

void work()
{
	int flg = count_illegal(seq, rgt);
	reverse(seq+1, seq+m+1);
	count_illegal(seq, lft);
	ll ans = qpow(k, n-m) * (n-m+1) % MOD;
	if(flg == 0) for(int i=0; i<=n-m; i++) add(ans, MOD*MOD - lft[i]*rgt[n-m-i]);
	else if(flg == -1)
	{
		ll con = 0;
		int cur = 0;
		memset(f[cur], 0, sizeof(f[cur]));
		f[cur][1] = k;
		g[cur][1] = (1>=m) * k;
		for(int i=2; i<=n; i++)
		{
			cur ^= 1;
			ll sumf = 0, sumg = 0;
			for(int j=k-1; j>=1; j--)
			{
				add(sumf, f[cur^1][j]);
				add(sumg, g[cur^1][j]);
				f[cur][j] = (sumf + f[cur^1][j-1]*(k-j+1)) % MOD;
				g[cur][j] = (sumg + g[cur^1][j-1]*(k-j+1)) % MOD;
				if(j >= m) add(g[cur][j], f[cur][j]);
			}
		}
		for(int j=1; j<k; j++) add(con, g[cur][j]);
		for(int i=k; i>k-m; i--) con = con * qpow(i, MOD-2) % MOD;
		ans = (ans - con + MOD) % MOD;
	}
	printf("%lld\n", ans);
}

int main()
{
	input();
	work();
	return 0;
}