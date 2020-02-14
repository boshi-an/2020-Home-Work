#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 404;
const ll MOD = 998244353;

template <typename T> void add(T &x, const T &y)
{
	x = (x+y) % MOD;
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

ll fac[MX], faci[MX], ivx[MX];
ll f[2][MX][MX];
int A[MX], B[MX], sA[MX], sB[MX];
int n;

void init()
{
	fac[0] = 1;
	for(int i=1; i<MX; i++) fac[i] = fac[i-1] * i % MOD;
	faci[MX-1] = inv(fac[MX-1]);
	for(int i=MX-1; i>=1; i--) faci[i-1] = faci[i] * i % MOD;
	for(int i=1; i<MX; i++) ivx[i] = faci[i] * fac[i-1] % MOD;
}

void input()
{
	read(n);
	for(int i=1; i<=n; i++)
	{
		read(A[i]), sA[i] = sA[i-1] + A[i];
		read(B[i]), sB[i] = sB[i-1] + B[i];
	}
}

void print_coef(ll *s)
{
	for(int i=0; i<=4; i++) printf("%lld ", s[i]*fac[i]%MOD);
	putchar('\n');
}

void work()
{
	int now = 0;
	f[now][0][0] = MOD-1;
	for(int i=1; i<=n; i++)
	{
		memmove(f[now^1], f[now], sizeof(f[now^1]));
		for(int j=A[i]; j<=sA[i]; j++)
		{
			for(int b=0; b<=sB[i-1]; b++)
			{
				ll tmp = 1;
				for(int a=0; a<B[i]; a++)
				{
					add(f[now^1][j][a+b], MOD*MOD - f[now][j-A[i]][b]*tmp);
					tmp = tmp * ivx[a+1] % MOD * A[i] % MOD;
				}
			}
		}
		now ^= 1;
	}
	ll ans = 0;
	for(int i=1; i<=sA[n]; i++)
		for(int j=0; j<=sB[n]; j++)
			add(ans, f[now][i][j] * fac[j] % MOD * qpow(inv(i), j+1) % MOD);
	printf("%lld\n", ans * sA[n] % MOD);
}

int main()
{
	init();
	input();
	work();
	return 0;
}