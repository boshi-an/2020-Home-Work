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

int val[MX];
int n, m, cur_ans;

void input()
{
	read(n), read(m);
	for(int i=1; i<=n*2; i++) read(val[i]);
}

bool check(int k)
{
	cur_ans = 0;
	for(int i=1; i<=k; i++)
	{
		int sum = val[n*2-k-i+1]+val[n*2-k+i]-m;
		if(sum < 0) return false;
		else cmax(cur_ans, sum);
	}
	for(int i=1; i<=n-k; i++)
		cmax(cur_ans, val[i]+val[n*2-k*2-i+1]);
	return true;
}

void work()
{
	sort(val+1, val+n*2+1);
	int l = 0, r = n, mid, ans = 0;
	while(l < r)
	{
		mid = (l+r+1)/2;
		if(check(mid)) ans = l = mid;
		else ans = r = mid-1;
	}
	check(ans);
	printf("%d\n", cur_ans);
}

int main()
{
	input();
	work();
	return 0;
}