#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 1505;
const int MK = 100005;
const ll MOD = 1000000007;

template <typename T> void add(T &x, const T &y)
{
	x += y;
	if(x >= MOD) x %= MOD;
}

template <typename T> void mns(T &x, const T &y)
{
	x -= y;
	if(x < 0) x = (x+MOD*MOD) % MOD;
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

int n, m, k;
ll p, q;
ll g[MX], g1[MX][MX], g2[MX][MX];
ll pow_p[MK], pow_q[MK];
ll fac[MK], faci[MK];
ll prob[MX], sumprob[MX];

ll cal_prob(int len)
{
	if(len > m) return 0;
	else return pow_p[len] * pow_q[k-len] % MOD * fac[k] % MOD * faci[len] % MOD * faci[k-len] % MOD;
}

void init()
{
	pow_p[0] = pow_q[0] = 1;
	for(int i=1; i<=k; i++) pow_p[i] = pow_p[i-1]*p%MOD, pow_q[i] = pow_q[i-1]*q%MOD;
	fac[0] = 1;
	for(int i=1; i<=k; i++) fac[i] = fac[i-1] * i % MOD;
	faci[k] = inv(fac[k]);
	for(int i=k; i>=1; i--) faci[i-1] = faci[i] * i % MOD;
	for(int i=0; i<=m; i++) prob[i] = cal_prob(i);
	for(int i=0; i<=m; i++) sumprob[i] = (sumprob[i-1] + prob[i]) % MOD;
}

void work()
{
	g[0] = 1;
	g1[0][m] = 1;
	g2[0][1] = 1;
	for(int i=1; i<=n; i++)
	{
		for(int l=1; l<=m; l++)
		{
			add(g[i], g[i-1]*prob[l-1]%MOD*sumprob[m-l]);
			mns(g[i], g1[i-1][l-1]*prob[l-1]%MOD*sumprob[m-l]);
			mns(g[i], g2[i-1][l+1]*prob[m-l]%MOD*sumprob[l-1]);
		}
		ll pg1 = 0;
		for(int j=1; j<=m; j++)
		{
			add(pg1, prob[j-1]*g1[i-1][j-1]);
			add(g1[i][j], g1[i][j-1]);
			add(g1[i][j], sumprob[j-1]*prob[m-j]%MOD*g[i-1]);
			mns(g1[i][j], pg1*prob[m-j]);
			mns(g1[i][j], sumprob[j-1]*prob[m-j]%MOD*g2[i-1][j+1]);
		}
		ll pg2 = 0;
		for(int j=m; j>=1; j--)
		{
			add(pg2, prob[m-j]*g2[i-1][j+1]);
			add(g2[i][j], g2[i][j+1]);
			add(g2[i][j], sumprob[m-j]*prob[j-1]%MOD*g[i-1]);
			mns(g2[i][j], sumprob[m-j]*prob[j-1]%MOD*g1[i-1][j-1]);
			mns(g2[i][j], pg2*prob[j-1]);
		}
	}
	printf("%lld\n", g[n]);
}

int main()
{
	read(n), read(m);
	ll a, b;
	read(a), read(b);
	read(k);
	p = a*inv(b) % MOD;
	q = (1-p+MOD) % MOD;
	init();
	work();
	return 0;
}
