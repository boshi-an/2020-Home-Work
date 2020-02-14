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
	int n = 10, m = 2;
	printf("%d %d\n", n, m);
	for(int i=1; i<n; i++) printf("%d %d\n", i+1, rand()%i+1);
	for(int i=1; i<=m; i++) printf("%d %d %d %d\n", rand()%n+1, rand()%n+1, rand()%n+1, rand()%n+1);
	return 0;
}
