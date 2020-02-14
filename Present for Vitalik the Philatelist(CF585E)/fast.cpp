#include <bits/stdc++.h>

using namespace std;

const int MX = 500005;
const int MV = 10000005;
const int MOD = 1000000007;

template<typename T> void cmax(T &x, const T &y)
{
	if(y > x) x = y;
}

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

struct PRM
{
	int prm[678900], pnum;
	bool vis[MV];
	int miu[MV], mnd[MV];
	
	void sieve()
	{
		miu[1] = mnd[1] = 1;
		for(int i=2; i<MV; i++)
		{
			if(!vis[i]) prm[++pnum] = i, miu[i] = -1, mnd[i] = i;
			for(int j=1; j<=pnum; j++)
			{
				if(prm[j]*i >= MV) break;
				vis[prm[j]*i] = 1;
				mnd[i*prm[j]] = prm[j];
				if(i%prm[j] == 0) break;
				else miu[i*prm[j]] = -miu[i];
			}
		}
	}

	vector<int> get_base(int n)
	{
		vector<int> ret;
		ret.push_back(1);
		while(n != 1)
		{
			if(n%(mnd[n]*mnd[n]) == 0) n /= mnd[n];
			else
			{
				auto t = ret.size();
				for(int i=0; i!=t; i++) ret.push_back(ret[i]*mnd[n]);
				n /= mnd[n];
			}
		}
		return ret;
	}
} P;

int n;
int val[MX];
int pw2[MX];
int num[MV];

void input()
{
	read(n);
	for(int i=1; i<=n; i++) read(val[i]);
	pw2[0] = 1;
	for(int i=1; i<=n; i++) pw2[i] = pw2[i-1]*2 % MOD;
}

void work()
{
	P.sieve();
	for(int i=1; i<=n; i++)
	{
		auto base = P.get_base(val[i]);
		for(auto x : base) num[x]++;
	}
	int ans = 0, way = 0;
	for(int i=2; i<MV; i++) way = (way - (pw2[num[i]]-1)*P.miu[i]) % MOD;
	for(int i=1; i<=n; i++)
	{
		auto base = P.get_base(val[i]);
		int now_way = way;
		for(auto x : base)
			if(x > 1)
				now_way = (now_way + (pw2[num[x]]-1)*P.miu[x] - (pw2[num[x]-1]-1)*P.miu[x]) % MOD;
		//cout<<val[i]<<" "<<now_way<<endl;
		ans = (ans + now_way) % MOD;
		for(auto x : base)
			if(x != 1)
				ans = (ans + (pw2[num[x]-1]-1)*P.miu[x]) % MOD;
	}
	printf("%d\n", (ans+MOD) % MOD);
}

int main()
{
	input();
	work();
	return 0;
}