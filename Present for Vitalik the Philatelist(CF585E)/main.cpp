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
	int prm[MX], pnum;
	bool vis[MV];
	int miu[MV];
	
	void sieve()
	{
		miu[1] = 1;
		for(int i=2; i<MV; i++)
		{
			if(!vis[i]) prm[++pnum] = i, miu[i] = -1;
			for(int j=1; j<=pnum; j++)
			{
				if(prm[j]*i >= MV) break;
				vis[prm[j]*i] = 1;
				if(i%prm[j] == 0) break;
				else miu[i*prm[j]] = -miu[i];
			}
		}
	}
} P;

int n;
int val[MX];
int pro[MV], oth[MV];
long long way[MV];
int pw2[MX];

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
	for(int i=1; i<=n; i++) pro[val[i]]++;
	for(int i=1; i<MV; i++)
	{
		for(int j=i*2; j<MV; j+=i) pro[i] += pro[j];
		if(i>1 && P.miu[i] && pro[i]) for(int j=i; j<MV; j+=i) oth[j] -= P.miu[i]*pro[i];
	}
	for(int i=1; i<MV; i++) way[i] = pw2[pro[i]]-1;
	for(int i=MV-1; i>=1; i--) for(int j=i*2; j<MV; j+=i) way[i] -= way[j];
	int ans = 0;
	for(int i=2; i<MV; i++) ans = (ans + way[i]%MOD*(n-oth[i])) % MOD;
	printf("%d\n", (ans+MOD) % MOD);
}

int main()
{
	input();
	work();
	return 0;
}