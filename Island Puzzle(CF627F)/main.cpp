#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 400005;

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

int fst[MX], nxt[MX], v[MX], lnum;
int ida[MX], idb[MX], on_path[MX];
int n;

void addeg(int nu, int nv)
{
	nxt[++lnum] = fst[nu];
	fst[nu] = lnum;
	v[lnum] = nv;
}

void input()
{
	read(n);
	for(int i=1; i<=n; i++) read(ida[i]);
	for(int i=1; i<=n; i++) read(idb[i]);
	for(int i=1; i<n; i++)
	{
		int a, b;
		read(a), read(b);
		addeg(a, b);
		addeg(b, a);
	}
}

int dep[MX], fa[MX], usd_mov;

void dfs1(int x, int f, int tar)
{
	dep[x] = dep[f] + 1, fa[x] = f;
	if(x == tar)
	{
		int tmp = x;
		on_path[x] = 1;
		while(fa[tmp]) swap(ida[tmp], ida[fa[tmp]]), tmp = fa[tmp], on_path[tmp] = 1, usd_mov++;
	}
	for(int i=fst[x]; i; i=nxt[i])
	{
		int y = v[i];
		if(v[i] != f) dfs1(v[i], x, tar);
	}
}

void fuck_out(char *s)
{
	cerr << s << endl;
	puts("-1");
	exit(0);
}

int posa[MX], posb[MX], on_cyc[MX];

void work()
{
	int frm = 0, tar = 0;
	for(int i=1; i<=n; i++) if(!ida[i]) frm = i;
	for(int i=1; i<=n; i++) if(!idb[i]) tar = i;
	dfs1(tar, 0, frm);
	for(int i=1; i<=n; i++) posa[ida[i]] = i, posb[idb[i]] = i;
	for(int i=1; i<=n; i++) if(ida[i] != idb[i]) on_cyc[i] = 1;
	int bot1 = 0, bot2 = 0;
	static int vis[MX];
	vector<int> cyc;
	for(int i=1; i<=n; i++) if(on_cyc[i] && dep[i]>dep[bot1]) bot1 = i;
	for(int x=bot1; on_cyc[x]; x=fa[x]) cyc.push_back(x), vis[x] = 1;
	reverse(cyc.begin(), cyc.end());
	if(!bot1) {printf("%d %d\n", 0, usd_mov); return;}
	for(int i=1; i<=n; i++) if(on_cyc[i] && dep[i]>dep[bot2] && !vis[i]) bot2 = i;
	for(int x=bot2; on_cyc[x]; x=fa[x]) cyc.push_back(x), vis[x] = -1;
	int top1 = *cyc.begin(), top2 = *cyc.rbegin(), entry = fa[top1];
	if(bot2 && fa[top1]!=fa[top2]) fuck_out("unconnected loop!");
	for(int i=1; i<=n; i++) if(on_cyc[i] && !vis[i]) fuck_out("not a single loop!");
	int step = 0, revs = 0;
	for(int i=0; i<cyc.size(); i++)
		if(idb[cyc[i]] == ida[cyc[0]])
			step = i;
	for(int i=0; i<cyc.size(); i++)
		if(idb[cyc[(i+step)%cyc.size()]] != ida[cyc[i]])
			fuck_out("can't rearrange loop!");
	for(int x=frm; x; x=fa[x]) revs += vis[x];
	ll way1 = usd_mov + 1ll*step*(cyc.size()+1);
	ll way2 = usd_mov + 1ll*(cyc.size()-step)*(cyc.size()+1);
	if(revs > 0) way2 -= revs*2;
	else way1 += revs*2;
	ll ans = min(way1, way2);
	int adda = 0, addb = 0;
	if(bot1 && bot2) adda = bot1, addb = bot2;
	else adda = bot1, addb = entry;
	for(int x=entry; !on_path[x]; x=fa[x]) ans += 2;
	if(adda > addb) swap(adda, addb);
	printf("%d %d %lld\n", adda, addb, ans);
}

int main()
{
	input();
	work();
	return 0;
}

/*
7
1 2 3 4 5 6 0
0 1 2 3 4 5 6
1 2
2 3
3 4
2 6
6 5
6 7
*/