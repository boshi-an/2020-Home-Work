#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 505;

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

int n;
int val[MX][MX];
ll neg[MX][MX], pos[MX][MX], f[MX][MX];

void input()
{
	read(n);
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<i; j++)
		{
			read(val[i][j]);
			pos[i][j] += val[i][j];
		}
		for(int j=i+1; j<=n; j++)
		{
			read(val[i][j]);
			neg[i][j] += val[i][j];
		}
	}
	for(int i=0; i<=n; i++)
		for(int j=1; j<=n; j++)
		{
			pos[i][j] += pos[i][j-1];
			neg[i][j] += neg[i][j-1];
		}
	for(int j=0; j<=n; j++)
		for(int i=1; i<=n; i++)
		{
			pos[i][j] += pos[i-1][j];
			neg[i][j] += neg[i-1][j];
		}
}

void work()
{
	memset(f, 0x3f, sizeof(f));
	for(int i=0; i<=n; i++) f[0][i] = neg[i][i];
	for(int i=0; i<=n; i++)
	{
		for(int j=i+1; j<=n; j++)
		{
			for(int k=j+1; k<=n; k++)
			{
				ll new_pos = pos[k][i] - pos[j][i];
				ll new_neg = neg[k][k] - neg[j][k] - neg[k][j] + neg[j][j];
				cmin(f[j][k], f[i][j] + new_pos + new_neg);
			}
		}
	}
	ll ans = 1e18;
	for(int i=0; i<=n; i++) cmin(ans, f[i][n]);
	printf("%lld\n", ans);
}

int main()
{
	input();
	work();
	return 0;
}
