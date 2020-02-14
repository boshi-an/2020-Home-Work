#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int MX = 100005;
const ll MOD = 1000000007;

template <typename T> void read(T &x)
{
	x = 0;
	char c = getchar();
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) x = x*10+c-'0', c = getchar();
}

template <typename T> void add(T &x, const T &y)
{
	x += y;
	x %= MOD;
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

int n, h[MX], rak[MX];
int lmost[MX], rmost[MX];
ll f[MX][2][2][2];
int hmn[MX];

void input()
{
	read(n);
	for(int i=1; i<=n; i++) read(h[i]), rak[i] = i;
	sort(rak+1, rak+n+1, [=](int a, int b){return h[a] > h[b];});
}

void trans(ll a[2][2][2], ll b[2][2][2], ll tar[2][2][2])
{
	ll f[2][2][2];
	memset(f, 0, sizeof(f));
	for(int l=0; l<2; l++)
		for(int ma=0; ma<2; ma++)
			for(int mb=0; mb<2; mb++)
				for(int r=0; r<2; r++)
					for(int ca=0; ca<2; ca++)
						for(int cb=0; cb<2; cb++)
							add(f[l][r][ca|cb|(ma==mb)], a[l][ma][ca]*b[mb][r][cb]);
	memmove(tar, f, sizeof(f));
}

void moveh(ll a[2][2][2], ll tar[2][2][2], int dh)
{
	ll f[2][2][2];
	memset(f, 0, sizeof(f));
	for(int l=0; l<2; l++)
		for(int r=0; r<2; r++)
		{
			if(dh)
			{
				add(f[l][r][0], a[l][r][0]*qpow(2, dh-1));
				add(f[l^1][r^1][0], a[l][r][0]*qpow(2, dh-1));
			}
			else add(f[l][r][0], a[l][r][0]);
			add(f[l^(dh&1)][r^(dh&1)][1], a[l][r][1]);
		}
	memmove(tar, f, sizeof(f));
}

void work()
{
	for(int i=1; i<=n; i++)
	{
		int p = rak[i];
		if(!lmost[p-1] && !rmost[p+1])
		{
			f[p][0][0][0] = 1;
			f[p][1][1][0] = 1;
			lmost[p] = rmost[p] = p;
			hmn[p] = h[p];
		}
		else if(!lmost[p-1] && rmost[p+1])
		{
			moveh(f[p+1], f[p+1], hmn[p+1]-h[p]);
			lmost[rmost[p+1]] = p;
			rmost[p] = rmost[p+1];
			hmn[p] = hmn[rmost[p+1]] = h[p];
			f[p][0][0][0] = 1;
			f[p][1][1][0] = 1;
			trans(f[p], f[p+1], f[p]);
			memmove(f[rmost[p+1]], f[p], sizeof(f[p]));
		}
		else if(lmost[p-1] && !rmost[p+1])
		{
			moveh(f[p-1], f[p-1], hmn[p-1]-h[p]);
			rmost[lmost[p-1]] = p;
			lmost[p] = lmost[p-1];
			hmn[p] = hmn[lmost[p-1]] = h[p];
			f[p][0][0][0] = 1;
			f[p][1][1][0] = 1;
			trans(f[p-1], f[p], f[p]);
			memmove(f[lmost[p-1]], f[p], sizeof(f[p]));
		}
		else
		{
			moveh(f[p-1], f[p-1], hmn[p-1]-h[p]);
			moveh(f[p+1], f[p+1], hmn[p+1]-h[p]);
			rmost[lmost[p-1]] = rmost[p+1];
			lmost[rmost[p+1]] = lmost[p-1];
			hmn[p] = hmn[lmost[p-1]] = hmn[rmost[p+1]] = h[p];
			f[p][0][0][0] = 1;
			f[p][1][1][0] = 1;
			trans(f[p-1], f[p], f[p]);
			trans(f[p], f[p+1], f[p+1]);
			memmove(f[lmost[p-1]], f[p+1], sizeof(f[p+1]));
			memmove(f[rmost[p+1]], f[p+1], sizeof(f[p+1]));
		}
	}
	moveh(f[1], f[1], hmn[1]-1);
	ll ans = 0;
	for(int i=0; i<2; i++)
		for(int j=0; j<2; j++)
			for(int k=0; k<2; k++)
				add(ans, f[1][i][j][k]);
	printf("%lld\n", ans);
}

int main()
{
	input();
	work();
	return 0;
}