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

int n;
int seq[MX];
bool same[MX];

bool check(int l, int r)
{
	int mn = n+1, mx = 0, ll = 0, lr = 0;
	for(int i=l; i<=r; i++)
	{
		if(seq[i]>i && seq[i]<lr) return false;
		if(seq[i]<i && seq[i]<ll) return false;
		if(seq[i] > i) lr = seq[i];
		if(seq[i] < i) ll = seq[i];
		cmin(mn, seq[i]);
		cmax(mx, seq[i]);
	}
	if(mn != l) return false;
	if(mx != r) return false;
	return true;
}

int main()
{
	auto fuck = [](){puts("No"), exit(0);};
	read(n);
	for(int i=1; i<=n; i++) read(seq[i]), same[i] = (i==seq[i]);
	for(int i=2; i<n; i++) if(!same[i-1] && !same[i] && !same[i+1]) fuck();
	int lst = 1;
	for(int i=1; i<n; i++)
	{
		if(same[i] == same[i+1])
		{
			if(!check(lst, i)) fuck();
			else lst = i+1;
		}
	}
	if(!check(lst, n)) fuck();
	puts("Yes");
	return 0;
}
