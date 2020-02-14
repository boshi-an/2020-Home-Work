#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define MX 1005
#define oo 1e18
#define eps 1e-18

using namespace std;

int n;
double p[MX][MX];
double e[MX];
bool vis[MX];
double rem[MX], top[MX], bot[MX];

int main()
{
	scanf("%d", &n);
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			scanf("%lf", &p[i][j]), p[i][j] /= 100;
	for(int i=1; i<=n; i++) e[i] = +oo, rem[i] = 1, bot[i] = eps, top[i] = 1;
	e[n] = 0;
	for(int t=1; t<n; t++)
	{
		int mnp = 0;
		double mnv = +oo;
		for(int i=1; i<=n; i++)
			if(!vis[i] && e[i]<mnv)
				mnv = e[i], mnp = i;
		int x = mnp;
		vis[x] = 1;
		for(int y=1; y<=n; y++)
		{
			if(vis[y]) continue;
			double ne = (top[y] + rem[y]*p[y][x]*e[x]) / (bot[y] + rem[y]*p[y][x]);
			if(ne < e[y]) e[y] = ne, top[y] += rem[y]*p[y][x]*e[x], bot[y] += rem[y]*p[y][x], rem[y] = rem[y]*(1-p[y][x]);
		}
		if(vis[1]) break;
	}
	printf("%.8lf\n", e[1]);
	return 0;
}
