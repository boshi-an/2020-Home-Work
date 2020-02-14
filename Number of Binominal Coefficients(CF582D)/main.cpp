#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;
const int MX = 4005;

template<typename T> void add(T &x, const T &y)
{
	x += y;
	x %= MOD;
}

ll p, m;
int n;
string str;
vector<ll> src, lim;
ll f[2][MX+1][2][2];

void input()
{
	cin >> p >> m >> str;
}

ll get_small(ll t)
{
	if(t <= p) return (1+t) * t / 2 % MOD;
	else return (p*p - get_small(2*p-t-1)) % MOD;
}

void work()
{
	for(auto c : str) src.push_back(c-'0');
	reverse(src.begin(), src.end());
	while(src.size())
	{
		ll rem = 0;
		for(int i=src.size()-1; i>=0; i--)
		{
			src[i] += rem*10;
			rem = src[i]%p;
			src[i] /= p;
		}
		while(!src.empty() && !src.back()) src.pop_back();
		lim.push_back(rem);
	}
	reverse(lim.begin(), lim.end());	//h:0, l:size()-1
	int now = 0;
	f[now][0][1][0] = 1;
	for(auto x : lim)
	{
		memset(f[now^1], 0, sizeof(f[now^1]));
		for(int b=0; b<2; b++)
		{
			for(int j=0; j<MX; j++)
			{
				add(f[now^1][j][0][b], f[now][j][0][0] * get_small(p-b));
				add(f[now^1][j+1][0][b], f[now][j][0][1] * ((p*p - get_small(p-b)) % MOD));
				add(f[now^1][j][1][b], f[now][j][1][0] * (x-b+1));
				add(f[now^1][j][0][b], f[now][j][1][0] * get_small(x-b));
				add(f[now^1][j+1][1][b], f[now][j][1][1] * (p-1-x+b));
				add(f[now^1][j+1][0][b], f[now][j][1][1] * (get_small(p+x-b) - get_small(p-b) + MOD));
			}
		}
		now ^= 1;
		/*for(int i=0; i<3; i++)
			cout<<i<<" : "<<f[now][i][0][0]<<" "<<f[now][i][0][1]<<" "<<f[now][i][1][0]<<" "<<f[now][i][1][1]<<endl;*/
	}
	ll ans = 0;
	for(int i=m; i<MX; i++)
		add(ans, f[now][i][0][0] + f[now][i][1][0]);
	printf("%lld\n", ans);
	//for(auto x : lim) printf("%d ", x);
	//putchar('\n');
}

int main()
{
	input();
	work();
	return 0;
}