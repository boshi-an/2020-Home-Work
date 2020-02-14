#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

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

int n, m;
int seq[MX], cng[MX];

void input()
{
	read(n);
	for(int i=1; i<=n; i++) read(seq[i]);
	read(m);
	for(int i=1; i<=m; i++) read(cng[i]);
	sort(cng+1, cng+m+1);
	cng[m+1] = 1e9+109;
}

int f[MX], g[MX], ans[MX];

void work(int l, int r, int vl, int vr)
{
	if(l==r && seq[l]>=1)
	{
		if(seq[l]>=vl && seq[l]<=vr) ans[l] = seq[l];
		else ans[l] = vl;
	}
	else if(l==r && seq[l]<=0)
	{
		ans[l] = *upper_bound(cng+1, cng+m+1, vl);
		if(ans[l] > vr) ans[l] = vl;
	}
	else
	{
		int mid = (l+r) / 2;
		int sl = upper_bound(cng+1, cng+m+1, vl) - cng;
		int sr = upper_bound(cng+1, cng+m+1, vr) - cng;
		f[0] = vl;
		g[0] = 0;
		for(int i=1; i<=r-l+1; i++) f[i] = 1e9+9;
		for(int i=l; i<=r; i++)
		{
			if(seq[i]>=1 && seq[i]>=vl && seq[i]<=vr)
			{
				int p = lower_bound(f, f+r-l+1, seq[i]) - f;
				f[p] = seq[i];
				if(i <= mid) g[p] = seq[i];
				else g[p] = g[p-1];
			}
			else if(seq[i] == -1)
			{
				int p = r-l+1;
				for(int j=sr-1; j>=sl; j--)
				{
					while(f[p] >= cng[j]) p--;
					f[p+1] = cng[j];
					if(i <= mid) g[p+1] = cng[j];
					else g[p+1] = g[p];
				}
			}
		}
		int mxlen = lower_bound(f, f+r-l+2, 1e9+9) - f - 1;
		int midval = max(g[mxlen], vl);
		work(l, mid, vl, midval);
		work(mid+1, r, midval, vr);
	}
}

int out[MX];

void output()
{
	multiset<int> have;
	for(int i=1; i<=m; i++) have.insert(cng[i]);
	for(int i=1; i<=n; i++)
	{
		if(seq[i] >= 1) out[i] = seq[i];
		else if(ans[i] != ans[i-1]) out[i] = ans[i], have.erase(have.find(ans[i]));
	}
	for(int i=1; i<=n; i++)
		if(seq[i]==-1 && ans[i]==ans[i-1])
			out[i] = *have.begin(), have.erase(have.begin());
	for(int i=1; i<=n; i++) printf("%d ", out[i]); putchar('\n');
}

int main()
{
	input();
	work(1, n, 0, 1e9);
	output();
	int cnt = 0;
	for(int i=1; i<=n; i++)
		if(ans[i] != ans[i-1])
			cnt++;
	//cerr<<cnt<<endl;
	//for(int i=1; i<=n; i++) cout<<ans[i]<<" "; cout<<endl;
	return 0;
}

/*
100
-1 2 3 74 90 39 37 18 23 -1 5 -1 56 88 99 49 72 11 19 6 81 24 8 23 64 -1 100 77 61 87 23 -1 20 15 -1 55 25 40 4 25 73 85 87 72 5 98 46 49 -1 67 81 58 3 -1 22 14 -1 -1 92 -1 78 53 64 23 84 10 -1 54 83 55 24 -1 79 23 92 41 -1 -1 93 -1 59 90 64 93 95 22 -1 67 -1 33 41 84 37 73 -1 -1 18 49 50 58
20
57 23 22 93 77 19 85 32 79 94 20 59 78 35 16 92 33 94 42 11
*/