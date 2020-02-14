#include <bits/stdc++.h>

using namespace std;

typedef long double ldb;

const int MX = 603;

struct vec
{
	ldb x, y;

	vec (const ldb &x0 = 0 , const ldb &y0 = 0) : x(x0), y(y0) {}
	vec operator + (const vec &t) const {return vec(x+t.x, y+t.y);}
	vec operator - (const vec &t) const {return vec(x-t.x, y-t.y);}
	vec operator * (const ldb &t) const {return vec(x*t, y*t);}
	vec operator / (const ldb &t) const {return vec(x/t, y/t);}
	ldb len2 () const {return x*x + y*y;}
	ldb len () const {return sqrt(len2());}
	vec norm () const {return *this/len();}
	vec rot_90_r () const {return vec(-y, x);}
};

ldb crs(vec a, vec b) {return a.x*b.y - a.y*b.x;}

vec lin_lin_int(vec p1, vec v1, vec p2, vec v2)
{
	assert(fabs(crs(v1, v2)) >= 1e-8);
	ldb k = crs(p2-p1, v2) / crs(v1, v2);
	return p1 + v1*k;
}

int n;
vec pos[MX];
ldb len[MX];
vec ansp1, ansp2, center;

void input()
{
	scanf("%d", &n);
	for(int i=1; i<=n; i++) cin >> pos[i].x >> pos[i].y;
	for(int i=1; i<=n; i++) pos[n+i] = pos[i], center = center + pos[i];
	for(int i=2; i<=n*2; i++) len[i] = len[i-1] + (pos[i]-pos[i-1]).len();
	center = center / n;
}

struct ITV
{
	ldb l, r;

	ITV (const ldb &l0 = 0, const ldb &r0 = 0) : l(l0), r(r0) {}
	bool operator < (const ITV &t) const {return l < t.l;}
};

vec gpos(ldb l)
{
	if(l < -1e9) return pos[1];
	while(l <= 0) l += len[n+1];
	for(int i=1; i<n*2; i++)
		if(l>=len[i] && l<=len[i+1])
		{
			vec tmp = pos[i] + (pos[i+1]-pos[i]).norm()*(l-len[i]);
			return tmp*(1-1e-12) + center*(1e-12);
		}
	assert(0);
}

bool check1(vector<ITV> src)
{
	vector<pair<ldb, int> > seq;
	vector<ITV> itv = src;
	for(auto i : src) itv.push_back(ITV(i.l+len[n+1], i.r+len[n+1]));
	for(auto i : itv)
	{
		seq.push_back(make_pair(i.l, -1));
		seq.push_back(make_pair(i.r, +1));
	}
	sort(seq.begin(), seq.end());
	int sum = src.size();
	for(auto i : seq)
	{
		if(!sum)
		{
			ansp2 = gpos(i.first);
			return true;
		}
		sum += i.second;
	}
	if(!sum) return true;
	else return false;
}

bool check2(ldb r)
{
	vector<ITV> itv;
	for(int i=1; i<=n; i++)
	{
		vec tov = pos[i+1] - pos[i];
		vec mov = tov.rot_90_r().norm();
		vec src = pos[i]+mov*r;
		ldb l = -1e10, r = +1e10;
		for(int j=1; j<n*2; j++)
		{
			if(crs(pos[j]-src, tov)>=0 && crs(pos[j+1]-src, tov)<=0 && fabs(crs(pos[j+1]-pos[j], tov))>1e-8)
			{
				r = len[j] + (lin_lin_int(src, tov, pos[j], pos[j+1]-pos[j])-pos[j]).len();
				break;
			}
		}
		for(int j=1; j<n*2; j++)
		{
			if(crs(pos[j]-src, tov)<=0 && crs(pos[j+1]-src, tov)>=0 && fabs(crs(pos[j+1]-pos[j], tov))>1e-8)
			{
				l = len[j] + (lin_lin_int(src, tov, pos[j], pos[j+1]-pos[j])-pos[j]).len();
				break;
			}
		}
		while(l > r) l -= len[n+1];
		itv.emplace_back(ITV(l, r));
	}
	auto inside = [=](ldb t, ITV iv)
	{
		if(iv.l<=t && t<=iv.r) return true;
		else if(iv.l<=t+len[n+1] && t+len[n+1]<=iv.r) return true;
		else if(iv.l<=t-len[n+1] && t-len[n+1]<=iv.r) return true;
		else return false;
	};
	for(auto i : itv)
	{
		vector<ITV> tmp;
		for(auto j : itv)
			if(!inside(i.l, j))
				tmp.push_back(j);
		if(check1(tmp))
		{
			ansp1 = gpos(i.l);
			return true;
		}
	}
	return false;
}

void work()
{
	check2(1);
	ldb l = 0, r = 50005, mid;
	for(int i=1; i<=60; i++)
	{
		mid = (l+r) / 2;
		if(check2(mid)) r = mid;
		else l = mid;
	}
	check2(mid+1e-9);
	cout.setf(ios::fixed);
	cout << setprecision(8) << mid+1e-9 << endl;
	cout << setprecision(8) << ansp1.x << " " << ansp1.y << endl;
	cout << setprecision(8) << ansp2.x << " " << ansp2.y << endl;
}

int main()
{
	input();
	work();
	return 0;
}
