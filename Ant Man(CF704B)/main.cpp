#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 5005;

int n, s, e;
int x[MX], a[MX], b[MX], c[MX], d[MX];
ll f[MX][MX];

void read(int &x)
{
	x = 0; char c = getchar();
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) x = x*10+c-'0', c = getchar();
}

void cmin(ll &x, const ll &y)
{
	if(y < x) x = y;
}

void input()
{
	read(n), read(s), read(e);
	for(int i=1; i<=n; i++) read(x[i]);
	for(int i=1; i<=n; i++) read(a[i]);
	for(int i=1; i<=n; i++) read(b[i]);
	for(int i=1; i<=n; i++) read(c[i]);
	for(int i=1; i<=n; i++) read(d[i]);
}

ll work()
{
	if(s==n && e==1) return 1e18;
	memset(f, 0x3f, sizeof(f));
	if(s == 1) f[1][1] = d[1]-x[1];
	else f[1][2] = b[1]+d[1]-x[1]*2;
	for(int i=1; i<n; i++)
	{
		for(int j=1; j<=i*2&&j<=n; j++)
		{
			if(i+1 == n)
			{
				if(e == n) cmin(f[i+1][j-1], f[i][j]+x[i+1]+a[i+1]);
				else if(j >= 2) cmin(f[i+1][j-2], f[i][j]+x[i+1]*2+a[i+1]+c[i+1]);
			}
			else if(i+1 == s)
			{
				cmin(f[i+1][j-1], f[i][j]+x[i+1]+c[i+1]);
				cmin(f[i+1][j+1], f[i][j]-x[i+1]+d[i+1]);
			}
			else if(i+1 == e)
			{
				cmin(f[i+1][j+1], f[i][j]-x[i+1]+b[i+1]);
				cmin(f[i+1][j-1], f[i][j]+x[i+1]+a[i+1]);
			}
			else
			{
				if(j > 1)
				{
					cmin(f[i+1][j-2], f[i][j]+x[i+1]*2+c[i+1]+a[i+1]);
					cmin(f[i+1][j], f[i][j]+b[i+1]+c[i+1]);
				}
				cmin(f[i+1][j+2], f[i][j]-x[i+1]*2+b[i+1]+d[i+1]);
				cmin(f[i+1][j], f[i][j]+a[i+1]+d[i+1]);
			}
		}
	}
	return f[n][0];
}

int main()
{
	input();
	if(s > e)
	{
		swap(s, e);
		swap(d, b);
		swap(a, c);
	}
	printf("%lld\n", work());
	return 0;
}