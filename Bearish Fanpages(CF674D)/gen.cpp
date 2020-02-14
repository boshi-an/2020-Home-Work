#include <bits/stdc++.h>

using namespace std;

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

const int MX = 100005;

int fa[MX];

int main()
{
	srand(time(0));
	int n = 10, m = 10;
	printf("%d %d\n", n, m);
	for(int i=1; i<=n; i++) printf("%d ", rand()); putchar('\n');
	for(int i=1; i<=n; i++)
	{
		int y = rand()%n+1;
		while(y==i || fa[y]==i) y = rand()%n+1;
		printf("%d ", y);
		fa[i] = y;
	}
	putchar('\n');
	for(int i=1; i<=m; i++)
	{
		if(rand()&1)
		{
			int x = rand()%n+1;
			int y = rand()%n+1;
			while(y==x || fa[y]==x || fa[x]==y) x = rand()%n+1, y = rand()%n+1;
			printf("%d %d %d\n", 1, x, y);
			fa[x] = y;
		}
		else printf("3\n");
	}
	return 0;
}