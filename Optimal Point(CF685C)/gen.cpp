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
	int t = 1000, n = 2;
	printf("%d\n", t);
	for(int i=1; i<=t; i++)
	{
		printf("%d\n", n);
		for(int j=1; j<=n; j++) printf("%d %d %d\n", rand()%10, rand()%10, rand()%10);
	}
	return 0;
}