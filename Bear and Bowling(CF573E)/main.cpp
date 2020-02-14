#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 200005;

struct NODE
{
	int s[2], siz;
	ll k, b, x;
};

struct TREE
{
	int root;
	NODE tre[MX];
	
	bool rand_top(int sa, int sb)
	{
		return rand()%(sa+sb) < sa;
	}
	
	void upd(int a)
	{
		int ls = tre[a].s[0], rs = tre[a].s[1];
		tre[a].siz = tre[ls].siz + tre[rs].siz + 1;
	}
	
	void tag(int a, ll k, ll b)
	{
		int ls = tre[a].s[0], rs = tre[a].s[1];
		tre[a].x += tre[ls].siz*k + b;
		tre[a].k += k, tre[a].b += b;
	}
	
	void psd(int a)
	{
		if(tre[a].k || tre[a].b)
		{
			tag(tre[a].s[0], tre[a].k, tre[a].b);
			tag(tre[a].s[1], tre[a].k, tre[a].b+tre[a].k*(tre[tre[a].s[0]].siz+1));
			tre[a].k = tre[a].b = 0;
		}
	}
	
	void split(int a, int k, int &x, int &y)
	{
		if(!a) x = y = 0;
		else
		{
			int tmp;
			psd(a);
			int lsiz = tre[tre[a].s[0]].siz;
			if(k <= lsiz)
			{
				y = a;
				split(tre[a].s[0], k, x, tmp);
				tre[a].s[0] = tmp;
			}
			else
			{
				x = a;
				split(tre[a].s[1], k-lsiz-1, tmp, y);
				tre[a].s[1] = tmp;
			}
			upd(a);
		}
	}
	
	int merge(int a, int b)
	{
		if((!a) || (!b)) return (a|b);
		else
		{
			if(rand_top(tre[a].siz, tre[b].siz))
			{
				psd(a);
				tre[a].s[1] = merge(tre[a].s[1], b);
				upd(a);
				return a;
			}
			else
			{
				psd(b);
				tre[b].s[0] = merge(a, tre[b].s[0]);
				upd(b);
				return b;
			}
		}
	}
	
	int kth(int a, int k)
	{
		psd(a);
		int lsiz = tre[tre[a].s[0]].siz;
		if(lsiz+1 == k) return a;
		else if(k <= lsiz) return kth(tre[a].s[0], k);
		else return kth(tre[a].s[1], k-lsiz-1);
	}
	
	ll max_x(int a)
	{
		if(!a) return -1e18;
		psd(a);
		return max(max(max_x(tre[a].s[0]), max_x(tre[a].s[1])), tre[a].x);
	}
} T;

int n;
int val[MX];

int main()
{
	scanf("%d", &n);
	for(int i=1; i<=n; i++) scanf("%d", &val[i]);
	T.root = 1;
	T.tre[1].siz = 1;
	for(int i=1; i<=n; i++)
	{
		int l = 2, r = i+1, mid, ans = 2;
		while(l < r)
		{
			mid = (l+r)/2;
			int a = T.kth(T.root, mid-1);
			int b = T.kth(T.root, mid);
			if(T.tre[a].x+1ll*(mid-1)*val[i] > T.tre[b].x) ans = r = mid;
			else ans = l = mid + 1;
		}
		//ans : the first node which is better using the second transistion (plus kx+b)
		int x, y;
		ll tmp_add = T.tre[T.kth(T.root, ans-1)].x;
		T.split(T.root, ans-1, x, y);
		T.tre[i+1].x = tmp_add;
		T.tre[i+1].siz = 1;
		y = T.merge(i+1, y);
		T.tag(y, val[i], 1ll*(ans-1)*val[i]);
		T.root = T.merge(x, y);
	}
	printf("%lld\n", T.max_x(T.root));
	return 0;
}