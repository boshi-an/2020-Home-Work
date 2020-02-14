#include <bits/stdc++.h>

using namespace std;

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

typedef long long ll;
typedef long double ldb;

const ll MOD = 1000000007;
const int MX = 1000005;

struct vec
{
	ll x, y;

	vec (const ll &x0 = 0, const ll &y0 = 0) : x(x0), y(y0) {}

	vec operator + (const vec &t) const {return vec((x+t.x)%MOD, (y+t.y)%MOD);}
	vec operator - (const vec &t) const {return vec((x-t.x)%MOD, (y-t.y)%MOD);}
	vec operator * (const ll &t) const {return vec((x*t)%MOD, (y*t)%MOD);}
};

struct dvec
{
	ldb x, y;

	dvec (const ldb &x0 = 0, const ldb &y0 = 0) : x(x0), y(y0) {}

	dvec operator + (const dvec &t) const {return dvec(x+t.x, y+t.y);}
	dvec operator - (const dvec &t) const {return dvec(x-t.x, y-t.y);}
	dvec operator * (const ldb &t) const {return dvec(x*t, y*t);}
};

ll crs(const vec &a, const vec &b)
{
	return (a.x*b.y - a.y*b.x)%MOD;
}

ldb crs(const dvec &a, const dvec &b)
{
	return a.x*b.y - a.y*b.x;
}

int n;
vec pos[MX];
vec sum[MX];
ll ner[MX], neri[MX];
dvec dpos[MX];
dvec dsum[MX];
ldb dner[MX], dneri[MX];

void input()
{
	read(n);
	for(int i=1; i<=n; i++)
	{
		read(pos[i].x), read(pos[i].y);
		pos[n+i] = pos[i];
		dpos[i].x = pos[i].x, dpos[i].y = pos[i].y;
		dpos[n+i] = dpos[i];
	}
}

ll work()
{
	for(int i=1; i<=n*2; i++)
	{
		sum[i] = sum[i-1] + pos[i];
		ner[i] = (ner[i-1] + crs(pos[i], pos[i-1]))%MOD;
		neri[i] = (neri[i-1] + crs(pos[i], pos[i-1])*i)%MOD;
		dsum[i] = dsum[i-1] + dpos[i];
		dner[i] = dner[i-1] + crs(dpos[i], dpos[i-1]);
		dneri[i] = dneri[i-1] + crs(dpos[i], dpos[i-1])*i;
	}
	ll ret = 0;
	ldb dtot = dner[n+1];
	int l = 1;
	for(int i=n+1; i<=n*2; i++)
	{
		while((dner[i]-dner[l+1]+crs(dpos[l+1], dpos[i]))*2 >= dtot) l++;
		int y = i-n;
		int num = l-y-1;
		ret += 2*(neri[l]-neri[y+1]) + (-num-2*y-4)*(ner[l]-ner[y+1]);// - num*crs(pos[y+1], pos[i]);
		ret += 2*crs(sum[l]-sum[y+1], pos[i]) - num*crs(pos[y+1], pos[i]);
		ret += num*(ner[i]-ner[l]);
		ret %= MOD;
		//cout<<i<<" "<<l<<endl;
	}
	return (ret+MOD)%MOD;
}

int main()
{
	input();
	ll ans = 0;
	ans += work();
	//reverse(pos+1, pos+n*2+1);
	//for(int i=1; i<=n*2; i++) pos[i] = pos[i]*(-1);
	//ans += work();
	printf("%lld\n", ans);
	return 0;
}
