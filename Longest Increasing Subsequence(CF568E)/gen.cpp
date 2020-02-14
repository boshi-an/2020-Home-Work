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
	int sed;
	read(sed);
	srand(sed);
	int n = 100, m = 0;
	printf("%d\n", n);
	for(int i=1; i<=n; i++)
		if(rand() & 1) printf("%d ", rand()%1000+1);
		else printf("%d ", -1), m++;
	putchar('\n');
	m += rand()%n;
	printf("%d\n", m);
	for(int i=1; i<=m; i++) printf("%d ", rand()%1000+1);
	putchar('\n');
	return 0;
}
