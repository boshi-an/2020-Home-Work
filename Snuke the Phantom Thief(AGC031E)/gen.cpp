#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

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

ll randx()
{
	return 1ll*rand()<<30 | rand();
}

int main()
{
	int sed;
	read(sed);
	srand(sed);
	int n = 80;
	int m = 320;
	printf("%d\n", n);
	for(int i=1; i<=n; i++) printf("%d %d %lld\n", rand()%100+1, rand()%100+1, randx()%1000000000000000+1);
	printf("%d\n", m);
	for(int i=1; i<=m; i++) printf("%c %d %d\n", "LRDU"[rand()%4], rand()%100+1, rand()%n+1);
	return 0;
}
