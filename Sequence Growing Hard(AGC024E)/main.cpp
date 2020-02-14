#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 303;

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

int n, k;
ll mod;
ll f[MX][MX], g[MX][MX], c[MX][MX];

int main()
{
	read(n), read(k), read(mod);
	n++, k++;		//set 0 into consideration
	for(int i=0; i<=n; i++)
	{
		c[i][0] = 1;
		for(int j=1; j<=i; j++) c[i][j] = (c[i-1][j] + c[i-1][j-1]) % mod;
	}
	for(int i=1; i<=k; i++) f[1][i] = 1;
	for(int i=1; i<=k; i++) g[1][i] = k-i;
	for(int s=2; s<=n; s++)
	{
		for(int i=k; i>=1; i--)
		{
			for(int t=1; t<s; t++)
				f[s][i] = (f[s][i] + g[s-t][i]*f[t][i]%mod*c[s-2][t-1]) % mod;
			g[s][i] = (g[s][i+1] + f[s][i+1]) % mod;
		}
	}
	printf("%lld\n", f[n][1]);
	return 0;
}
