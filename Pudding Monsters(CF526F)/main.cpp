#include <bits/stdc++.h>

using namespace std;

const int MX = 300005;

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
	int mx, num, add;

	NODE (const int &mx0 = 0, const int &num0 = 0, const int &add0 = 0) : mx(mx0), num(num0), add(add0) {}
	void tag(int x)
	{
		mx += x;
		add += x;
	}
	NODE operator + (const NODE &t)
	{
		NODE ret;
		if(mx > t.mx) ret.mx = mx, ret.num = num;
		else if(mx < t.mx) ret.mx = t.mx, ret.num = t.num;
		else ret.mx = t.mx, ret.num = num+t.num;
		return ret;
	}
};

struct SEGT
{
	#define ls (a<<1)
	#define rs ((a<<1)|1)
	#define mid ((l+r)/2)

	NODE tre[MX*4];

	void upd(int a)
	{
		tre[a] = tre[ls] + tre[rs];
	}

	void psd(int a)
	{
		if(tre[a].add)
		{
			tre[ls].tag(tre[a].add);
			tre[rs].tag(tre[a].add);
			tre[a].add = 0;
		}
	}

	void build(int a, int l, int r)
	{
		if(l == r) tre[a] = NODE(l+1, 1, 0);
		else build(ls, l, mid), build(rs, mid+1, r), upd(a);
	}

	void add(int a, int l, int r, int ql, int qr, int x)
	{
		if(ql<=l && r<=qr) tre[a].tag(x);
		else if(ql>r || qr<l) return;
		else psd(a), add(ls, l, mid, ql, qr, x), add(rs, mid+1, r, ql, qr, x), upd(a);
	}

	NODE qur(int a, int l, int r, int ql, int qr)
	{
		if(ql<=l && r<=qr) return tre[a];
		else if(ql>r || qr<l) return NODE(-1e9, 0, 0);
		else
		{
			psd(a);
			return qur(ls, l, mid, ql, qr) + qur(rs, mid+1, r, ql, qr);
		}
	}

	#undef ls
	#undef rs
	#undef mid
} T;

int n;
int seq[MX], pos[MX];

void input()
{
	read(n);
	for(int i=1; i<=n; i++)
	{
		int r, c;
		read(r), read(c);
		seq[r] = c;
		pos[c] = r;
	}
}

void work()
{
	long long ans = 0;
	T.build(1, 0, n);
	for(int i=1; i<=n; i++)
	{
		int l = pos[seq[i]-1];
		int r = pos[seq[i]+1];
		if(seq[i]>1 && l<i) T.add(1, 0, n, l, n, -1);
		if(seq[i]<n && r<i) T.add(1, 0, n, r, n, -1);
		ans += T.qur(1, 0, n, 0, i-1).num;
	}
	printf("%lld\n", ans);
}

int main()
{
	input();
	work();
	return 0;
}
