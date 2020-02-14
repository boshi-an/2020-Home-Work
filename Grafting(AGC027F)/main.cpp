#include <bits/stdc++.h>

using namespace std;

const int MX = 55;

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

struct GRAPH
{
	vector<int> v[MX];
	bool e[MX][MX];
	int deg[MX];

	void deleg(int a, int b)
	{
		for(auto i=v[a].begin(); i!=v[a].end(); i++)
			if(*i == b)
			{
				v[a].erase(i);
				break;
			}
		e[a][b] = 0;
		deg[b]--;
	}

	void addeg(int a, int b)
	{
		v[a].push_back(b);
		e[a][b] = 1;
		deg[b]++;
	}

	void init()
	{
		memset(e, 0, sizeof(e));
		memset(deg, 0, sizeof(deg));
		for(int i=0; i<MX; i++) v[i].clear();
	}

	bool no_loop(int n)
	{
		int cnt = 0;
		vector<int> stk;
		for(int i=1; i<=n; i++)
			if(!deg[i])
				stk.push_back(i);
		while(!stk.empty())
		{
			int x = stk.back();
			cnt++;
			stk.pop_back();
			for(auto y : v[x])
				if(!(--deg[y]))
					stk.push_back(y);
		}
		return (cnt==n);
	}
} A, B, C;

int n;

void input()
{
	A.init();
	B.init();
	read(n);
	for(int i=1; i<n; i++)
	{
		int a, b;
		read(a), read(b);
		A.addeg(a, b);
		A.addeg(b, a);
	}
	for(int i=1; i<n; i++)
	{
		int a, b;
		read(a), read(b);
		B.addeg(a, b);
		B.addeg(b, a);
	}
}

bool fxd[MX];
int faa[MX], fab[MX];

void getfa(int x, int f, const GRAPH &g, int *fa)
{
	fa[x] = f;
	for(auto y : g.v[x])
		if(y != f)
			getfa(y, x, g, fa);
}

void dfs(int x, int f)
{
	fxd[x] = 1;
	for(auto y : A.v[x])
	{
		if(y == f) continue;
		if(B.e[x][y]) dfs(y, x);
	}
}

int calc(int root)
{
	memset(fxd, 0, sizeof(fxd));
	getfa(root, 0, A, faa);
	getfa(root, 0, B, fab);
	dfs(root, 0);
	C.init();
	int cnt = 0;
	for(int i=1; i<=n; i++)
	{
		if(!fxd[i]) cnt++;
		if(!fxd[i] && !fxd[faa[i]]) C.addeg(i, faa[i]);
		if(!fxd[i] && !fxd[fab[i]]) C.addeg(fab[i], i);
	}
	if(C.no_loop(n)) return cnt;
	else return n+1;
}

void work()
{
	int ans = n+1;
	for(int i=1; i<=n; i++) cmin(ans, calc(i));
	for(int i=1; i<=n; i++)
		if(A.deg[i] == 1)
			for(int j=1; j<=n; j++)
				if(i != j)
				{
					int f = *A.v[i].begin();
					if(f == j) continue;
					A.deleg(i, f);
					A.deleg(f, i);
					A.addeg(i, j);
					A.addeg(j, i);
					cmin(ans, calc(i)+1);
					A.deleg(i, j);
					A.deleg(j, i);
					A.addeg(i, f);
					A.addeg(f, i);
				}
	if(ans == n+1) puts("-1");
	else printf("%d\n", ans);
}

int main()
{
	int t;
	read(t);
	while(t--)
	{
		input();
		work();
	}
	return 0;
}
