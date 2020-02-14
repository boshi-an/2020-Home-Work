#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 505;

template<typename T> void read(T &x)
{
	x = 0;
	char c = getchar();
	bool f = 0;
	while(!isdigit(c) && c!='-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(isdigit(c)) x = x*10+c-'0', c = getchar();
	if(f) x = -x;
}

struct NODE
{
	int l, r, typ;

	NODE (const int &l0 = 0, const int &r0 = 0) : l(l0), r(r0) {typ = (l0>=1);}

	int key() const {return typ ? l*1000+r : r*1000;}

	bool operator < (const NODE &t) const {return key() < t.key();}
};

int n;
ll mod;
NODE seq[MX];
ll f[MX][MX];
int t1[MX], t2[MX];

ll calc(int k)
{
	memset(f, 0, sizeof(f));
	f[0][0] = 1;
	for(int i=1; i<=n*2; i++)
	{
		for(int j=0; j<=t2[i]&&j<=k; j++)
		{
			if(seq[i].l)
			{
				f[i][j] = f[i-1][j] * (seq[i].r - (t1[2*n] + t2[i-1] + (k-j))) % mod;
				if(j) f[i][j] = (f[i][j] + f[i-1][j-1] * (seq[i].l - (t1[i-1] + (j-1)))) % mod;
			}
			else
			{
				f[i][j] = f[i-1][j] * (seq[i].r - (t1[i-1] + j)) % mod;
			}
		}
	}
	return f[n*2][k];
}

int main()
{
	read(n), read(mod);
	int l = n*2-1, r = n*2-1;
	for(int i=0; i<n*2; i++)
	{
		while(l>=0 && l*l+i*i>=n*n) l--;
		while(r>=0 && r*r+i*i>4*n*n) r--;
		seq[i+1] = NODE(l+1, r+1);
	}
	sort(seq+1, seq+n*2+1);
	for(int i=1; i<=n*2; i++)
	{
		if(seq[i].l) t2[i]++;
		else t1[i]++;
		t1[i] += t1[i-1];
		t2[i] += t2[i-1];
	}
	ll ans = 0;
	for(int i=0; i<=n; i++)
	{
		if(i&1) ans -= calc(i);
		else ans += calc(i);
	}
	printf("%lld\n", (ans%mod+mod) % mod);
	return 0;
}