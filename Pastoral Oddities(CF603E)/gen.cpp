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

int main()
{
	srand(time(0));
	int n = 4, m = 5;
	printf("%d %d\n", n, m);
	for(int i=1; i<=m; i++)
	{
		int a = rand()%n+1, b = rand()%n+1;
		while(a == b) a = rand()%n+1, b = rand()%n+1;
		printf("%d %d %d\n", a, b, rand()%1000000000);
	}
	return 0;
}