#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 2000002;

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

struct TRI
{
	ll r, x, y;

	TRI (const ll &r0 = 0, const ll &x0 = 0, const ll &y0 = 0) : r(r0), x(x0), y(y0) {}
	TRI operator - (const TRI &t) const {return TRI(r-t.r, x-t.x, y-t.y);}
	ll len () const {return abs(x)+abs(y);}
};

bool test_case_33;
int n, len;
vector<TRI> pos[MX];

void fuck(const char *str)
{
	puts("NO");
	//if(test_case_33) cout << str << endl;
	exit(0);
}

ll updiv(ll u, ll d)
{
	assert(d > 0);
	if(u < 0) return u/d;
	else return (u-1)/d+1;
}

ll dndiv(ll u, ll d)
{
	assert(d > 0);
	if(u < 0) return (u+1)/d-1;
	else return u/d;
}

void input()
{
	read(n), read(len);
	pos[0].push_back(TRI(0, 0, 0));
	for(int i=0; i<n; i++)
	{
		ll t, x, y;
		read(t), read(x), read(y);
		if((t&1) != ((x&1)^(y&1))) fuck("cannot reach at all");
		pos[t%len].push_back(TRI(t/len, x, y));
	}
	if(n==1000 && len==2000000) test_case_33 = 1;
}

void print_seq(TRI t)
{
	for(int i=0; i<t.r; i++)
	{
		if(t.x > 0) putchar('R'), t.x--;
		else if(t.x < 0) putchar('L'), t.x++;
		else if(t.y > 0) putchar('U'), t.y--;
		else putchar('D'), t.y++;
	}
	//assert(t.x==0 && t.y==0);
}

void print_by_dxdy(ll dx, ll dy)
{
	vector<TRI> tar;
	for(int i=0; i<len; i++)
		for(auto j : pos[i])
			tar.push_back(TRI(i, j.x-dx*j.r, j.y-dy*j.r));
	tar.push_back(TRI(len, dx, dy));
	for(int i=0; i+1<tar.size(); i++)
		if(tar[i+1].r-tar[i].r < (tar[i+1]-tar[i]).len())
		{
			//if(test_case_33) cout<<i<<": "<<dx<<" "<<dy<<" "<<tar[i+1].r-tar[i].r<<" ? "<<tar[i+1].x<<" "<<tar[i].x<<" "<<tar[i+1].y<<" "<<tar[i].y<<endl;
			fuck("dx and dy not fit");
		}
	for(int i=0; i+1<tar.size(); i++) print_seq(tar[i+1]-tar[i]);
	putchar('\n');
}

void work()
{
	ll mndx = -len, mxdx = +len, mndy = -len, mxdy = +len;
	for(int i=0; i<len; i++)
	{
		if(pos[i].size() > 1)
		{
			for(int j=1; j<pos[i].size(); j++)
			{
				if((pos[i][j].x-pos[i][0].x) % (pos[i][j].r-pos[i][0].r)) fuck("can't transist 1");
				if((pos[i][j].y-pos[i][0].y) % (pos[i][j].r-pos[i][0].r)) fuck("can't transist 2");
				ll dx = (pos[i][j].x-pos[i][0].x)/(pos[i][j].r-pos[i][0].r);
				ll dy = (pos[i][j].y-pos[i][0].y)/(pos[i][j].r-pos[i][0].r);
				cmax(mndx, dx-dy);
				cmin(mxdx, dx-dy);
				cmax(mndy, dx+dy);
				cmin(mxdy, dx+dy);
			}
		}
	}
	if(mndx>mxdx || mndy>mxdy) fuck("mn > mx 1");
	else if(mndx==mxdx && mndy==mxdy) print_by_dxdy((mndx+mndy)/2, (mndy-mndx)/2);
	else
	{
		for(int i=0; i<len; i++)
		{
			if(pos[i].size())
			{
				int j = i+1;
				while(j<len && !pos[j].size()) j++;
				if(j == len)
				{
					TRI p = pos[i][0];
					ll c = j-i;
					ll lx = updiv(-c+(p.x-p.y), 1+p.r), rx = dndiv(c+(p.x-p.y), 1+p.r);
					cmax(mndx, lx);
					cmin(mxdx, rx);
					ll ly = updiv(-c+(p.x+p.y), 1+p.r), ry = dndiv(c+(p.x+p.y), 1+p.r);
					cmax(mndy, ly);
					cmin(mxdy, ry);
				}
				else
				{
					TRI p1 = pos[i][0], p2 = pos[j][0];
					ll c = j-i, d = (p1.x-p2.x), e = (p1.y-p2.y);
					if(p1.r == p2.r)
					{
						if((p1-p2).len() > c) fuck("can't transist 3");
					}
					else
					{
						if(p1.r > p2.r) swap(p1, p2), d = -d, e = -e;
						ll lx = updiv(-c-(d-e), p2.r-p1.r), rx = dndiv(c-(d-e), p2.r-p1.r);
						cmax(mndx, lx);
						cmin(mxdx, rx);
						ll ly = updiv(-c-(d+e), p2.r-p1.r), ry = dndiv(c-(d+e), p2.r-p1.r);
						cmax(mndy, ly);
						cmin(mxdy, ry);
					}
				}
			}
		}
		if(mndx>mxdx || mndy>mxdy) fuck("mn > mx 2");
		for(ll dx=mndx; dx<=mxdx; dx++)
			for(ll dy=mndy; dy<=mxdy; dy++)
			{
				if((dx+dy) & 1) continue;
				else if((dy-dx) & 1) continue;
				ll x = (dx+dy)/2, y = (dy-dx)/2;
				if((len&1) != ((x&1)^(y&1))) continue;
				else {print_by_dxdy(x, y); return;}
			}
		fuck("none answer found");
	}
}

int main()
{
	input();
	work();
	return 0;
}