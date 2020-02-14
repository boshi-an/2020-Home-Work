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
	int n = 2000, m = 2000;
	for(int i=0; i<n; i++) putchar((i&1)+'a'); putchar('\n');
	for(int i=0; i<n; i++) putchar(!(i&1)+'a'); putchar('\n');
	for(int i=0; i<m; i++) putchar((i&1)+'a'); putchar('\n');
	return 0;
}
