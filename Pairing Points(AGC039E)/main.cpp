#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 41;

template <typename T> void read(T &x)
{
	x = 0; char c = getchar(); bool f = 0;
	while(!isdigit(c) && c!='-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(isdigit(c)) x = x*10+c-'0', c = getchar();
	if(f) x = -x;
}

int n;
int w[MX][MX];
char str[MX];

void input()
{
	read(n);
	for(int i=1; i<=n*2; i++)
	{
		scanf("%s", str+1);
		for(int j=1; j<=n*2; j++) w[i][j] = str[j]-'0';
	}
}

bool visf[MX][MX][MX];
ll valf[MX][MX][MX];

bool visg[MX][MX][MX][MX];
ll valg[MX][MX][MX][MX];

bool vish[MX][MX][MX];
ll valh[MX][MX][MX];

ll getf(int l, int r, int i);

ll getg(int p, int y, int i, int r)
{
	if(visg[p][y][i][r]) return valg[p][y][i][r];
	ll ret = 0;
	for(int q=i; q<y; q++) ret += getf(p+1, q, i) * getf(q+1, r, y);
	visg[p][y][i][r] = 1;
	valg[p][y][i][r] = ret;
	return ret;
}

ll geth(int l, int p, int y)
{
	if(vish[l][p][y]) return valh[l][p][y];
	ll ret = 0;
	for(int x=l; x<=p; x++)
		if(w[x][y])
			ret += getf(l, p, x);
	vish[l][p][y] = 1;
	valh[l][p][y] = ret;
	return ret;
}

ll getf(int l, int r, int i)
{
	if(l == r) return 1;
	else if(l==i || r==i) return 0;
	else if((r-l)&1) return 0;
	if(visf[l][r][i]) return valf[l][r][i];
	ll ret = 0;
	for(int p=l; p<i; p++)
		for(int y=r; y>i; y--)
			ret += geth(l, p, y) * getg(p, y, i, r);
	visf[l][r][i] = 1;
	valf[l][r][i] = ret;
	return ret;
}

int main()
{
	input();
	ll ans = 0;
	for(int i=2; i<=n*2; i++)
		if(w[1][i])
			ans += getf(2, n*2, i);
	printf("%lld\n", ans);
	return 0;
}
