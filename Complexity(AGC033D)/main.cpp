#include <bits/stdc++.h>

using namespace std;

const int MX = 190;

int n, m;
char mp[MX][MX];
int f[MX][MX][MX], g[MX][MX][MX];
int sum[2][MX][MX];

void cmax(int &a, const int &b)
{
	if(b > a) a = b;
}

void input()
{
	scanf("%d%d", &n, &m);
	for(int i=1; i<=n; i++) scanf("%s", mp[i]+1);
}

void work()
{
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
		{
			sum[0][i][j] = sum[0][i][j-1] + (mp[i][j]=='.');
			sum[1][i][j] = sum[1][i][j-1] + (mp[i][j]=='#');
		}
	for(int i=n; i>=1; i--)
		for(int j=1; j<=m; j++)
			for(int k=j; k<=m; k++)
				for(int c=0; c<2; c++)
					if(sum[c][i][k]-sum[c][i][j-1]==k-j+1)
					{
						if(sum[c][i+1][k]-sum[c][i+1][j-1]==k-j+1) cmax(f[i][j][k], f[i+1][j][k]+1);
						else cmax(f[i][j][k], 1);
					}
	if(f[1][1][m] == n)
	{
		printf("%d\n", 0);
		return;
	}
	for(int r=1; r<=15; r++)
	{
		for(int i=1; i<=n; i++)
			for(int j=1; j<=m; j++)
				for(int k=j; k<=m; k++)
					cmax(g[j][i][i+f[i][j][k]-1], k-j+1);
		for(int i=1; i<=n; i++)
			for(int j=1; j<=m; j++)
				for(int k=m; k>=j; k--)
					cmax(f[i][j][k], f[i][j][k+1]);
		for(int i=1; i<=m; i++)
			for(int j=1; j<=n; j++)
				for(int k=n; k>=j; k--)
					cmax(g[i][j][k], g[i][j][k+1]);
		for(int i=1; i<=n; i++)
			for(int j=1; j<=m; j++)
				for(int k=1; k<=m; k++)
					cmax(f[i][j][k], f[i][j][k]+f[i+f[i][j][k]][j][k]);
		for(int i=1; i<=m; i++)
			for(int j=1; j<=n; j++)
				for(int k=1; k<=n; k++)
					cmax(g[i][j][k], g[i][j][k]+g[i+g[i][j][k]][j][k]);
		for(int i=1; i<=m; i++)
			for(int j=1; j<=n; j++)
				for(int k=j; k<=n; k++)
					cmax(f[j][i][i+g[i][j][k]-1], k-j+1);
		if(f[1][1][m] == n)
		{
			printf("%d\n", r);
			return;
		}
	}
	printf("16\n");
}

int main()
{
	input();
	work();
	return 0;
}