#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 100005;
const ll oo = 4444444444444444444;

template<typename T> void cmax(T &x, const T &y)
{
	if(y > x) x = y;
}

template<typename T> void cmin(T &x, const T &y)
{
	if(y < x) x = y;
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

int n;
ll pos[MX][3], ansp[3];

void input()
{
	read(n);
	for(int i=1; i<=n; i++)
	{
		read(pos[i][0]);
		read(pos[i][1]);
		read(pos[i][2]);
	}
}

ll up_to_parity(ll a, ll p)
{
	return a + ((a&1)^p);
}

ll dn_to_parity(ll a, ll p)
{
	return a - ((a&1)^p);
}

bool check(ll d)
{
	ll la = -oo, ra = +oo, lb = -oo, rb = +oo, lc = -oo, rc = +oo, ld = -oo, rd = +oo;
	for(int i=1; i<=n; i++)
	{
		cmax(la, +pos[i][0]+pos[i][1]-pos[i][2]-d);
		cmin(ra, +pos[i][0]+pos[i][1]-pos[i][2]+d);
		cmax(lb, +pos[i][0]-pos[i][1]+pos[i][2]-d);
		cmin(rb, +pos[i][0]-pos[i][1]+pos[i][2]+d);
		cmax(lc, -pos[i][0]+pos[i][1]+pos[i][2]-d);
		cmin(rc, -pos[i][0]+pos[i][1]+pos[i][2]+d);
		cmax(ld, +pos[i][0]+pos[i][1]+pos[i][2]-d);
		cmin(rd, +pos[i][0]+pos[i][1]+pos[i][2]+d);
	}
	for(int p=0; p<=1; p++)
	{
		ll pla = up_to_parity(la, p), pra = dn_to_parity(ra, p);
		ll plb = up_to_parity(lb, p), prb = dn_to_parity(rb, p);
		ll plc = up_to_parity(lc, p), prc = dn_to_parity(rc, p);
		ll pld = up_to_parity(ld, p), prd = dn_to_parity(rd, p);
		ll sum_l = pla + plb + plc;
		ll sum_r = pra + prb + prc;
		if(sum_l>prd || sum_r<pld || pla>pra || plb>prb || plc>prc || pld>prd) continue;
		else
		{
			ll a = up_to_parity(la, p), b = up_to_parity(lb, p), c = up_to_parity(lc, p);
			if(a+b+c < pld)
			{
				a += min(dn_to_parity(ra, p)-a, pld-(a+b+c));
				b += min(dn_to_parity(rb, p)-b, pld-(a+b+c));
				c += min(dn_to_parity(rc, p)-c, pld-(a+b+c));
			}
			ansp[0] = (a+b) / 2;
			ansp[1] = (a+c) / 2;
			ansp[2] = (b+c) / 2;
			return true;
		}
	}
	return false;
}

void work()
{
	ll ans = 0;
	if(!check(ans))
	{
		for(int i=61; i>=0; i--)
			if(!check(ans + (1ll<<i)))
				ans |= (1ll<<i);
		check(ans + 1);
		//cout<<ans+1<<endl;
	}
	//else cout<<ans<<endl;
	printf("%lld %lld %lld\n", ansp[0], ansp[1], ansp[2]);
}

int main()
{
	int t;
	read(t);
	while(t--)
	{
		input();
		work();
		//printf("%lld %lld %lld\n", ans[0], ans[1], ans[2]);
	}
	return 0;
}

/*
1
2
5 4 5
3 6 5
*/