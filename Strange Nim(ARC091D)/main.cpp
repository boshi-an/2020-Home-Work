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

int g(int x, int k)
{
	if(x%k == 0) return x/k;
	else if(x < k) return 0;
	else return g(x-(x/k+1)*((x%k-1)/(x/k+1)+1), k);
}

int main()
{
	int n, a, k, xo = 0;
	read(n);
	for(int i=1; i<=n; i++)
	{
		read(a), read(k);
		xo ^= g(a, k);
	}
	puts((xo==0) ? "Aoki" : "Takahashi");
	return 0;
}