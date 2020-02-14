#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define MX 17
#define MOD 1000000007
#define mov(x) (1<<(x))

using namespace std;

typedef long long ll;

template <typename T> void read(T& x)
{
	x = 0; char c = getchar(); bool f = 0;
	while(!isdigit(c) && c!='-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(isdigit(c)) x = x*10+c-'0', c = getchar();
	if(f) x = -x;
}

template <typename T> void add(T& x, const T &y)
{
	x += y;
	if(x >= MOD) x %= MOD;
}

template <typename T> void mns(T& x, const T &y)
{
	x = ((x-y)%MOD + MOD) % MOD;
}

int N, M, A[MX];
ll f[MX][mov(MX)];
ll fac[mov(MX)], faci[mov(MX)];

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

ll C(int n, int m)
{
	if(n<0 || m<0 || m>n) return 0;
	else return fac[n] * faci[m] % MOD * faci[n-m] % MOD;
}

void init()
{
	fac[0] = 1;
	for(int i=1; i<mov(MX); i++) fac[i] = fac[i-1] * i % MOD;
	faci[mov(MX)-1] = inv(fac[mov(MX)-1]);
	for(int i=mov(MX)-1; i>=1; i--) faci[i-1] = faci[i] * i % MOD;
}

int main()
{
	read(N); read(M);
	init();
	for(int i=1; i<=M; i++) read(A[i]);
	sort(A+1, A+M+1, greater<int>());
	f[0][0] = 1;
	for(int i=1; i<=M; i++)
		for(int s=0; s<mov(N); s++)
		{
			add(f[i][s], f[i-1][s]);
			for(int j=0; j<N; j++)
				if(!(s&mov(j)))
					add(f[i][s|mov(j)], f[i-1][s] * C(mov(N)-A[i]-s, mov(j)-1) % MOD * fac[mov(j)]);
		}
	ll ans = 0;
	for(int s=0; s<mov(N); s++)
	{
		//cout<<s<<" "<<f[M][s]*fac[mov(N)-1-s]<<endl;
		if(__builtin_popcount(s) & 1) mns(ans, f[M][s] * fac[mov(N)-1-s]);
		else add(ans, f[M][s] * fac[mov(N)-1-s]);
	}
	printf("%lld\n", ans * mov(N) % MOD);
	return 0;
}
