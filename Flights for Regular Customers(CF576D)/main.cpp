#include <bits/stdc++.h>

using namespace std;

const int MX = 155;
const int oo = 1000231231;

template<typename T> void cmin(T &x, const T &y)
{
	if(y < x) x = y;
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

struct EDGE
{
	int u, v, d;

	bool operator < (const EDGE &t) const {return d < t.d;}
};

int n, m;
EDGE e[MX];

struct MAT
{
	bool x[MX][MX];

	MAT () {memset(x, 0, sizeof(x));}

	MAT operator * (const MAT &t)
	{
		MAT ret;
		bitset<MX> row1[MX], col2[MX];
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++)
				row1[i][j] = x[i][j],
				col2[j][i] = t.x[i][j];
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++)
				ret.x[i][j] = (row1[i]&col2[j]).any();
		return ret;
	}
};

MAT qpow(MAT x, int t)
{
	MAT ret;
	for(int i=1; i<=n; i++) ret.x[i][i] = 1;
	while(t)
	{
		if(t & 1) ret = ret * x;
		x = x * x;
		t >>= 1;
	}
	return ret;
}

void input()
{
	read(n), read(m);
	for(int i=1; i<=m; i++) read(e[i].u), read(e[i].v), read(e[i].d);
	sort(e+1, e+m+1);
}

int dis[MX][MX];

void work()
{
	int cur_time = 0, ans = 2e9;
	MAT cur, grp;
	memset(dis, 0x3f, sizeof(dis));
	for(int i=1; i<=n; i++) cur.x[i][i] = 1, dis[i][i] = 0;
	if(e[1].d) puts("Impossible"), exit(0);
	for(int i=1; i<=m; i++)
	{
		cur_time = e[i].d;
		grp.x[e[i].u][e[i].v] = 1;
		for(int a=1; a<=n; a++)
			for(int b=1; b<=n; b++)
				if(dis[a][e[i].u]<+oo && dis[e[i].v][b]<+oo)
					cmin(dis[a][b], dis[a][e[i].u]+dis[e[i].v][b]+1);
		for(int a=1; a<=n; a++)
			if(cur.x[1][a] && dis[a][n]<+oo)
				cmin(ans, dis[a][n]+cur_time);
		if(i < m) cur = cur*qpow(grp, e[i+1].d-cur_time);
	}
	if(ans <= 1e9+n+1) printf("%d\n", ans);
	else puts("Impossible");
}

int main()
{
	input();
	work();
	return 0;
}