#include <bits/stdc++.h>

using namespace std;

const int MX = 100005;
const int MOD = 1000000007;

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

int n;
char str[MX];
int f[MX], s[MX];
int nxt[MX];

int main()
{
	scanf("%s", str+1);
	n = strlen(str+1);
	bool con = 0;
	for(int i=2; i<=n; i++)
		if(str[i] == str[i-1])
			con = 1;
	if(!con) puts("1");
	else
	{
		nxt[n+1] = n+1;
		for(int i=n; i>=1; i--)
			nxt[i] = (str[i]==str[i+1]) ? i+1 : nxt[i+1];
		f[0] = 1;
		for(int i=0; i<n; i++)
		{
			f[i+1] = (f[i+1] + f[i]) % MOD;
			f[nxt[i+1]] = (f[nxt[i+1]] + f[i]) % MOD;
			//if the sum of subsequence between i and nxt[i] is 0,
			//it means that we add the contribution of i to the neares
			//j which i<j and sum[i...j]!=0, by repeatedly jumping nxt[].
			//the subsequence s[i...nxt[i]] can always be eliminated by canceling characters with neibours.
			//it can be proved that one can never construct a input such that nxt[nxt[...[i]]] is not the nearest one.
			//the meaning of nxt[] is explained in the tutorial.
		}
		int ans = 0;
		for(int i=n; i>=1; i--)
		{
			s[i] = (s[i+1] + str[i+1] - 'a' + 1) % 3;
			if(s[i] == 0) ans = (ans + f[i]) % MOD;
		}
		printf("%d\n", ans);
	}
	return 0;
}