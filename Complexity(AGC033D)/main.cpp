#include <bits/stdc++.h>

using namespace std;

const int MX = 186;

int n, m;
char mp[MX][MX];
int f[MX][MX][MX];
int sum0[MX][MX], sum1[MX][MX];

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
			sum0[i][j] = sum0[i][j-1] + (mp[i][j]=='.');
			sum0[i][j] = sum0[i][j-1] + (mp[i][j]=='#');
		}
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=m; j++)
		{
			for(int k=j; k<=m; k++)
			{
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