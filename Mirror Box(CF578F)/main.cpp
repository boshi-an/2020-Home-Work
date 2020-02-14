#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 505;

char mp[MX][MX];
int n, m;
ll mod;

ll qpow(ll x, ll t)
{
	ll ret = 1;
	while(t)
	{
		if(t & 1) ret = ret*x % mod;
		x = x*x % mod;
		t >>= 1;
	}
	return ret;
}

ll inv(ll x)
{
	return qpow(x, mod-2);
}

struct MAT
{
	ll x[MX][MX];
	
	ll gauss(int len)
	{
		ll ret = 1;
		for(int i=1; i<=len; i++)
		{
			for(int j=i+1; j<=len; j++)
				if(x[j][i])
				{
					swap(x[i], x[j]);
					ret *= -1;
					break;
				}
			for(int j=i+1; j<=len; j++)
				if(x[j][i])
				{
					ll mul = (mod*mod - x[j][i]*inv(x[i][i])) % mod;
					for(int k=i; k<=len; k++) x[j][k] = (x[j][k] + mul*x[i][k]) % mod;
				}
		}
		return ret;
	}

	ll det(int len)
	{
		ll ret = gauss(len);
		for(int i=1; i<=len; i++) ret = ret*x[i][i] % mod;
		return (ret+mod) % mod;
	}
};

struct UNION
{
	int fa[MX*MX];
	
	void init(int num)
	{
		for(int i=1; i<=num; i++) fa[i] = i;
	}
	
	int id(int x)
	{
		return (fa[x]==x) ? (x) : (fa[x]=id(fa[x]));
	}
};

void input()
{
	scanf("%d%d%lld", &n, &m, &mod);
	for(int i=0; i<n; i++) scanf("%s", mp[i]);
}

bool col(int x, int y)
{
	return (x^y) & 1;
}

int id(int x, int y)
{
	return (x*(m+1)+y)/2 + 1;
}

void work()
{
	static MAT mat;
	static UNION uni;
	static int ind[MX*MX];
	ll ans = 0;
	for(int c=0; c<2; c++)
	{
		memset(&mat, 0, sizeof(mat));
		
		int num = ((n+1)*(m+1)+1-c)/2;
		uni.init(num);
		
		bool fucked = 0;
		
		for(int i=0; i<n; i++)
		{
			for(int j=0; j<m; j++)
			{
				int grp_a, grp_b;
				if(mp[i][j]=='/' && col(i, j+1)==c) grp_a = uni.id(id(i, j+1)), grp_b = uni.id(id(i+1, j));
				else if(mp[i][j]=='\\' && col(i, j)==c) grp_a = uni.id(id(i+1, j+1)), grp_b = uni.id(id(i, j));
				else continue;
				if(grp_a == grp_b) fucked = 1;
				else uni.fa[grp_a] = grp_b;
			}
		}
		
		if(fucked) continue;
		
		int ind_siz = 0;
		for(int i=1; i<=num; i++)
			if(uni.id(i) == i)
				ind[i] = ++ind_siz;
		
		if(ind_siz > MX) continue;
		
		for(int i=0; i<n; i++)
		{
			for(int j=0; j<m; j++)
			{
				if(mp[i][j] == '*')
				{
					int a, b;
					if(col(i, j) == c) a = id(i, j), b = id(i+1, j+1);
					else a = id(i, j+1), b = id(i+1, j);
					a = ind[uni.id(a)];
					b = ind[uni.id(b)];
					mat.x[a][a]++;
					mat.x[b][b]++;
					mat.x[a][b]--;
					mat.x[b][a]--;
				}
			}
		}
		
		ans = (ans + mat.det(ind_siz-1)) % mod;
	}
	printf("%lld\n", ans);
}

int main()
{
	input();
	work();
	return 0;
}