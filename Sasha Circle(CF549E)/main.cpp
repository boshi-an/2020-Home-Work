#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-5;

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

struct vec
{
	double x, y;

	vec (const double &x0 = 0, const double &y0 = 0) : x(x0), y(y0) {}
	vec operator + (const vec &t) const {return vec(x+t.x, y+t.y);}
	vec operator - (const vec &t) const {return vec(x-t.x, y-t.y);}
	vec operator * (const double &t) const {return vec(x*t, y*t);}
	double len2 () const {return x*x + y*y;}
	bool operator < (const vec &t) const {return (fabs(x-t.x)>eps) ? (x<t.x) : (y<t.y);}
	vec rot_90_a () const {return vec(-y, x);}
};

double crs(const vec &a, const vec &b)
{
	return a.x*b.y - a.y*b.x;
}

double dot(const vec &a, const vec &b)
{
	return a.x*b.x + a.y*b.y;
}

vector<vec> convex(vector<vec> src)
{
	vector<vec> stk;
	sort(src.begin(), src.end());
	for(auto i=src.begin(); i!=src.end(); i++)
	{
		while(stk.size()>=2 && crs(*i-stk.end()[-1], stk.end()[-1]-stk.end()[-2])>=-eps) stk.pop_back();
		stk.emplace_back(*i);
	}
	int top = stk.size();
	for(auto i=src.rbegin(); i!=src.rend(); i++)
	{
		while(stk.size()>top && crs(*i-stk.end()[-1], stk.end()[-1]-stk.end()[-2])>=-eps) stk.pop_back();
		stk.emplace_back(*i);
	}
	stk.pop_back();
	return stk;
}

int n, m;
vector<vec> A, B;

void input()
{
	read(n), read(m);
	for(int i=1; i<=n; i++)
	{
		vec tmp;
		read(tmp.x), read(tmp.y);
		A.emplace_back(tmp);
	}
	for(int i=1; i<=m; i++)
	{
		vec tmp;
		read(tmp.x), read(tmp.y);
		B.emplace_back(tmp);
	}
}

vec lin_lin_int(vec p1, vec v1, vec p2, vec v2)
{
	double k = crs(p2-p1, v2) / crs(v1, v2);
	return p1 + v1*k;
}

bool try_plain(vec a, vec b, const vector<vec> &in, const vector<vec> &out)
{
	double mxc = +1e30, mnc = -1e30;
	vec mid = (a+b)*0.5, per = (b-a).rot_90_a();
	for(auto i : in)
		if(crs(b-a, i-a) > eps)
			cmax(mnc, crs(b-a, lin_lin_int((i+a)*0.5, (i-a).rot_90_a(), mid, per)-a));
		else if(crs(b-a, i-a) < -eps)
			cmin(mxc, crs(b-a, lin_lin_int((i+a)*0.5, (i-a).rot_90_a(), mid, per)-a));
		else if(dot(b-a, i-a)>dot(b-a, b-a) || dot(b-a, i-a)<0) return false;
	for(auto i : out)
		if(crs(b-a, i-a) > eps)
			cmin(mxc, crs(b-a, lin_lin_int((i+a)*0.5, (i-a).rot_90_a(), mid, per)-a));
		else if(crs(b-a, i-a) < -eps)
			cmax(mnc, crs(b-a, lin_lin_int((i+a)*0.5, (i-a).rot_90_a(), mid, per)-a));
		else if(dot(b-a, i-a)<dot(b-a, b-a) && dot(b-a, i-a)>0) return false;
	if(mxc > mnc+eps) return true;
	else return false;
}

bool check(vector<vec>::iterator in_beg, vector<vec>::iterator in_end, const vector<vec> &in, const vector<vec> &out)
{
	if(try_plain(*in_beg, *(in_end-1), in, out)) return true;
	if(in_end-in_beg < 3) return 0;
	vec lft = *in_beg, rgt = *(in_end-1);
	double mxd = -1e18, tmp;
	vector<vec>::iterator mxp;
	for(auto i=in_beg+1; i!=in_end-1; i++)
	{
		double val = - dot(*i-lft, *i-rgt) / crs(*i-lft, *i-rgt);
		if(val > mxd) mxd = val, mxp = i;
	}
	if(check(in_beg, mxp+1, in, out) || check(mxp, in_end, in, out)) return true;
	else return false;
}
	
int main()
{
	input();
	vector<vec> cA = convex(A), cB = convex(B);
	if(check(cA.begin(), cA.end(), A, B)) puts("YES");
	else if(check(cB.begin(), cB.end(), B, A)) puts("YES");
	else puts("NO");
	return 0;
}