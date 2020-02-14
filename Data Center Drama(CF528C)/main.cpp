#include <bits/stdc++.h>

using namespace std;

const int MX = 600006;

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

int fst[MX], nxt[MX], u[MX], v[MX], deg[MX], lnum;
pair<int, int> edge[MX];
int n, m, top;

void addeg(int nu, int nv)
{
	nxt[++lnum] = fst[nu];
	fst[nu] = lnum;
	u[lnum] = nu;
	v[lnum] = nv;
	deg[nv]++;
}

void init()
{
	memset(fst, 0xff, sizeof(fst));
	lnum = -1;
}

void input()
{
	read(n), read(m);
	for(int i=1; i<=m; i++)
	{
		int a, b;
		read(a), read(b);
		addeg(a, b);
		addeg(b, a);
	}
}

bool vis[MX];

void dfs(int x)
{
	int &e = fst[x];
	while(~e)
	{
		int y = v[e], cur = e;
		e = nxt[e];
		if(vis[cur]) continue;
		else vis[cur] = vis[cur^1] = 1, dfs(y), edge[++top] = make_pair(x, y);
	}
}

void work()
{
	vector<int> odd;
	for(int i=1; i<=n; i++)
		if(deg[i] & 1)
			odd.push_back(i);
	for(int i=0; i<odd.size(); i+=2)
	{
		addeg(odd[i], odd[i+1]);
		addeg(odd[i+1], odd[i]);
	}
	while((lnum+1)%4) addeg(1, 1), addeg(1, 1);
	dfs(1);
	printf("%d\n", top);
	for(int i=1; i<=top; i+=2) swap(edge[i].first, edge[i].second);
	for(int i=1; i<=top; i++) printf("%d %d\n", edge[i].first, edge[i].second);
}

int main()
{
	init();
	input();
	work();
	return 0;
}
