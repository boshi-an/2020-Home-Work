#include <bits/stdc++.h>

using namespace std;

const int MX = 186;

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
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=m; j++)
		{
			for(int k=j; k<=m; k++)
			{
				for(int c=0; c<2; c++)
				{
					if(sum[c][i][k]-sum[c][i][j-1]==k-j+1)
					{
						if(sum[c][i+1][k]-sum[c][i+1][j-1]==k-j+1) f[i][j][k] = f[i+1][j][k]+1;
						else f[i][j][k] = 1;
					}
					else f[i][j][k] = 0;
				}
			}
		}
	}
	for(int r=1; r<=14; r++)
	{
		for(int i=1; i<=n; i++)
		{
			for(int j=1; j<=m; j++)
			{
				for(int k=j+1; k<=m; k++)
				{
					cmax(f[i][j][k], f[i][j][k]+f[i+f[i][j][k]][j][k]);
				}
			}
		}
		
	}
}

int main()
{
	input();
	work();
	return 0;
}