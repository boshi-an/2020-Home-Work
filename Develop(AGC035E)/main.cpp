#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 155;

ll work_odd(int n, int k, ll mod)
{
	auto add = [=](ll &x, const ll &y){x = (x+y) % mod;};
	static ll f[2][MX][MX];
	int now = 0;
	memset(f[now], 0, sizeof(f[now]));
	f[now][0][0] = 1;
	for(int i=2-k; i<=n+2; i+=2)
	{
		int l = i, r = i+k;
		memset(f[now^1], 0, sizeof(f[now^1]));
		//l=0, r=0:
		for(int a=0; a<=k+1; a++)
			for(int b=0; b<=n; b++)
				add(f[now^1][0][0], f[now][a][b]);

		//l=1, r=0:
		if(1<=l && l<=n)
			for(int a=0; a<k+1; a++)
				for(int b=0; b<=n; b++)
					add(f[now^1][a+(a>0)][0], f[now][a][b]);
		
		//l=0, r=1:
		if(r <= n)
			for(int a=0; a<=k+1; a++)
				for(int b=0; b<=n; b++)
					add(f[now^1][0][b+1], f[now][a][b]);
		
		//l=1, r=1:
		if(1<=l && l<=n && r<=n)
			for(int a=0; a+1<=k+1; a++)
				for(int b=0; b+2<=k+1; b++)
					add(f[now^1][max(a+1, b+2)][b+1], f[now][a][b]);
		
		now ^= 1;
	}
	return f[now][0][0];
}

ll work_even(int n, int k, ll mod)
{
	auto add = [=](ll &x, const ll &y){x = (x+y) % mod;};
	static ll f[MX][MX];
	memset(f, 0, sizeof(f));
	f[0][0] = 1;
	for(int i=1; i<=n+1; i++)
	{
		for(int j=0; j<=k; j++) add(f[i][0], f[i-1][j]);
		for(int j=1; j<=k; j++) add(f[i][j], f[i-1][j-1]);
	}
	return f[n+1][0];
}

int main()
{
	int n, k;
	ll mod;
	scanf("%d%d%lld", &n, &k, &mod);
	if(k&1) printf("%lld\n", work_odd(n, k, mod));
	else printf("%lld\n", work_even(n/2, k/2, mod) * work_even(n-n/2, k/2, mod) % mod);
	return 0;
}