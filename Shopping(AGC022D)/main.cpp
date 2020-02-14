#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 300003;

template <typename T> void read(T &x)
{
	x = 0; char c = getchar(); bool f = 0;
	while(!isdigit(c) && c!='-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(isdigit(c)) x = x*10+c-'0', c = getchar();
	if(f) x = -x;
}

int n, len;
int x[MX], t[MX], l[MX], r[MX];

void input()
{
	read(n), read(len), len *= 2;
	for(int i=1; i<=n; i++) read(x[i]);
	for(int i=1; i<=n; i++) read(t[i]);
}

void work()
{
	ll ans = len;
	for(int i=1; i<=n; i++)
	{
		if(t[i]%len == 0) ans += t[i];
		else
		{
			ans += 1ll*((t[i]-1)/len+1)*len;
			if(t[i]%len <= x[i]*2) r[i] = 1;
			if(t[i]%len <= len-x[i]*2) l[i] = 1;
		}
	}
	int lft = 0, rgt = 0, tmp = 0;
	for(int i=1; i<n; i++)
	{
		if(!(t[i]%len)) continue;
		else if(r[i]) tmp += l[i], rgt++;
		else lft += l[i];
		while(rgt-lft < 2*tmp)
		{
			if(tmp) tmp--;
			else lft--;
		}
	}
	ans -= 1ll*l[n]*len;
	printf("%lld\n", ans - 1ll*lft*len - 1ll*tmp*len);
}

int main()
{
	input();
	work();
	return 0;
}