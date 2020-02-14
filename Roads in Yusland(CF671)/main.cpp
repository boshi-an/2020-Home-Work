#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <cmath>
#define MX 300003

using namespace std;

typedef long long ll;

template <typename T> void read(T& x)
{
	x = 0; char c = getchar(); bool f = 0;
	while(!isdigit(c) && c!='-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(isdigit(c)) x = x*10+c-'0', c = getchar();
	if(f) x = -x;
}

struct OPER
{
	int id, f;
	
	OPER (const int &i0 = 0, const int &f0 = 0) : id(i0), f(f0) {}
};

struct NODE
{
	int x, add, ls, rs, d;
	
	void tag(int a) {x += a, add += a;}
} tre[MX];

void psd(int a)
{
	tre[tre[a].ls].tag(tre[a].add);
	tre[tre[a].rs].tag(tre[a].add);
	tre[a].add = 0;
}

int merge(int x, int y)
{
	if(!x || !y) return (x|y);
	psd(x), psd(y);
	if(tre[x].x > tre[y].x) swap(x, y);
	tre[x].ls = merge(tre[x].ls, y);
	if(tre[tre[x].ls].d > tre[tre[x].rs].d) swap(tre[x].ls, tre[x].rs);
	tre[x].d = tre[tre[x].ls].d + 1;
	return x;
}

void pop(int &x)
{
	psd(x);
	x = merge(tre[x].ls, tre[x].rs);
}

int n, m;
int fst[MX], nxt[MX*2], v[MX*2], lnum;
vector<OPER> opr[MX];

void addeg(int nu, int nv)
{
	nxt[++lnum] = fst[nu];
	fst[nu] = lnum;
	v[lnum] = nv;
}

void input()
{
	int a, b, c;
	read(n); read(m);
	for(int i=1; i<n; i++)
	{
		read(a); read(b);
		addeg(a, b);
		addeg(b, a);
	}
	for(int i=1; i<=m; i++)
	{
		read(a); read(b); read(c);
		opr[a].push_back(OPER(i, +1));
		opr[b].push_back(OPER(i, -1));
		tre[i].x = c;
	}
}

int rot[MX], del[MX];
ll ans;

void dfs(int x, int f)
{
	for(int i=fst[x]; i; i=nxt[i])
		if(v[i] !=f)
			dfs(v[i], x), rot[x] = merge(rot[x], rot[v[i]]);
	for(auto i : opr[x])
	{
		if(i.f == -1) del[i.id] = 1;
		else rot[x] = merge(rot[x], i.id);
	}
	while(del[rot[x]]) pop(rot[x]);
	if(x!=1 && !rot[x]) puts("-1"), exit(0);
	else
	{
		psd(rot[x]);
		if(x != 1) ans += tre[rot[x]].x;
		tre[rot[x]].tag(-tre[rot[x]].x);
	}
}

int main()
{
	input();
	dfs(1, 0);
	printf("%lld\n", ans);
	return 0;
}