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

struct NODE
{
	int s[2], x;
};

struct SEGT
{
	#define mid ((l+r)>>1)

	int cnt;
	NODE tre[MX*100];

	void upd(int a)
	{
		tre[a].x = tre[tre[a].s[0]].x + tre[tre[a].s[1]].x;
	}

	void add(int &a, int l, int r, int p, int x)
	{
		tre[++cnt] = tre[a], a = cnt;
		if(l == r) tre[a].x += x;
		else if(p <= mid) add(tre[a].s[0], l, mid, p, x), upd(a);
		else add(tre[a].s[1], mid+1, r, p, x), upd(a);
	}

	int qur(int a, int l, int r, int ql, int qr)
	{
		if(!a) return 0;
		else if(ql<=l && r<=qr) return tre[a].x;
		else if(ql>r || qr<l) return 0;
		else return qur(tre[a].s[0], l, mid, ql, qr) + qur(tre[a].s[1], mid+1, r, ql, qr);
	}

	int mer(int x, int y, int l, int r, int limy, int &num)
	{
		if(r <= limy) {num += tre[y].x; return x;}
		else if(!y) return x;
		else if(!x && l>limy) return y;
		else
		{
			int p = ++cnt;
			tre[p].s[0] = mer(tre[x].s[0], tre[y].s[0], l, mid, limy, num);
			tre[p].s[1] = mer(tre[x].s[1], tre[y].s[1], mid+1, r, limy, num);
			upd(p);
			return p;
		}
	}

	#undef mid
} T;

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

int anc[MX], rot[MX], sub[MX], ans[MX];

void dfs(int x, int f, int mx)
{
	anc[x] = mx;
	for(int i=fst[x]; i; i=nxt[i])
		if(v[i] != f)
		{
			dfs(v[i], x, max(mx, x));
			int num = 0;
			rot[x] = T.mer(rot[x], rot[v[i]], 1, n, v[i], num);
			T.add(rot[x], 1, n, v[i], num+1);
		}
}

void calc(int x, int f)
{
	ans[x] = ans[f] - ((x<anc[f]) ? T.qur(rot[x], 1, n, 1, anc[f]-1)+1 : 0) + T.qur(rot[x], 1, n, 1, anc[x]-1) + 1;
	for(int i=fst[x]; i; i=nxt[i])
		if(v[i] != f)
			calc(v[i], x);
}

void work()
{
	dfs(1, 0, 0);
	calc(1, 0);
	for(int i=2; i<=n; i++) printf("%d ", ans[i]-1);
	putchar('\n');
}

int main()
{
	input();
	work();
	return 0;
}
