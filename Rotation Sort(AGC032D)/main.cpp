#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 5005;

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

int n, a, b;
int seq[MX];
ll f[MX];
int les[MX][MX], gre[MX][MX];

int main()
{
	read(n), read(a), read(b);
	for(int i=1; i<=n; i++) read(seq[i+1]);
	n += 2;
	seq[n] = n;
	seq[1] = 0;
	for(int i=1; i<=n; i++)
	{
		for(int l=1; l+i-1<=n; l++)
		{
			int r = l+i-1;
			les[l][r] = les[l][r-1] + (seq[r]<seq[l]);
			gre[l][r] = gre[l+1][r] + (seq[l]>seq[r]);
		}
	}
	memset(f, 0x3f, sizeof(f));
	f[1] = 0;
	for(int i=1; i<=n; i++)
		for(int j=1; j<i; j++)
			if(seq[j]<seq[i] && les[j][i]+gre[j][i]==i-j-1)
				cmin(f[i], f[j] + 1ll*les[j][i]*b + 1ll*gre[j][i]*a);
	printf("%lld\n", f[n]);
	return 0;
}