#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 603;
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

int n, k;
ll f[MX][MX], way[MX];
int mnid[MX][MX], mxid[MX][MX];
int sum[MX];

int main()
{
	read(n), read(k);
	memset(mnid, 0x3f, sizeof(mnid));
	memset(mxid, 0x00, sizeof(mxid));
	for(int i=1; i<=k; i++)
	{
		int a, b;
		read(a), read(b);
		mnid[a][a] = mxid[a][a] = b;
		mnid[b][b] = mxid[b][b] = a;
		sum[a]++, sum[b]++;
	}
	for(int i=1; i<=n*2; i++) sum[i] += sum[i-1];
	for(int i=1; i<=n*2; i++)
		for(int j=i+1; j<=n*2; j++)
		{
			mnid[i][j] = min(mnid[i][j-1], mnid[j][j]);
			mxid[i][j] = max(mxid[i][j-1], mxid[j][j]);
		}
	way[0] = 1;
	for(int i=2; i<=n*2; i++) way[i] = way[i-2] * (i-1) % MOD;
	ll ans = 0;
	for(int i=1; i<=n*2; i++)
	{
		for(int l=1; l+i-1<=n*2; l++)
		{
			int r = l+i-1;
			if(mnid[l][r]<l || mxid[l][r]>r) continue;
			int num = (r-l+1) - (sum[r]-sum[l-1]);
			if(num & 1) continue;
			f[l][r] = way[num];
			for(int j=l; j<r; j++)
			{
				int rem = (r-j) - (sum[r]-sum[j]);
				if(rem&1) continue;
				else if(mnid[j+1][r]<=j || mxid[j+1][r]>r) continue;
				else f[l][r] = (f[l][r] - f[l][j]*way[rem] + MOD*MOD) % MOD;
			}
			ans = (ans + f[l][r]*way[n*2-k*2-num]) % MOD;
			//cout<<l<<" "<<r<<" "<<f[l][r]<<" "<<way[n*2-k*2-num]<<endl;
		}
	}
	printf("%lld\n", ans);
	//printf("%lld\n", f[1][n*2]);
	return 0;
}
