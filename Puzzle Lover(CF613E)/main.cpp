#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 2005;
const ll MOD = 1000000007;
const ll P1 = 998244353;
const ll P2 = 1000000009;
const ll R = 1331;

void add(ll &x, const ll &y)
{
	x = (x+y) % MOD;
}

char str[2][MX], tar[MX];
int n, m;

void input()
{
	scanf("%s", str[0]+1);
	scanf("%s", str[1]+1);
	scanf("%s", tar+1);
	n = strlen(str[0]+1);
	m = strlen(tar+1);
}

ll *pwr, base[MX*4];

ll qpow(ll x, ll t, ll p)
{
	ll ret = 1;
	while(t)
	{
		if(t & 1) ret = ret * x % p;
		x = x * x % p;
		t >>= 1;
	}
	return ret;
}

ll inv(ll x, ll p)
{
	return qpow(x, p-2, p);
}

void init()
{
	pwr = base+MX*2;
	pwr[0] = 1;
	for(int i=1; i<MX*2; i++) pwr[i] = pwr[i-1] * R % P1;
	ll iv = inv(R, P1);
	for(int i=-1; i>-MX*2; i--) pwr[i] = pwr[i+1] * iv % P1;
}

ll ans;
ll pre_hash[MX], suf_hash[MX];
ll fwd[2][MX], bcw[2][MX];
ll lft[2][MX][MX], tmp[2][MX][MX], rgt[2][MX][MX];

void work()
{
	memset(lft, 0, sizeof(lft));
	memset(rgt, 0, sizeof(rgt));
	ll h = 0;
	for(int i=1; i<=m; i++)
	{
		h = (h*R + tar[i]) % P1;
		pre_hash[i] = h;
	}
	ll g = 0;
	for(int i=m; i>=1; i--)
	{
		g = (g*R + tar[i]) % P1;
		suf_hash[m-i+1] = g;
	}
	for(int i=1; i<=n; i++)
	{
		fwd[0][i] = (fwd[0][i-1] + pwr[i]*str[0][i]) % P1;
		fwd[1][i] = (fwd[1][i-1] + pwr[i]*str[1][i]) % P1;
		bcw[0][i] = (bcw[0][i-1] + pwr[-i]*str[0][i]) % P1;
		bcw[1][i] = (bcw[1][i-1] + pwr[-i]*str[1][i]) % P1;
	}
	for(int i=0; i<=n; i++)
	{
		for(int j=4; j<=m; j+=2)
		{
			if(j > i*2) break;
			ll h0 = ((fwd[0][i]-fwd[0][i-j/2]+P1)*pwr[j-1-i] + (bcw[1][i]-bcw[1][i-j/2]+P1)*pwr[i]) % P1;
			ll h1 = ((fwd[1][i]-fwd[1][i-j/2]+P1)*pwr[j-1-i] + (bcw[0][i]-bcw[0][i-j/2]+P1)*pwr[i]) % P1;
			if(h0 == pre_hash[j]) lft[1][i][j] = 1;
			if(h1 == pre_hash[j]) lft[0][i][j] = 1;
		}
	}
	for(int i=1; i<=n+1; i++)
	{
		for(int j=4; j<=m; j+=2)
		{
			if(j > (n-i+1)*2) break;
			ll h0 = ((fwd[0][i+j/2-1]-fwd[0][i-1]+P1)*pwr[-i] + (bcw[1][i+j/2-1]-bcw[1][i-1]+P1)*pwr[i+j-1]) % P1;
			ll h1 = ((fwd[1][i+j/2-1]-fwd[1][i-1]+P1)*pwr[-i] + (bcw[0][i+j/2-1]-bcw[0][i-1]+P1)*pwr[i+j-1]) % P1;
			if(h0 == suf_hash[j]) rgt[0][i][j] = 1;
			if(h1 == suf_hash[j]) rgt[1][i][j] = 1;
		}
	}
	memmove(tmp, lft, sizeof(tmp));
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=m; j++)
		{
			if(str[0][i] == tar[j])
			{
				if(j == 1) tmp[0][i][j] = 1;
				add(tmp[0][i][j], tmp[0][i-1][j-1]);
				if(j>=2 && str[1][i]==tar[j-1])
				{
					if(j == 2) add(tmp[0][i][j], 1);
					add(tmp[0][i][j], tmp[1][i-1][j-2]);
				}
			}
			if(str[1][i] == tar[j])
			{
				if(j == 1) tmp[1][i][j] = 1;
				add(tmp[1][i][j], tmp[1][i-1][j-1]);
				if(j>=2 && str[0][i]==tar[j-1])
				{
					if(j == 2) add(tmp[1][i][j], 1);
					add(tmp[1][i][j], tmp[0][i-1][j-2]);
				}
			}
		}
	}
	for(int i=0; i<=n; i++)
	{
		for(int j=0; j<=m; j++)
		{
			add(ans, tmp[0][i][j]*rgt[0][i+1][m-j]);
			add(ans, tmp[1][i][j]*rgt[1][i+1][m-j]);
		}
		add(ans, tmp[0][i][m]);
		add(ans, tmp[1][i][m]);
		add(ans, rgt[0][i][m]);
		add(ans, rgt[1][i][m]);
	}
}

bool pal()
{
	for(int i=1; i<=m; i++)
		if(tar[i] != tar[m-i+1])
			return false;
	return true;
}

int main()
{
	init();
	input();
	work();
	if(m >= 2)
	{
		reverse(tar+1, tar+m+1);
		work();
		for(int i=1; i<=n; i++) ans = (ans + MOD*4 - (lft[0][i][m]+lft[1][i][m]+rgt[0][i][m]+rgt[1][i][m])) % MOD;
	}
	if(m == 2)
	{
		for(int i=1; i<=n; i++)
		{
			if(str[0][i]==tar[1] && str[1][i]==tar[2]) ans = (ans + MOD - 1) % MOD;
			if(str[1][i]==tar[1] && str[0][i]==tar[2]) ans = (ans + MOD - 1) % MOD;
		}
	}
	printf("%lld\n", ans);
	return 0;
}