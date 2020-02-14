#include <bits/stdc++.h>

using namespace std;

const int MX = 100005;

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

int n, q;
int fst[MX], nxt[MX*2], v[MX*2], w[MX*2], lnum;

struct TREE
{
	int root;
	int fa[MX][20];
	int wfa[MX], dep[MX];
	pair<int, int> mxc[MX];
	int mx_len[MX], mx_pos[MX];

	void dfs(int x, int f)
	{
		mx_len[x] = 0;
		mx_pos[x] = x;
		fa[x][0] = f;
		dep[x] = dep[f] + wfa[x];
		for(int i=1; i<20; i++) fa[x][i] = fa[fa[x][i-1]][i-1];
		for(int i=fst[x]; i; i=nxt[i])
			if(v[i] != f)
			{
				wfa[v[i]] = w[i];
				dfs(v[i], x);
				if(mx_len[v[i]]+w[i] > mx_len[x])
				{
					mx_len[x] = mx_len[v[i]] + w[i];
					mx_pos[x] = mx_pos[v[i]];
				}
			}
	}

	int find_top_less(int x, pair<int, int> val)
	{
		for(int i=19; i>=0; i--)
			if(fa[x][i] && mxc[fa[x][i]] < val)
				x = fa[x][i];
		return x;
	}

	int sum[MX];
	vector<pair<int, int> > seq;
	set<pair<int, int> > rak;
	bool vis[MX];

	void get_initial_seq()
	{
		for(int i=1; i<=n; i++) rak.insert(make_pair(mx_len[i]+wfa[i], mx_pos[i]));
		while(rak.size())
		{
			auto tmp = *rak.rbegin();
			int x = tmp.second;
			seq.push_back(tmp);
			mxc[tmp.second] = tmp;
			sum[seq.size()] = sum[seq.size()-1] + tmp.first;
			while(!vis[x])
			{
				vis[x] = 1;
				rak.erase(make_pair(mx_len[x]+wfa[x], mx_pos[x]));
				x = fa[x][0];
			}
		}
	}

	void collect(int x, int f)
	{
		for(int i=fst[x]; i; i=nxt[i])
			if(v[i] != f)
				collect(v[i], x), cmax(mxc[x], mxc[v[i]]); 
	}

	int calc(int x, int y)
	{
		if(2*y-1 > seq.size()) return sum[seq.size()];
		else if(mxc[x] >= seq[y*2-2]) return sum[y*2-1];
		else
		{
			int ret1 = 0, ret2 = 0;
			int top = find_top_less(x, seq[y*2-2]);
			ret1 = sum[y*2-2] + mx_len[x] + dep[x] - dep[fa[top][0]];
			ret2 = sum[y*2-1] - mx_len[fa[top][0]] + mx_len[x] + dep[x] - dep[fa[top][0]];
			return max(ret1, ret2);
		}
	}

	void init(int x)
	{
		root = x;
		dfs(root, 0);
		get_initial_seq();
		collect(root, 0);
	}
} T1, T2;

void addeg(int nu, int nv, int nw)
{
	nxt[++lnum] = fst[nu];
	fst[nu] = lnum;
	v[lnum] = nv;
	w[lnum] = nw;
}

void input()
{
	read(n), read(q);
	for(int i=1; i<n; i++)
	{
		int a, b, c;
		read(a), read(b), read(c);
		addeg(a, b, c);
		addeg(b, a, c);
	}
}

int mxp, mxd;

void dfs(int x, int f, int d)
{
	if(d > mxd) mxp = x, mxd = d;
	for(int i=fst[x]; i; i=nxt[i])
		if(v[i] != f)
			dfs(v[i], x, d+w[i]);
}

void work()
{
	mxp = mxd = 0;
	dfs(1, 0, 1);
	T1.init(mxp);
	mxp = mxd = 0;
	dfs(T1.root, 0, 1);
	T2.init(mxp);
	int ans = 0;
	for(int i=1; i<=q; i++)
	{
		int x, y;
		read(x), read(y);
		x = (x+ans-1) % n + 1;
		y = (y+ans-1) % n + 1;
		ans = max(T1.calc(x, y), T2.calc(x, y));
		printf("%d\n", ans);
	}
}

int main()
{
	input();
	work();
	return 0;
}

/*
12 1
1 2 1
2 3 1
3 4 1
4 5 1
5 6 1
6 7 1
4 8 1
8 9 1
9 10 1
10 11 1
9 12 1
12 1
*/