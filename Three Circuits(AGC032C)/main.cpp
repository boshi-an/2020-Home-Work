#include <bits/stdc++.h>

using namespace std;

const int MX = 200002;

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

int deg[MX];
int fst[MX], nxt[MX], v[MX], lnum;
int n, m;

void addeg(int nu, int nv)
{
	nxt[++lnum] = fst[nu];
	fst[nu] = lnum;
	v[lnum] = nv;
	deg[nv]++;
}

void input()
{
	read(n), read(m);
	for(int i=1; i<=m; i++)
	{
		int nu, nv;
		read(nu), read(nv);
		addeg(nu, nv);
		addeg(nv, nu);
	}
}

void out_no()
{
	puts("No");
	exit(0);
}

void out_yes()
{
	puts("Yes");
	exit(0);
}

void check(int x, int y)
{
	queue<int> que;
	static int way[MX];
	memset(way, 0, sizeof(way));
	que.push(x);
	way[x] = 1;
	while(!que.empty())
	{
		int a = que.front();
		que.pop();
		if(a == y) continue;
		for(int i=fst[a]; i; i=nxt[i])
		{
			int b = v[i];
			if(!way[b]) que.push(b);
			way[b] += way[a];
		}
	}
	if(way[y] == 2) out_yes();
	else if(way[y] == 4) out_no();
	else assert(0);
}

void work()
{
	for(int i=1; i<=n; i++) if(deg[i]&1) out_no();
	for(int i=1; i<=n; i++) if(deg[i] >= 6) out_yes();
	vector<int> v4;
	for(int i=1; i<=n; i++) if(deg[i] == 4) v4.push_back(i);
	if(v4.size() <= 1) out_no();
	else if(v4.size() == 2) check(v4[0], v4[1]);
	else out_yes();
}

int main()
{
	input();
	work();
	return 0;
}