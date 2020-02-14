#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define maxn 1005
typedef long long ll;
const ll mod = 1e9 + 7;
ll ans;
int n, k;
char s[maxn];
int f[maxn];
ll c[maxn][maxn], fac[maxn], inv[maxn];

ll quickpow(ll p, ll k)
{
	ll res = 1;
	while (k)
	{
		if (k & 1)
			res = (res * p) % mod;
		p = (p * p) % mod;
		k >>= 1;
	}
	return res;
}
void check(int len, int low)
{
	int cnt1 = 0, cnt2 = 0, temp1 = 0, temp2 = 0;
	for (int i = 1; i <= k; i++)
	{
		if (s[i] == 'r' && cnt1 < len)
		{
			cnt1++;
			temp1 += (f[cnt1] != 1);
		}
		else if (s[i] == 'b' && temp1)
		{
			temp1--;
			cnt2++;
			temp2 += (f[cnt2] - 2);
		}
		else if (temp2)
			temp2--;
	}

	if (cnt1 < len || temp1 || temp2) return;


	ll res = fac[len];
	for (int i = 1; i <= len; i++)
	{
		int j = i;
		while (f[j + 1] == f[i] && j < len) j++;
		res = (res * inv[j - i + 1]) % mod;
		i = j;
	}
	ll sz = len + 1;
	for (int i = 1; i <= len; i++) sz += (f[i] * 2 - 1);

	/*if(res == 2)
	{
		for(int i=1; i<=len; i++) cout<<f[i]<<" "; cout<<endl;
	}*/
	ans += (res * c[n - low + sz - 1][sz - 1]) % mod;
	ans %= mod;
}
void dfs(int now, int len, int low)
{
	if (low > n) return;
	check(len - 1, low);
	for (int i = now; i >= 1; i--)
	{
		f[len] = i;
		dfs(i, len + 1, low + (max(2 * i - 3, 1)) + (len != 1));
	}
}
int main()
{
	scanf("%d%d%s", &n, &k, s + 1);
	for (int i = 0; i <= 300; i++)
	{
		c[i][0] = c[i][i] = 1;
		for (int j = 1; j <= i - 1; j++)
			c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
	}
	inv[0] = fac[0] = 1;
	for (int i = 1; i <= 300; i++)
		fac[i] = (fac[i - 1] * i) % mod, inv[i] = (quickpow(fac[i], mod - 2));
	dfs(70, 1, 0);
	printf("%lld\n", ans);

	return 0;
}
