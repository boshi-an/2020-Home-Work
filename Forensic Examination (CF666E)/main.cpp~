#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <assert.h>
#define MX 100005
#define ML 500005

using namespace std;

int fst[MX], nxt[MX*2], v[MX*2], lnum;

void addeg(int nu, int nv)
{
	nxt[++lnum] = fst[nu];
	fst[nu] = lnum;
	v[lnum] = nv;
}

struct NODE
{
	int x, p, ls, rs;
	
	NODE () {x = p = ls = rs = 0;}
	
	NODE operator + (const NODE& t) const
	{
		if(x >= t.x) return *this;
		else return t;
	}
};

struct SEGT
{
	#define mid ((l+r)>>1)
	
	NODE tre[MX*40];
	int rot[MX], cnt;
	
	void upd(int a)
	{
		int ls = tre[a].ls, rs = tre[a].rs;
		if(tre[ls].x >= tre[rs].x) tre[a].x = tre[ls].x, tre[a].p = tre[ls].p;
		else tre[a].x = tre[rs].x, tre[a].p = tre[rs].p;
	}
	
	void add(int& a, int o, int l, int r, int p, int x)
	{
		a = ++cnt;
		tre[a] = tre[o];
		if(l == r) tre[a].x += x, tre[a].p = l;
		else if(p <= mid) add(tre[a].ls, tre[o].ls, l, mid, p, x), upd(a);
		else add(tre[a].rs, tre[o].rs, mid+1, r, p, x), upd(a);
	}
	
	int comb(int a, int b, int l, int r)
	{
		if(!a || !b) return (a|b);
		else if(l == r)
		{
			int cur = ++cnt;
			tre[cur].x = tre[a].x + tre[b].x;
			tre[cur].p = l;
			return cur;
		}
		else
		{
			int cur = ++cnt;
			tre[cur].ls = comb(tre[a].ls, tre[b].ls, l, mid);
			tre[cur].rs = comb(tre[a].rs, tre[b].rs, mid+1, r);
			upd(cur);
			return cur;
		}
	}
	
	NODE qur(int a, int l, int r, int ql, int qr)
	{
		if(ql<=l && r<=qr) return tre[a];
		else if(ql>r || qr<l) return NODE();
		else return qur(tre[a].ls, l, mid, ql, qr) + qur(tre[a].rs, mid+1, r, ql, qr);
	}
	
	#undef mid
} T;

struct SAM
{
	int cnt, lst;
	int tra[MX][26], len[MX], fa[MX], rak[MX];
	
	SAM () {cnt = lst = 1;}
	
	void insert(int c)
	{
		int cur = ++cnt, p = lst;
		len[cur] = len[lst]+1;
		lst = cur;
		for(; p&&!tra[p][c]; p=fa[p]) tra[p][c] = cur;
		if(!p) fa[cur] = 1;
		else
		{
			int q = tra[p][c];
			if(len[q] == len[p]+1) fa[cur] = q;
			else
			{
				int cpy = ++cnt;
				memmove(tra[cpy], tra[q], sizeof(tra[cpy]));
				len[cpy] = len[p]+1;
				fa[cpy] = fa[q];
				fa[q] = fa[cur] = cpy;
				for(; p&&tra[p][c]==q; p=fa[p]) tra[p][c] = cpy;
			}
		}
	}
	
	void build()
	{
		for(int i=2; i<=cnt; i++) addeg(fa[i], i);
	}
} S;

struct GRAPH
{
	int n;
	int fa[MX][20];
	int val[MX];
	
	void init(int* src_fa, int* src_val, int src_n)
	{
		n = src_n;
		for(int i=1; i<=n; i++) fa[i][0] = src_fa[i], val[i] = src_val[i];
		for(int i=1; i<20 ;i++)
			for(int j=1; j<=n; j++)
				fa[j][i] = fa[fa[j][i-1]][i-1];
	}
	
	int jump(int x, int tar)
	{
		for(int i=19; i>=0; i--)
			if(val[fa[x][i]] >= tar)
				x = fa[x][i];
		return x;
	}
} G;

int n, m;
char src[ML];
int len;
int pos[ML], mat[ML];

void input()
{
	static char tmp[MX];
	scanf("%s", src+1);
	len = strlen(src+1);
	scanf("%d", &n);
	for(int i=1; i<=n; i++)
	{
		scanf("%s", tmp+1);
		int l = strlen(tmp+1);
		S.lst = 1;
		for(int j=1; j<=l; j++) S.insert(tmp[j]-'a'), T.add(T.rot[S.lst], 0, 1, n, i, 1);
	}
	scanf("%d", &m);
}

void dfs(int x)
{
	for(int i=fst[x]; i; i=nxt[i])
	{
		dfs(v[i]);
		T.rot[x] = T.comb(T.rot[x], T.rot[v[i]], 1, n);
	}
}

void work()
{
	S.build();
	G.init(S.fa, S.len, S.cnt);
	dfs(1);
	int now = 1, mln = 0;
	for(int i=1; i<=len; i++)
	{
		int c = src[i]-'a';
		while(now!=1 && !S.tra[now][c]) now = S.fa[now], mln = min(mln, S.len[now]);
		if(S.tra[now][c]) now = S.tra[now][c], mln++;
		pos[i] = now;
		mat[i] = mln;
	}
	for(int i=1; i<=m; i++)
	{
		int sl, sr, ql, qr;
		scanf("%d%d%d%d", &ql, &qr, &sl, &sr);
		int x = G.jump(pos[sr], sr-sl+1);
		if(S.len[x]>=sr-sl+1 && mat[sr]>=sr-sl+1)
		{
			NODE t = T.qur(T.rot[x], 1, n, ql, qr);
			if(t.x == 0) t.p = ql;
			printf("%d %d\n", t.p, t.x);
		}
		else printf("%d 0\n", ql);
	}
}

int main()
{
	input();
	work();
	return 0;
}
