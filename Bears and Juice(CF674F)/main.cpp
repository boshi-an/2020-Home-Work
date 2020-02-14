#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;

const int MX = 135;

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

int n, p, q;
uint up[MX], dn[MX], c[MX];

int main()
{
	read(n), read(p), read(q);
	c[0] = 1;
	for(int i=1; i<=p; i++)
	{
		up[i] = n+1-i;
		dn[i] = i;
		for(int j=1; j<=i; j++)
		{
			uint g = __gcd(up[j], dn[i]);
			up[j] /= g, dn[i] /= g;
		}
		c[i] = 1;
		for(int j=1; j<=i; j++) c[i] *= up[j];
	}
	uint sum = 0;
	for(int i=1; i<=q; i++)
	{
		uint ans = 0, d = 1;
		for(int j=0; j<n&&j<=p; j++) ans += c[j]*d, d *= i;
		sum ^= ans*i;
	}
	printf("%u\n", sum);
	return 0;
}