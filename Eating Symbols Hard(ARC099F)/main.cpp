#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD1 = 998244353;
const ll MOD2 = 1000000009;
const int MX = 250005;
const ll R1 = 123123;
const ll IR1 = 981323583;
const ll R2 = 321321;
const ll IR2 = 234033881;

ll qpow(ll x, ll t, ll p)
{
	ll ans = 1;
	while(t)
	{
		if(t & 1) ans = ans*x % p;
		x = x*x % p;
		t >>= 1;
	}
	return ans;
}

ll inv(ll x, ll p)
{
	return qpow(x, p-2, p);
}

struct NUM
{
	ll x, y;

	NUM (const ll &x0 = 0, const ll &y0 = 0) : x(x0), y(y0) {}
	NUM operator + (const NUM &t) const {return NUM((x+t.x)%MOD1, (y+t.y)%MOD2);}
	NUM operator - (const NUM &t) const {return NUM((x-t.x+MOD1)%MOD1, (y-t.y+MOD2)%MOD2);}
	NUM operator * (const NUM &t) const {return NUM((x*t.x)%MOD1, (y*t.y)%MOD2);}
	bool operator == (const NUM &t) const {return x==t.x && y==t.y;}
	bool operator < (const NUM &t) const {return (x!=t.x) ? (x<t.x) : (y<t.y);}
};

int n;
char str[MX];

void input()
{
	scanf("%d", &n);
	scanf("%s", str+1);
}

NUM con[MX], sum[MX];
map<NUM, int> hav;

void work()
{
	NUM p(1, 1), t(1, 1), r(R1, R2), ir(IR1, IR2);
	for(int i=1; i<=n; i++)
	{
		if(str[i] == '+') con[i] = p;
		else if(str[i] == '-') con[i] = NUM(0, 0) - p;
		else if(str[i] == '>') p = p * r;
		else p = p * ir;
		sum[i] = sum[i-1] + con[i];
		hav[sum[i]]++;
	}
	ll ans = 0;
	for(int i=1; i<=n; i++)
	{
		ans += hav[sum[n]*t+sum[i-1]];
		if(str[i] == '>') t = t * r;
		else if(str[i] == '<') t = t * ir;
		hav[sum[i]]--;
	}
	printf("%lld\n", ans);
}

int main()
{
	input();
	work();
	return 0;
}