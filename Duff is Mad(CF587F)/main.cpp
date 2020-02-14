#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 100005;
const int MB = 320;

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

struct BLK
{
	int blk[MX/MB+100], sum[MX];
	int bel[MX];

	BLK ()
	{
		for(int i=1; i<MX; i++) bel[i] = i/MB;
	}

	void add(int r, int x)
	{
		for(int i=0; i<bel[r]; i++) blk[i] += x;
		for(int i=r; i>=1&&bel[i]==bel[r]; i--) sum[i] += x;
	}

	int qur(int r)
	{
		return blk[bel[r]] + sum[r];
	}
} B;

struct AC
{
	int son[MX][26], fal[MX];
	int cnt, rot;

	AC () {cnt = rot = 1;}

	int insert(string s)
	{
		int x = rot;
		for(auto c : s)
		{
			if(!son[x][c-'a']) son[x][c-'a'] = ++cnt;
			x = son[x][c-'a'];
		}
		return x;
	}

	void build()
	{
		queue<int> que;
		for(int i=0; i<26; i++)
			if(son[rot][i]) fal[son[rot][i]] = rot, que.push(son[rot][i]);
			else son[rot][i] = rot;
		while(que.size())
		{
			int x = que.front();
			que.pop();
			for(int i=0; i<26; i++)
			{
				int &y = son[x][i];
				if(!y) y = son[fal[x]][i];
				else fal[y] = son[fal[x]][i], que.push(y);
			}
		}
	}
} A;

struct GRAPH
{
	int fst[MX], nxt[MX], v[MX], lnum;

	void addeg(int nu, int nv)
	{
		nxt[++lnum] = fst[nu];
		fst[nu] = lnum;
		v[lnum] = nv;
	}
} G;

struct QUR
{
	int qid, x, f;

	QUR (const int &q0 = 0, const int &x0 = 0, const int &f0 = 0) : qid(q0), x(x0), f(f0) {}
};

int n, q;
string str[MX];
int pos[MX];
int ql[MX], qr[MX], qk[MX], appk[MX];
vector<QUR> squr[MX];	//index, f
vector<QUR> bqur[MX];	//index, f
ll ans[MX];

void input()
{
	read(n), read(q);
	for(int i=1; i<=n; i++)
	{
		cin >> str[i];
		pos[i] = A.insert(str[i]);
	}
	for(int i=1; i<=q; i++)
	{
		read(ql[i]), read(qr[i]), read(qk[i]);
		appk[qk[i]]++;
	}
	for(int i=1; i<=q; i++)
	{
		if(appk[qk[i]] <= MB)
		{
			squr[ql[i]-1].emplace_back(QUR(i, qk[i], -1));
			squr[qr[i]].emplace_back(QUR(i, qk[i], +1));
		}
		else
		{
			bqur[qk[i]].emplace_back(QUR(i, ql[i]-1, -1));
			bqur[qk[i]].emplace_back(QUR(i, qr[i], +1));
		}
	}
}

int dfn[MX][2], dfc;

void dfs(int x)
{
	dfn[x][0] = ++dfc;
	for(int i=G.fst[x]; i; i=G.nxt[i]) dfs(G.v[i]);
	dfn[x][1] = dfc;
}

ll walk(string s)
{
	ll ret = 0;
	int x = A.rot;
	for(auto c : s)
	{
		x = A.son[x][c-'a'];
		ret += B.qur(dfn[x][0]);
	}
	return ret;
}

int tag[MX];
ll sum[MX];

void get_sum(int x)
{
	for(int i=G.fst[x]; i; i=G.nxt[i])
	{
		get_sum(G.v[i]);
		tag[x] += tag[G.v[i]];
	}
}

void cover(string s)
{
	int x = A.rot;
	for(auto c : s)
	{
		x = A.son[x][c-'a'];
		tag[x]++;
	}
}

void work()
{
	A.build();
	for(int i=2; i<=A.cnt; i++) G.addeg(A.fal[i], i);
	dfs(1);
	for(int i=1; i<=n; i++)
	{
		B.add(dfn[pos[i]][1], 1);
		B.add(dfn[pos[i]][0]-1, -1);
		for(auto t : squr[i]) ans[t.qid] += walk(str[t.x]) * t.f;
	}
	for(int i=1; i<=n; i++)
	{
		if(appk[i] > MB)
		{
			memset(tag, 0, sizeof(tag));
			cover(str[i]);
			get_sum(A.rot);
			for(int j=1; j<=n; j++) sum[j] = tag[pos[j]] + sum[j-1];
			for(auto t : bqur[i]) ans[t.qid] += sum[t.x] * t.f;
		}
	}
	for(int i=1; i<=q; i++) printf("%lld\n", ans[i]);
}

int main()
{
	input();
	work();
	return 0;
}
