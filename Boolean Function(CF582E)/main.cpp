#include <bits/stdc++.h>
#define mov(x) (1<<(x))

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

template <typename T> void add(T &x, const T &y)
{
	x = (x+y) % MOD;
}

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

struct POLY
{
	ll x[mov(16)];

	POLY () {memset(x, 0, sizeof(x));}
};

int n, len;
char str[505];
int constrain[16];

void input()
{
	scanf("%s", str+1);
	len = strlen(str+1);
	read(n);
	memset(constrain, 0xff, sizeof(constrain));
	for(int i=1; i<=n; i++)
	{
		int bit = 0, x;
		for(int j=0; j<4; j++)
		{
			read(x);
			bit |= mov(j)*x;
		}
		read(constrain[bit]);
	}
}

POLY operator & (const POLY &a, const POLY &b)
{
	static ll fa[mov(16)], fb[mov(16)];
	POLY ret;
	memmove(fa, a.x, sizeof(fa));
	memmove(fb, b.x, sizeof(fb));
	for(int i=0; i<16; i++)
		for(int j=0; j<mov(16); j++)
			if(j&mov(i))
				add(fa[j^mov(i)], fa[j]),
				add(fb[j^mov(i)], fb[j]);
	for(int i=0; i<mov(16); i++) ret.x[i] = fa[i] * fb[i] % MOD;
	for(int i=15; i>=0; i--)
		for(int j=mov(16)-1; j>=0; j--)
			if(j&mov(i))
				add(ret.x[j^mov(i)], MOD-ret.x[j]);
	return ret;
}

POLY operator | (const POLY &a, const POLY &b)
{
	static ll fa[mov(16)], fb[mov(16)];
	POLY ret;
	memmove(fa, a.x, sizeof(fa));
	memmove(fb, b.x, sizeof(fb));
	for(int i=0; i<16; i++)
		for(int j=0; j<mov(16); j++)
			if(j&mov(i))
				add(fa[j], fa[j^mov(i)]),
				add(fb[j], fb[j^mov(i)]);
	for(int i=0; i<mov(16); i++) ret.x[i] = fa[i] * fb[i] % MOD;
	for(int i=15; i>=0; i--)
		for(int j=mov(16)-1; j>=0; j--)
			if(j&mov(i))
				add(ret.x[j], MOD-ret.x[j^mov(i)]);
	return ret;
}

POLY operator + (const POLY &a, const POLY &b)
{
	POLY ret;
	for(int i=0; i<mov(16); i++)
		ret.x[i] = (a.x[i]+b.x[i]) % MOD;
	return ret;
}

POLY calc(int l, int r)
{
	POLY ret;
	if(l == r)
	{
		int bit = 0;
		if(str[l] != '?')
		{
			int base, need = 0;
			if(str[l]>='A' && str[l]<='Z')
			{
				base = str[l]-'A';
				need = 1;
			}
			else
			{
				base = str[l]-'a';
				need = 0;
			}
			bit = 0;
			for(int i=0; i<16; i++)
				if(((i>>base) & 1) == need)
					bit |= mov(i);
			ret.x[bit]++;
		}
		else
		{
			for(int base=0; base<4; base++)
			{
				for(int need=0; need<2; need++)
				{
					bit = 0;
					for(int i=0; i<16; i++)
						if(((i>>base) & 1) == need)
							bit |= mov(i);
					ret.x[bit]++;
				}
			}
		}
	}
	else
	{
		int sum = 0;
		for(int i=l; i<=r; i++)
		{
			if(str[i] == '(') sum++;
			else if(str[i] == ')') sum--;
			if(!sum)
			{
				POLY subl = calc(l+1, i-1), subr = calc(i+3, r-1);
				if(str[i+1] == '&') ret = subl & subr;
				else if(str[i+1] == '|') ret = subl | subr;
				else ret = (subl|subr) + (subl&subr);
				break;
			}
		}
	}
	return ret;
}

void work()
{
	POLY res = calc(1, len);
	ll ans = 0;
	for(int i=0; i<mov(16); i++)
	{
		bool cant = 0;
		for(int j=0; j<16; j++)
			if(constrain[j] != -1)
				if(((i>>j)&1) != constrain[j])
					cant = 1;
		if(!cant && res.x[i]) add(ans, res.x[i]);
	}
	printf("%lld\n", ans);
}

int main()
{
	input();
	work();
	return 0;
}