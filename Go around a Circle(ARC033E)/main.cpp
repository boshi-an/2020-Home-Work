#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 200005;
const ll MOD = 1000000007;

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

int n, m, nR, nB;
char str[MX];
ll f[MX], sum[2][MX];

vector<int> divide(int x)
{
	vector<int> ret;
	for(int i=1; i<=x; i++)
		if(x%i == 0)
			ret.push_back(i);
	return ret;
}

int main()
{
	ll ans = 0;
	read(n), read(m);
	scanf("%s", str+1);
	for(int i=1; i<=m; i++)
		if(str[i] == 'R') nR++;
		else nB++;
	vector<int> dvs = divide(n);
	if(!nR || !nB)
	{
		f[0] = 1;
		sum[0][0] = sum[0][1] = 1;
		for(int i=2; i<=n; i++)
		{
			f[i] = sum[0][i-2];
			sum[0][i] = (sum[0][i-1] + f[i]) % MOD;
		}
		ans = 1;
		for(int i=1; i<n; i++) ans = (ans+f[n-i-1]*(i+1)) % MOD;
	}
	else
	{
		int len = n-1;
		int pre = 0;
		while(str[pre+1] == str[1]) pre++;
		/*if(pre&1) cmin(len, pre);		//the worst case isn't when the initial position is in the middle!
		else cmin(len, pre*2-1);*/
		cmin(len, pre|1);
		int cur = 0;
		for(int i=pre+1; i<=m; i++)
		{
			if(str[i] != str[1])
			{
				if(cur & 1) cmin(len, cur);
				cur = 0;
			}
			else cur++;
		}
		f[0] = sum[0][0] = 1;
		for(int i=1; i<=n; i++)
		{
			f[i] = (((i-2>=0) ? (sum[i&1][i-2]) : (0)) - ((i-2-len>=0) ? (sum[i&1][i-2-len]) : (0)) + MOD) % MOD;
			sum[i&1][i] = (sum[i&1][i-1] + f[i]) % MOD;
			sum[i&1^1][i] = sum[i&1^1][i-1];
		}
		for(int i=1; i<=len; i+=2) ans = (ans+f[n-i-1]*(i+1)) % MOD;
	}
	printf("%lld\n", ans);
	return 0;
}