#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 500005;
const ll MOD = 998244353;

int n, m;
ll fac[MX], faci[MX], inv[MX], pwn[MX], pwm[MX];

void init()
{
	int x = max(n, m);
	fac[0] = faci[0] = inv[0] = inv[1] = pwn[0] = pwm[0] = 1;
	for(int i=1; i<=x; i++)
	{
		fac[i] = fac[i-1] * i % MOD;
		if(i > 1) inv[i] = (MOD*MOD-(MOD/i)*inv[MOD%i]) % MOD;
		faci[i] = faci[i-1] * inv[i] % MOD;
		pwn[i] = pwn[i-1] * (n+1) % MOD;
		pwm[i] = pwm[i-1] * (m+1) % MOD;
	}
}

void work()
{
	ll ans = 0;
	auto C = [=](int x, int y){return fac[x]*faci[y]%MOD*faci[x-y]%MOD;};
	for(int i=0; i<=min(n, m); i++)
	{
		ll coe = (i&1) ? (MOD-1) : (+1);
		ans = (ans + coe*C(n, i)%MOD*C(m, i)%MOD*pwn[m-i]%MOD*pwm[n-i]%MOD*fac[i]) % MOD;
	}
	printf("%lld\n", ans);
}

int main()
{
	scanf("%d%d", &n, &m);
	init();
	work();
	return 0;
}