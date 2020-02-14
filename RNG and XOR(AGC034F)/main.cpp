#include <bits/stdc++.h>
#define mov(x) (1<<(x))

using namespace std;

typedef long long ll;

const ll MOD = 998244353;
const int MX = 262144;

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

void fwt(ll *f, int bit)
{
	for(int i=1; i<mov(bit); i<<=1)
		for(int j=0; j<mov(bit); j+=(i<<1))
			for(int k=0; k<i; k++)
			{
				ll x = f[j+k], y = f[j+k+i];
				f[j+k] = (x+y) % MOD;
				f[j+k+i] = (x-y+MOD) % MOD;
			}
}

int n;
ll p[MX], rgt[MX], lft[MX];

void input()
{
	read(n);
	for(int i=0; i<mov(n); i++) read(p[i]);
}

void work()
{
	ll sum_i = inv(accumulate(p, p+mov(n), 0));
	for_each(p, p+mov(n), [=](ll &x){x = x*sum_i%MOD;}), p[0] = (p[0]-1+MOD) % MOD;
	fill(rgt, rgt+mov(n), MOD-1), rgt[0] = mov(n)-1;
	fwt(rgt, n), fwt(p, n);
	for_each(p, p+mov(n), [=](ll &x){x = inv(x);});
	for(int i=0; i<mov(n); i++) lft[i] = rgt[i] * p[i] % MOD;
	fwt(lft, n);
	ll iv = inv(mov(n));
	for_each(lft, lft+mov(n), [=](ll &x){x = x*iv%MOD;});
	for_each(lft, lft+mov(n), [=](ll x){printf("%lld\n", (x-lft[0]+MOD)%MOD);});
}

int main()
{
	input();
	work();
	return 0;
}
