#include <bits/stdc++.h>

using namespace std;

const int MX = 500005;

struct OPR
{
	int x, f, id;

	OPR (const int &x0 = 0, const int &f0 = 0, const int &i0 = 0) : x(x0), f(f0), id(i0) {}
};

struct AC
{
	int son[MX][26], fal[MX], cnt;

	AC ()
	{
		memset(son, 0, sizeof(son));
		memset(fal, 0, sizeof(fal));
		cnt = 1;
	}

	int insert(string str)
	{
		int x = 1;
		for(auto c : str)
		{
			if(!son[x][c-'a']) son[x][c-'a'] = ++cnt;
			x = son[x][c-'a'];
		}
		return x;
	}

	void build()
	{
		queue<int> que;
		for(auto &y : son[1])
			if(!y) y = 1;
			else que.push(y), fal[y] = 1;
		while(!que.empty())
		{
			int x = que.front();
			que.pop();
			for(int i=0; i<26; i++)
				if(!son[x][i]) son[x][i] = son[fal[x]][i];
				else fal[son[x][i]] = son[fal[x]][i], que.push(son[x][i]);
		}
	}
} A;

struct TREE
{
	int fst[MX], nxt[MX], dfn[MX][2], dep[MX], dfc;

	void add(int f, int x)
	{
		nxt[x] = fst[f];
		fst[f] = x;
	}

	void dfs(int x)
	{
		dfn[x][0] = ++dfc;
		for(int y=fst[x]; y; y=nxt[y]) dep[y] = dep[x]+1, dfs(y);
		dfn[x][1] = dfc;
	}
} T;

struct FEN
{
	int sum[MX];

	void add(int p, int x)
	{
		for(int i=p; i<MX; i+=(i&-i)) sum[i] += x;
	}

	int qur(int p)
	{
		int ret = 0;
		for(int i=p; i; i-=(i&-i)) ret += sum[i];
		return ret;
	}
} F;

int n, q;
string str[MX];
int endpos[MX];
int ans[MX];
vector<OPR> opr[MX];

void input()
{
	scanf("%d%d", &n, &q);
	for(int i=1; i<=n; i++) cin >> str[i];
	for(int i=1; i<=q; i++)
	{
		int l, r, k;
		scanf("%d%d%d", &l, &r, &k);
		opr[r].push_back(OPR(k, 1, i));
		opr[l-1].push_back(OPR(k, -1, i));
	}
}

void work()
{
	for(int i=1; i<=n; i++) endpos[i] = A.insert(str[i]);
	A.build();
	for(int i=2; i<=A.cnt; i++) T.add(A.fal[i], i);
	T.dfs(1);
	for(int i=1; i<=n; i++)
	{
		int x = 1;
		for(auto c : str[i])
		{
			x = A.son[x][c-'a'];
			F.add(T.dfn[x][0], +1);
		}
		for(auto t : opr[i])
		{
			ans[t.id] += t.f * (F.qur(T.dfn[endpos[t.x]][1]) - F.qur(T.dfn[endpos[t.x]][0]-1));
		}
	}
	for(int i=1; i<=q; i++) printf("%d\n", ans[i]);
}

int main()
{
	input();
	work();
	return 0;
}