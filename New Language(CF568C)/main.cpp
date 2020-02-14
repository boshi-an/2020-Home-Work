#include <bits/stdc++.h>

using namespace std;

const int MX = 404;
const int ME = 320005;

template<typename T> void cmax(T &x, const T &y)
{
	if(y > x) x = y;
}

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

struct GRAPH
{
	int fst[MX], nxt[ME], v[ME], lnum;

	void addeg(int nu, int nv)
	{
		nxt[++lnum] = fst[nu];
		fst[nu] = lnum;
		v[lnum] = nv;
	}

	vector<int> con[MX];
	int bel[MX], dfn[MX], low[MX], stk[MX], ins[MX], top, col, dfc;

	void tarjan(int x)
	{
		dfn[x] = low[x] = ++dfc;
		stk[++top] = x;
		ins[x] = 1;
		for(int i=fst[x]; i; i=nxt[i])
		{
			int y = v[i];
			if(!dfn[y]) tarjan(y), cmin(low[x], low[y]);
			else if(ins[y]) cmin(low[x], dfn[y]);
		}
		if(low[x] == dfn[x])
		{
			col++;
			while(stk[top] != x)
			{
				int y = stk[top--];
				ins[y] = 0;
				bel[y] = col;
				con[col].push_back(y);
			}
			int y = stk[top--];
			ins[y] = 0;
			bel[y] = col;
			con[col].push_back(y);
		}
	}
} G;

int n, cn, m;
char str[MX], lim[MX];

int type(char c)
{
	return (c=='C');
}

int id(int x, int p)
{
	return p*n + x;
}

char get_c(char &c)
{
	c = getchar();
	while(!isalpha(c)) c = getchar();
	return c;
}

void input()
{
	scanf("%s", str);
	cn = strlen(str);
	read(n), read(m);
	for(int i=1; i<=m; i++)
	{
		int p1, p2;
		char c1, c2;
		read(p1), get_c(c1);
		read(p2), get_c(c2);
		int v1 = type(c1), v2 = type(c2);
		G.addeg(id(p1, v1), id(p2, v2));
		G.addeg(id(p2, v2^1), id(p1, v1^1));
	}
	scanf("%s", lim+1);
}

vector<int> aff[MX];
char off_mx[2];
char ans[MX];
int fxd0[MX], fxd1[MX];

auto fuck = [](){puts("-1"); exit(0);};

bool check(int pre)
{
	bool stuck = 1;
	for(int i=1; i<=pre; i++)
	{
		if(fxd0[i] && fxd1[i]) return false;
		if(stuck && ans[i]<lim[i]) return false;
		else if(stuck && ans[i]>lim[i]) stuck = 0;
	}
	for(int i=pre+1; i<=n; i++)
	{
		if(fxd0[i] && fxd1[i]) return false;
		else if(stuck && fxd0[i] && off_mx[0]<lim[i]) return false;
		else if(stuck && fxd1[i] && off_mx[1]<lim[i]) return false;
		else if(stuck && fxd0[i] && off_mx[0]>lim[i]) stuck = 0;
		else if(stuck && fxd1[i] && off_mx[1]>lim[i]) stuck = 0;
		else if(stuck && !fxd0[i] && !fxd1[i] && max(off_mx[0], off_mx[1])>lim[i]) stuck = 0;
	}
	return true;
}

void solve(int p)
{
	if(p == n+1)
	{
		printf("%s\n", ans+1);
		exit(0);
	}
	if(fxd0[p])
	{
		for(int i=0; i<cn; i++)
			if(str[i] == 'V')
			{
				ans[p] = 'a'+i;
				if(check(p)) solve(p+1), fuck();
			}
	}
	else if(fxd1[p])
	{
		for(int i=0; i<cn; i++)
			if(str[i] == 'C')
			{
				ans[p] = 'a'+i;
				if(check(p)) solve(p+1), fuck();
			}
	}
	else
	{
		for(int i=0; i<cn; i++)
		{
			ans[p] = 'a'+i;
			int t = type(str[i]);
			for(auto y : aff[G.bel[id(p, t)]])
			{
				if(y <= n) fxd0[y]++;
				else fxd1[y-n]++;
			}
			if(check(p)) solve(p+1), fuck();
			for(auto y : aff[G.bel[id(p, t)]])
			{
				if(y <= n) fxd0[y]--;
				else fxd1[y-n]--;
			}
		}
	}
}

void work()
{
	for(int i=0; i<cn; i++)
	{
		if(str[i] == 'V') cmax(off_mx[0], (char)(i+'a'));
		else cmax(off_mx[1], (char)(i+'a'));
	}
	for(int i=1; i<=n*2; i++)
		if(!G.dfn[i])
			G.tarjan(i);
	for(int i=1; i<=n; i++)
		if(G.bel[id(i, 0)] == G.bel[id(i, 1)])
			fuck();
	for(int i=1; i<=G.col; i++)
	{
		int c;
		aff[i] = G.con[i];
		for(auto x : G.con[i])
			for(int j=G.fst[x]; j; j=G.nxt[j])
				if((c=G.bel[G.v[j]]) != G.bel[x])
					aff[i].insert(aff[i].end(), aff[c].begin(), aff[c].end());
		sort(aff[i].begin(), aff[i].end());
		aff[i].erase(unique(aff[i].begin(), aff[i].end()), aff[i].end());
	}
	solve(1);
	fuck();
}

int main()
{
	input();
	work();
	return 0;
}