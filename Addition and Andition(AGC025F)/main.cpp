#include <bits/stdc++.h>

using namespace std;

const int MX = 2000006;

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

set<int> pos[2];
char seq[2][MX];

void solve(int p, int k, int a, int b)
{
	if(k<0 || (!a&&!b)) return;
	int nxt[2], near, from;
	for(int i=0; i<2; i++) nxt[i] = *pos[i].lower_bound(p);
	near = min(nxt[0], nxt[1]);
	from = (near == nxt[1]);
	if(a && b)
	{
		if(near-p > k)
		{
			pos[0].insert(p+k);
			pos[1].insert(p+k);
		}
		else
		{
			pos[from].erase(near);
			pos[from^1].insert(near);
			solve(near+1, k-(near-p), !from, from);
		}
	}
	else
	{
		if(p != near) pos[b==1].insert(p);
		else if((b==1) != from)
		{
			if(k) pos[from].erase(p), solve(p+1, k-1, 1, 1);
			else pos[!from].insert(p);
		}
		else pos[from].erase(p), solve(p+1, k, a, b);
	}
}

int len[2], n, k;
char out[2][MX];

int main()
{
	read(len[0]), read(len[1]), read(k);
	n = max(len[0], len[1]);
	for(int i=0; i<2; i++)
	{
		scanf("%s", seq[i]);
		fill(seq[i]+len[i], seq[i]+n, '0');
		reverse(seq[i], seq[i]+len[i]);
		pos[i].insert(1e9);
	}
	for(int i=n-1; i>=0; i--) solve(i, k, seq[0][i]-'0', seq[1][i]-'0');
	for(int i=0; i<2; i++)
	{
		pos[i].erase(1e9);
		len[i] = *pos[i].rbegin()+1;
		fill(out[i], out[i]+len[i], '0');
		for(auto x : pos[i]) out[i][x] = '1';
		reverse(out[i], out[i]+len[i]);
		puts(out[i]);
	}
	return 0;
}