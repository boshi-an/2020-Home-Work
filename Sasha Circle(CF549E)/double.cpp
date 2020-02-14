#include <bits/stdc++.h>
 
using namespace std;
 
const int MX = 10005;
const double eps = 1e-10;
 
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
	vec r_90_a () const {return vec(-y, x);}
	void print () {printf("%.2lf, %.2lf\n", x, y);}
	void scan () {scanf("%lf%lf", &x, &y);}
	bool operator < (const vec &t) const {return (fabs(x-t.x)>eps) ? (x<t.x) : (y<t.y);}
};
 
double crs(const vec &a, const vec &b)
{
	return a.x*b.y - a.y*b.x;
}
 
double dot(const vec &a, const vec &b)
{
	return a.x*b.x + a.y*b.y;
}
 
struct lin
{
	vec p, v;
	double a;
 
	lin (const vec &tp = vec(), const vec &tv = vec()) : p(tp), v(tv) {a = atan2(tv.y, tv.x);}
	bool operator < (const lin &t) const {return a < t.a;}
};

bool parallel(lin a, lin b)
{
	return fabs(crs(a.v, b.v)) < eps;
}
 
bool better(lin a, lin b)
{
	return crs(b.v, a.p-b.p) > 0;
}
 
vec lin_lin_int(lin a, lin b)
{
	double k = crs(b.p-a.p, b.v) / crs(a.v, b.v);
	return a.p + a.v*k;
}
 
bool judge(lin a, lin b, lin nxt)
{
	vec p = lin_lin_int(a, b);
	if(crs(nxt.v, p-nxt.p) <= 0) return true;
	else return false;
}
 
int n, m;
vec black[MX], white[MX];
 
void input()
{
	read(n), read(m);
	for(int i=1; i<=n; i++) black[i].scan();
	for(int i=1; i<=m; i++) white[i].scan();
}
 
int convex(vec *src, vec *tar, int num)
{
	sort(src+1, src+num+1);
	static vec stk[MX];
	int top = 0, bot = 0;
	for(int i=1; i<=num; i++)
	{
		while(top>=2 && crs(stk[top]-stk[top-1], src[i]-stk[top-1])<=eps) top--;
		stk[++top] = src[i];
	}
	bot = top;
	for(int i=num; i>=1; i--)
	{
		while(top>bot && crs(stk[top]-stk[top-1], src[i]-stk[top-1])<=eps) top--;
		stk[++top] = src[i];
	}
	for(int i=1; i<=top; i++) tar[i] = stk[i];
	return top;
}
 
int pla_int_count(lin *src, int ln)
{
	int h = 0, t = 1, tot = 0;
	sort(src+1, src+ln+1);
	for(int i=1; i<=ln; i++)
		if(!tot || !parallel(src[tot], src[i])) src[++tot] = src[i];
		else if(better(src[i], src[tot])) src[tot] = src[i];
	for(int i=1; i<=tot; i++)
	{
		while(t<h && judge(src[h-1], src[h], src[i])) h--;
		while(t<h && judge(src[t+1], src[t], src[i])) t++;
		src[++h] = src[i];
	}
	while(t+1<h && judge(src[h-1], src[h], src[t])) h--;
	while(t+1<h && judge(src[t+1], src[t], src[h])) t++;
	return h-t+1;
}
 
bool work(vec *in_src, vec *out_src, int in_num, int out_num)
{
	static vec in[MX];
	static lin pla[MX*406];
	int pl_num = 0;
	in_num = convex(in_src, in, in_num);
	random_shuffle(in_src+1, in_src+in_num+1);
	cmin(in_num, 400);
	//if(in_num*out_num >= MX*606) {printf("%d\n", in_num); exit(0);}
	pla[++pl_num] = lin(vec(0, -1e20), vec(+1e20, +1e20));
	pla[++pl_num] = lin(vec(+1e20, 0), vec(-1e20, +1e20));
	pla[++pl_num] = lin(vec(0, +1e20), vec(-1e20, -1e20));
	pla[++pl_num] = lin(vec(-1e20, 0), vec(+1e20, -1e20));
	for(int i=1; i<=in_num; i++)
		for(int j=1; j<=out_num; j++)
			pla[++pl_num] = lin(in[i]*(0.5+eps)+out_src[j]*(0.5-eps), (out_src[j]-in[i]).r_90_a());
	int cnt = pla_int_count(pla, pl_num);
	if(cnt >= 3) return true;
	else return false;
}
 
int main()
{
	srand(time(0));
	//freopen("in", "r", stdin);
	input();
	if(work(black, white, n, m) || work(white, black, m, n)) printf("YES\n");
	else printf("NO\n");
	return 0;
}