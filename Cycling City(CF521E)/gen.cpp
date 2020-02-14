#include <bits/stdc++.h>

using namespace std;

bool vis[1005][1005];

int main()
{
	srand(time(0));
	int n = 10 , m = 12;
	printf("%d %d\n", n, m);
	for(int i=1; i<=n; i++) vis[i][i] = i;
	for(int i=1; i<=m; i++)
	{
		int a = rand()%n+1, b = rand()%n+1;
		while(vis[a][b]) a = rand()%n+1, b = rand()%n+1;
		printf("%d %d\n", a, b);
		vis[a][b] = vis[b][a] = 1;
	}
	return 0;
}