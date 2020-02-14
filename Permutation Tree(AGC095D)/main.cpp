#include <bits/stdc++.h>

const int MX = 100005;

using namespace std;

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

int n;
int fst[MX], nxt[MX*2], v[MX*2], lnum;

void addeg(int nu, int nv)
{
	nxt[++lnum] = fst[nu];
	fst[nu] = lnum;
	v[lnum] = nv;
}

void input()
{
	read(n);
	for(int i=1; i<n; i++)
	{
		int a, b;
		read(a), read(b);
		addeg(a, b);
		addeg(b, a);
	}
}

int fa[MX], mxd, pos;
vector<int> path;
bool on_path[MX];
int siz[MX];

void dfs(int x, int f, int d)
{
	fa[x] = f;
	if(d > mxd) pos = x, mxd = d;
	for(int i=fst[x]; i; i=nxt[i])
		if(v[i] != f)	
			dfs(v[i], x, d+1);
}

void work()
{
	dfs(1, 0, 1);
	int l = pos;
	mxd = 0;
	dfs(l, 0, 1);
	int r = pos;

	int x = r;
	while (x != l)
	{
		path.push_back(x);
		on_path[x] = 1;
		x = fa[x];
	}
	path.push_back(x);
	on_path[x] = 1;

	auto fuck = [](){puts("-1"), exit(0);};

	on_path[0] = 1;
	for(int i=1; i<=n; i++)
		if(!on_path[fa[i]]) fuck();
		else siz[fa[i]]++;
	siz[r]++;

	auto get_seq = [](vector<int> p)
	{
		vector<int> seq;
		int cnt = 1;
		for(auto v : path)
		{
			for(int i=1; i<siz[v]; i++) seq.push_back(cnt+i);
			seq.push_back(cnt);
			cnt += siz[v];
		}
		return seq;
	};

	vector<int> seq1 = get_seq(path), seq2;
	reverse(path.begin(), path.end());
	seq2 = get_seq(path);

	for(int i=0; i<seq1.size(); i++)
		if(seq1[i] != seq2[i])
			if(seq1[i] < seq2[i])
			{
				for(int j=0; j+1<seq1.size(); j++) printf("%d ", seq1[j]);
				printf("%d\n", seq1.back());
				return;
			}
			else
			{
				for(int j=0; j+1<seq2.size(); j++) printf("%d ", seq2[j]);
				printf("%d\n", seq2.back());
				return;
			}
	for(int j=0; j+1<seq2.size(); j++) printf("%d ", seq2[j]);
	printf("%d\n", seq2.back());
}

int main()
{
	input();
	work();
	return 0;
}