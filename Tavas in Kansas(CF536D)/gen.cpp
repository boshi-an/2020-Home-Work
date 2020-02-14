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

int main()
{
	srand(time(0));
	int n = 468, m = 467;
	printf("%d %d\n", n, m);
	printf("%d %d\n", 1, n);
	for(int i=1; i<=n; i++) printf("%d ", rand()%10000-5000); putchar('\n');
	for(int i=1; i<=m; i++) printf("%d %d %d\n", rand()%n+1, rand()%n+1, 1000000000);
	return 0;
}