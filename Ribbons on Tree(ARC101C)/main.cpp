#include <bits/stdc++.h>

using namespace std;

const int MX = 5005;
const int MOD = 1000000007;

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

int n;
int fst[MX], nxt[MX*2], v[MX*2], lnum;

void addeg(int nu, int nv)
{
	nxt[++lnum] = fst[nu];
	fst[nu] = lnum;
	v[lnum] = nv;
}

void input()
{
	read(n);
	for(int i=1; i<n; i++)
	{
		int a, b;
		read(a), read(b);
		addeg(a, b);
		addeg(b, a);
	}
}

int way[MX], g[MX][MX], ng[MX];
int siz[MX];

void dfs(int x, int f)
{
	siz[x] = 1;
	g[x][1] = 1;
	for(int i=fst[x]; i; i=nxt[i])
	{
		int y = v[i];
		if(y == f) continue;
		dfs(y, x);
		memset(ng, 0, sizeof(ng));
		for(int a=0; a<=siz[y]; a++)
			for(int b=0; b<=siz[x]; b++)
				ng[a+b] = (ng[a+b] + 1ll*g[y][a]*g[x][b]) % MOD;
		memmove(g[x], ng, sizeof(ng));
		siz[x] += siz[y];
	}
	for(int i=0; i<=siz[x]; i++) g[x][0] = (g[x][0] - 1ll*g[x][i]*way[i] + 1ll*MOD*MOD) % MOD;
}

void work()
{
	way[0] = 1;
	for(int i=2; i<=n; i++) way[i] = 1ll * way[i-2] * (i-1) % MOD;
	dfs(1, 0);
	printf("%d\n", (MOD-g[1][0]) % MOD);
}

int main()
{
	input();
	work();
	return 0;
}