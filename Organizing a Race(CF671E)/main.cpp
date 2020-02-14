#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 100005;
const ll oo = 12312312312312312;

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

int n, k;
ll dis[MX], gas[MX];
ll pre[MX], suf[MX];

struct NODE
{
	ll mx_suf;	//suf is the fuel consumed when starting from n backward to i;
	ll mn_p;	//p[i] = cost[i] - suf[i], which in modifications, we modify a suffix of suf instead of prefix, which can make p stable;
	ll l_to_r;	//the answer produced by suf[i](i in [l,mid]) and p[j](j in [mid+1, r]);
	ll add;		//in modifications, we modify suf[] and cost[] together, which changes mx_suf and l_to_r, but mn_p remains stable

	void tag(ll x)
	{
		mx_suf += x;
		l_to_r += x;
		add += x;
	}
};

struct SEGT
{
	#define ls (a<<1)
	#define rs (a<<1|1)
	#define mid ((l+r)/2)

	NODE tre[MX*4];

	void psd(int a, int l, int r)
	{
		if(l!=r && tre[a].add)
		{
			tre[ls].tag(tre[a].add);
			tre[rs].tag(tre[a].add);
			tre[a].add = 0;
		}
	}

	ll calc(int a, int l, int r, ll out)
	{
		if(l == r) return tre[a].mn_p + out;
		psd(a, l, r);
		if(tre[ls].mx_suf <= out) return min(out+tre[ls].mn_p, calc(rs, mid+1, r, out));
		else return min(tre[a].l_to_r, calc(ls, l, mid, out));
	}

	void upd(int a, int l, int r)
	{
		tre[a].mx_suf = max(tre[ls].mx_suf, tre[rs].mx_suf);
		tre[a].l_to_r = calc(rs, mid+1, r, tre[ls].mx_suf);
	}

	void mdf(int a, int l, int r, int ql, int qr, ll x)
	{
		if(ql<=l && r<=qr) tre[a].tag(x);
		else if(ql>r || qr<l) return;
		else psd(a, l, r), mdf(ls, l, mid, ql, qr, x), mdf(rs, mid+1, r, ql, qr, x), upd(a, l, r);
	}

	int qur(int a, int l, int r, ll out)
	{
		if(l == r) return ((out+tre[a].mn_p) <= k) ? l : -1;
		psd(a, l, r);
		if(tre[ls].mx_suf >= out)
		{
			if(tre[a].l_to_r <= k) return qur(rs, mid+1, r, tre[ls].mx_suf);
			else return qur(ls, l, mid, out);
		}
		else return max(solve(ls, l, mid, out), qur(rs, mid+1, r, out));
	}

	int solve(int a, int l, int r, ll out)
	{
		if(l == r) return ((out+tre[a].mn_p) <= k) ? l : -1;
		psd(a, l, r);
		if(out+tre[rs].mn_p <= k) return solve(rs, mid+1, r, out);
		else return solve(ls, l, mid, out);
	}

	void build(int a, int l, int r)
	{
		if(l == r)
		{
			tre[a].mn_p = -suf[l];
			tre[a].mx_suf = suf[l];
		}
		else
		{
			build(ls, l, mid);
			build(rs, mid+1, r);
			upd(a, l, r);
			tre[a].mn_p = min(tre[ls].mn_p, tre[rs].mn_p);
		}
	}

	#undef mid
	#undef rs
	#undef ls
} T;

void input()
{
	read(n), read(k);
	dis[n] = +oo;
	for(int i=1; i<n; i++) read(dis[i]);
	for(int i=1; i<=n; i++) read(gas[i]);
	for(int i=1; i<=n; i++) pre[i] = pre[i-1] + gas[i] - dis[i];
	for(int i=1; i<=n; i++) suf[i] = suf[i-1] + gas[i] - dis[i-1];
}

int nxt[MX];
vector<int> son[MX];
int stk[MX], top;
int ans;

void dfs(int x)
{
	stk[++top] = x;
	if(x != n+1)
	{
		int l = 1, r = top, mid, ret = 1;
		while(l < r)
		{
			mid = (l+r) / 2;
			if(pre[x-1]-pre[stk[mid]-1] <= k) ret = r = mid;
			else ret = l = mid+1;
		}
		T.mdf(1, 1, n, 1, x-1, -oo);		//deleting prefix
		T.mdf(1, 1, n, stk[ret-1], n, +oo);	//deleting suffix
		cmax(ans, T.qur(1, 1, n, -oo) - x + 1);
		T.mdf(1, 1, n, stk[ret-1], n, -oo);
		T.mdf(1, 1, n, 1, x-1, +oo);
	}
	for(auto y : son[x])
	{
		T.mdf(1, 1, n, x-1, n, pre[y-1]-pre[x-1]);
		dfs(y);
		T.mdf(1, 1, n, x-1, n, pre[x-1]-pre[y-1]);
	}
	top--;
}

void work()
{
	for(int i=n; i>=1; i--)
	{
		if(pre[i-1] > pre[i]) nxt[i] = i+1;
		else
		{
			nxt[i] = nxt[i+1];
			while(pre[nxt[i]-1] >= pre[i-1]) nxt[i] = nxt[nxt[i]];
		}
		son[nxt[i]].push_back(i);
	}
	T.build(1, 1, n);
	dfs(n+1);
	printf("%d\n", ans);
}

int main()
{
	input();
	work();
	return 0;
}