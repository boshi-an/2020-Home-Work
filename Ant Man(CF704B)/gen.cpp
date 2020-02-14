#include <bits/stdc++.h>

using namespace std;

int main()
{
	int sed;
	cin >> sed;
	srand(sed);
	int n = 100;
	printf("%d %d %d\n", n, rand()%n+1, rand()%n+1);
	int x = 1;
	for(int i=1; i<=n; i++) x += rand()%n+1, printf("%d ", x); putchar('\n');
	for(int i=1; i<=n; i++) printf("%d ", rand()%n+1); putchar('\n');
	for(int i=1; i<=n; i++) printf("%d ", rand()%n+1); putchar('\n');
	for(int i=1; i<=n; i++) printf("%d ", rand()%n+1); putchar('\n');
	for(int i=1; i<=n; i++) printf("%d ", rand()%n+1); putchar('\n');
	return 0;
}