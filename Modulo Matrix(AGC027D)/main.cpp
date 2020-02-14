#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 505;
const int MP = 100005;

int n, pnum;
ll x[MX][MX], prm[MP];
bool vis[MP];

ll lcm(ll x, ll y)
{
	return x*y/__gcd(x, y);
}

void sieve()
{
	prm[0] = 1;
	for(int i=2; i<MP; i++)
	{
		if(!vis[i]) prm[++pnum] = i;
		for(int j=1; j<=pnum; j++)
		{
			if(prm[j]*i >= MP) break;
			vis[prm[j]*i] = 1;
			if(i%prm[j] == 0) break;
		}
	}
}

int main()
{
	sieve();
	scanf("%d", &n);
	for(int i=0; i<=n+1; i++) x[i][0] = x[i][n+1] = x[0][i] = x[n+1][i] = 1;
	int t = 0;
	for(int i=0; i<=n+1; i++)
		for(int j=0; j<=n+1; j++)
			if((i&1) == (j&1))
				x[i][j] = prm[(i+j)/2] * prm[(i-j)/2+n+5+(n+1)/2];
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			if(!x[i][j])
				x[i][j] = x[i-1][j] * x[i+1][j] + 1;
	ll mxv = 0;
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=n; j++)
			printf("%lld ", x[i][j]), mxv = max(mxv, x[i][j]);
		putchar('\n');
	}
	return 0;
}
