#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 77;
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
char str[MX];
ll inv[MX*3], fac[MX*3], faci[MX*3];

void init()
{
	inv[0] = fac[0] = faci[0] = 1;
	inv[1] = fac[1] = faci[1] = 1;
	for(int i=2; i<MX*3; i++)
	{
		inv[i] = (MOD*MOD - (MOD/i) * inv[MOD%i]) % MOD;
		fac[i] = fac[i-1] * i % MOD;
		faci[i] = faci[i-1] * inv[i] % MOD;
	}
}

ll binom(int x, int y)
{
	if(x<0 || y<0 || x<y) return 0;
	else return fac[x] * faci[y] % MOD * faci[x-y] % MOD;
}

void input()
{
	read(n), read(k);
	scanf("%s", str+1);
}

vector<vector<int> > sta;

void dfs(vector<int> cur)
{
	int len = cur.size()-1;
	for(auto i : cur)
		if(i == 0) len++;
		else len += i*2-1;
	if(len > n) return;
	sta.push_back(cur);
	for(int i=0; i<=(cur.size() ? cur.back() : (n+1)/2); i++)
	{
		vector<int> tmp = cur;
		tmp.push_back(i);
		dfs(tmp);
	}
}

bool check(vector<int> s)
{
	int sum[MX];
	fill(sum+1, sum+k+1, 1);
	vector<int> can;
	int rem = 0, r = 1, b = 1, bpos[MX];
	for(int i=0; i<s.size(); i++)
	{
		if(s[i])
		{
			while(r<=k && str[r]!='r') r++;
			if(r > k) return false;
			while(b<=k && (str[b]!='b' || b<=r)) b++;
			if(b > k) return false;
			sum[r] = sum[b] = 0;
			bpos[i] = b;
			r++, b++;
		}
	}
	for(int i=0; i<s.size(); i++)
	{
		if(!s[i])
		{
			while(r<=k && str[r]!='r') r++;
			if(r > k) return false;
			sum[r] = 0;
			r++;
		}
	}
	for(int i=k-1; i>=1; i--) sum[i] += sum[i+1];
	for(int i=0; i<s.size(); i++) if(s[i]) can.push_back(sum[bpos[i]]);
	reverse(can.begin(), can.end());
	while(s.size() && !s.back()) s.pop_back();
	reverse(s.begin(), s.end());
	int tmp = 0;
	for(int i=0; i<can.size(); i++)
	{
		tmp += max(s[i]-1, 0);
		if(tmp > can[i]) return false;
	}
	return true;
}

ll calc(vector<int> s)
{
	ll ret = fac[s.size()];
	int cnt = 1;
	for(int i=1; i<s.size(); i++)
		if(s[i] != s[i-1])
			ret = ret*faci[cnt] % MOD, cnt = 1;
		else cnt++;
	ret = ret*faci[cnt] % MOD;
	int up = n+1, dn = 0;
	for(auto v : s)
	{
		dn += 2*v+2;
		up += (v>=1)*2;
	}
	return ret * binom(up, dn) % MOD;
}

void work()
{
	ll ans = 0;
	dfs(vector<int>());
	for(auto s : sta)
		if(check(s))
			ans = (ans + calc(s)) % MOD;
	printf("%lld\n", ans);
}

int main()
{
	init();
	input();
	work();
	return 0;
}