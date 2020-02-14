#include <bits/stdc++.h>

using namespace std;

const int MX = 200005;

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

int N, T, Q;
int pi[MX], li[MX], wi[MX];

struct SEGT
{
	#define ls (a<<1)
	#define rs (a<<1|1)
	#define mid ((l+r)>>1)

	pair<double, int> mn[MX*4], mx[MX*4];
	double sum[MX*4];

	void upd(int a)
	{
		mn[a] = min(mn[ls], mn[rs]);
		mx[a] = max(mx[ls], mx[rs]);
		sum[a] = sum[ls] + sum[rs];
	}

	double calc(int id, int w)
	{
		w = min(w, li[id]);
		if(w < 0) return -1e9;
		else return 1.0 * pi[id] * w / (li[id]+w);
	}

	void refresh(int a, int l, int r, int p)
	{
		if(l == r)
		{
			mn[a].second = mx[a].second = p;
			sum[a] = calc(p, wi[l]);
			mx[a].first = calc(p, wi[p]+1) - calc(p, wi[p]);
			mn[a].first = calc(p, wi[p]) - calc(p, wi[p]-1);
		}
		else if(p <= mid) refresh(ls, l, mid, p), upd(a);
		else refresh(rs, mid+1, r, p), upd(a);
	}

	#undef ls
	#undef rs
	#undef mid
} tree;

void input()
{
	read(N), read(T), read(Q);
	for(int i=1; i<=N; i++) read(pi[i]);
	for(int i=1; i<=N; i++) read(li[i]);
}

void work()
{
	for(int i=1; i<=N; i++) tree.refresh(1, 1, N, i);
	for(int i=1; i<=T; i++)
	{
		wi[tree.mx[1].second]++;
		tree.refresh(1, 1, N, tree.mx[1].second);
	}
	for(int i=1; i<=Q; i++)
	{
		int t, r;
		read(t), read(r);
		if(t == 1) li[r]++;
		else li[r]--;
		tree.refresh(1, 1, N, r);
		while(tree.mx[1].first-tree.mn[1].first > 1e-10)
		{
			int a = tree.mx[1].second, b = tree.mn[1].second;
			wi[a]++;
			wi[b]--;
			tree.refresh(1, 1, N, a);
			tree.refresh(1, 1, N, b);
		}
		printf("%.10lf\n", tree.sum[1]);
	}
}

int main()
{
	input();
	work();
	return 0;
}