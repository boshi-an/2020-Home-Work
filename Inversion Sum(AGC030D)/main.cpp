#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 3003;
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

ll qpow(ll x, ll t)
{
	ll ans = 1;
	while(t)
	{
		if(t & 1) ans = ans * x % MOD;
		x = x * x % MOD;
		t >>= 1;
	}
	return ans;
}

ll inv(ll x)
{
	return qpow(x, MOD-2);
}

ll f[MX][MX], seq[MX], rak[MX];

int main()
{
	int n, q;
	read(n), read(q);
	for(int i=1; i<=n; i++) read(seq[i]);
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			if(seq[j] > seq[i])
				f[i][j] = 1;
	ll iv2 = inv(2);
	for(int i=1; i<=q; i++)
	{
		int x, y;
		read(x), read(y);
		if(x > y) swap(x, y);
		for(int j=1; j<=n; j++)
			if(j!=x && j!=y)
			{
				ll tmp = (f[j][x] + f[j][y]) * iv2 % MOD;
				f[j][x] = f[j][y] = tmp;
				tmp = (f[x][j] + f[y][j]) * iv2 % MOD;
				f[x][j] = f[y][j] = tmp;
			}
		ll tmp = (f[x][y] + f[y][x]) * iv2 % MOD;
		f[x][y] = f[y][x] = tmp;
	}
	ll ans = 0;
	for(int i=1; i<=n; i++)
		for(int j=1; j<i; j++)
			ans = (ans + f[i][j]) % MOD;
	printf("%lld\n", ans * qpow(2, q) % MOD);
	return 0;
}
