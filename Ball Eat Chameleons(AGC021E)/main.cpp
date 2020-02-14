#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 998244353;
const int MX = 500005;

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

int n, k;
ll fac[MX+5], faci[MX+5];

ll qpow(ll x, ll t)
{
	ll ret = 1;
	while(t)
	{
		if(t & 1) ret = ret * x % MOD;
		x = x * x % MOD;
		t >>= 1;
	}
	return ret;
}

ll inv(ll x)
{
	return qpow(x, MOD-2);
}

void init()
{
	fac[0] = 1;
	for(int i=1; i<=MX; i++) fac[i] = fac[i-1] * i % MOD;
	faci[MX] = inv(fac[MX]);
	for(int i=MX; i>=1; i--) faci[i-1] = faci[i] * i % MOD;
}

ll C(int x, int y)
{
	if(x<0 || y<0 || y>x) return 0;
	return fac[x] * faci[y] % MOD * faci[x-y] % MOD;
}

void work()
{
	read(n), read(k);
	ll ans = 0;
	for(int i=(k+1)/2; i<=k; i++)
	{
		int r = i, b = k-i;
		int t = max(0, n-(r-b));
		if(t*2+(n-t) > k) continue;
		if(t == n) ans = (ans + C(k-1, r) - C(k-1, r+b-t+1) + MOD) % MOD;
		else ans = (ans + C(k, r) - C(k, r+b-t+1) + MOD) % MOD;
	}
	printf("%lld\n", ans);
}

int main()
{
	init();
	work();
	return 0;
}