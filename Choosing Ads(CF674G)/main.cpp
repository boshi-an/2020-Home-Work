#include <bits/stdc++.h>

using namespace std;

const int MX = 150005;

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

int lim;

struct ITEM
{
	int x, c;

	ITEM (const int &x0 = 0, const int &c0 = 0) : x(x0), c(c0) {}
	bool operator < (const ITEM &t) const {return c > t.c;}
};

vector<ITEM> merge_val(const vector<ITEM> &a, const vector<ITEM> &b)
{
	vector<ITEM> ret = a;
	for(auto i : b)
	{
		bool had = 0;
		for(int j=0; j<ret.size(); j++)
		{
			if(ret[j].x == i.x)
			{
				ret[j].c += i.c;
				had = 1;
				break;
			}
		}
		if(!had) ret.push_back(i);
	}
	sort(ret.begin(), ret.end());
	while(ret.size() > lim)
	{
		for(auto &i : ret) i.c -= ret.back().c;
		while(ret.size() && !ret.back().c) ret.pop_back();
	}
	return ret;
}

struct SEGT
{
	#define ls (a<<1)
	#define rs (a<<1|1)
	#define mid ((l+r)/2)

	vector<ITEM> tre[MX*4];
	int tag[MX*4];

	void reset_id(int a, int id, int num)
	{
		tre[a].clear();
		tre[a].emplace_back(ITEM(id, num));
	}

	void psd(int a, int l, int r)
	{
		if(tag[a] && l!=r)
		{
			reset_id(ls, tag[a], mid-l+1);
			reset_id(rs, tag[a], r-mid);
			tag[ls] = tag[rs] = tag[a];
			tag[a] = 0;
		}
	}

	void upd(int a)
	{
		tre[a] = merge_val(tre[ls], tre[rs]);
	}

	vector<ITEM> qur(int a, int l, int r, int ql, int qr)
	{
		psd(a, l, r);
		if(ql<=l && r<=qr) return tre[a];
		else if(ql>r || qr<l) return vector<ITEM>();
		else return merge_val(qur(ls, l, mid, ql, qr), qur(rs, mid+1, r, ql, qr));
	}

	void mdf(int a, int l, int r, int ql, int qr, int id)
	{
		psd(a, l, r);
		if(ql<=l && r<=qr)
		{
			tag[a] = id;
			reset_id(a, id, r-l+1);
		}
		else if(ql>r || qr<l) return;
		else mdf(ls, l, mid, ql, qr, id), mdf(rs, mid+1, r, ql, qr, id), upd(a);
	}

	#undef ls
	#undef rs
	#undef mid
} T;

int main()
{
	int n, m, p;
	read(n), read(m), read(p);
	lim = 100/p;
	for(int i=1; i<=n; i++)
	{
		int a;
		read(a);
		T.mdf(1, 1, n, i, i, a);
	}
	for(int i=1; i<=m; i++)
	{
		int op, l, r, id;
		read(op);
		if(op == 1)
		{
			read(l), read(r), read(id);
			T.mdf(1, 1, n, l, r, id);
		}
		else
		{
			read(l), read(r);
			vector<ITEM> ret = T.qur(1, 1, n, l, r);
			printf("%d ", ret.size());
			for(auto j : ret) printf("%d ", j.x);
			putchar('\n');
		}
	}
	return 0;
}

/*
10 10 20
3 3 1 2 1 1 4 5 2 2
1 4 9 1
1 3 8 4
2 8 8
*/