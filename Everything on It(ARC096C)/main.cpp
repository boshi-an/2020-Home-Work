#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 3003;

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

int n;
ll mod;
ll S[MX][MX], C[MX][MX];
ll p22[MX], p2[MX*MX];

void work()
{
	S[0][0] = C[0][0] = 1;
	for(int i=1; i<=n+1; i++)
	{
		C[i][0] = 1;
		for(int j=1; j<=i; j++)
		{
			S[i][j] = (j*S[i-1][j] + S[i-1][j-1]) % mod;
			C[i][j] = (C[i-1][j] + C[i-1][j-1]) % mod;
		}
	}
	p2[0] = 1, p22[0] = 2;
	for(int i=1; i<=n; i++) p22[i] = p22[i-1]*p22[i-1] % mod;
	for(int i=1; i<=n*n; i++) p2[i] = p2[i-1]*2 % mod;
	ll ans = 0;
	for(int i=0; i<=n; i++)
	{
		ll coe = (i&1) ? (mod-C[n][i]) : (C[n][i]);
		for(int k=0; k<=i; k++)
		{
			ll con = S[i+1][k+1] * p2[(n-i)*k] % mod * p22[n-i] % mod;
			ans = (ans + coe*con) % mod;
		}
	}
	printf("%lld\n", ans);
}

int main()
{
	read(n), read(mod);
	work();
	return 0;
}