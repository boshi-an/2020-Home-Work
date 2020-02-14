#include <bits/stdc++.h>
#define mov(x) (1ll<<(x))

using namespace std;

typedef long long ll;

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

const int MX = 1005;

int n;
int px[MX], py[MX];

void input()
{
	read(n);
	for(int i=1; i<=n; i++) read(px[i]), read(py[i]);
}

ll dis(ll x, ll y)
{
	return abs(x) + abs(y);
}

void get_seq(ll x, ll y, ll step, int rem)
{
	if(!step) step = 1;
	ll dr = dis(x-step, y), dl = dis(x+step, y);
	ll du = dis(x, y-step), dd = dis(x, y+step);
	ll mnd = min(min(dl, dr), min(dd, du));
	if(!rem) putchar('\n');
	else if(mnd == dr) putchar('R'), get_seq(x-step, y, step/2, rem-1);
	else if(mnd == dl) putchar('L'), get_seq(x+step, y, step/2, rem-1);
	else if(mnd == du) putchar('U'), get_seq(x, y-step, step/2, rem-1);
	else if(mnd == dd) putchar('D'), get_seq(x, y+step, step/2, rem-1);
	else assert(0);
}

void work()
{
	bool tag = (px[1]&1) ^ (py[1]&1);
	int step = tag ? 31 : 32;
	for(int i=2; i<=n; i++)
		if(((px[i]&1)^(py[i]&1)) != tag)
			puts("-1"), exit(0);
	printf("%d\n", step);
	for(int i=30; i>=0; i--) printf("%d ", mov(i));
	if(!tag) printf("%d", mov(0));
	putchar('\n');
	for(int i=1; i<=n; i++) get_seq(px[i], py[i], mov(30), step);
}

int main()
{
	input();
	work();
	return 0;
}