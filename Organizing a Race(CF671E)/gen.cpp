#include <bits/stdc++.h>

using namespace std;

template<typename T> void cmax(T &x, const T &y)
{
	if(y > x) x = y;
}

template<typename T> void read(T &x)
{
	x = 0;
	char c = getchar();
	bool f = 0;
	while(!isdigit(c) && c!='-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(isdigit(c)) x = x*10+c-'0', c = getchar();
	if(f) x = -x;
}

int n = 10, k;

int main()
{
	int sed;
	read(sed);
	srand(sed);
	k = rand()%3;
	printf("%d %d\n", n, k);
	for(int i=1; i<n; i++) printf("%d ", rand()%3);
	putchar('\n');
	for(int i=1; i<=n; i++) printf("%d ", rand()%3);
	return 0;
}