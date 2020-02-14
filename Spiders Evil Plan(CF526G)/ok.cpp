#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define rep(i,a) for(int i=lst[a];i;i=nxt[i])
using namespace std;

int read() {
	char ch;
	for(ch=getchar();ch<'0'||ch>'9';ch=getchar());
	int x=ch-'0';
	for(ch=getchar();ch>='0'&&ch<='9';ch=getchar()) x=x*10+ch-'0';
	return x;
}

void write(int x) {
	if (!x) {puts("0");return;}
	char ch[20];int tot=0;
	for(;x;x/=10) ch[++tot]=x%10+'0';
	fd(i,tot,1) putchar(ch[i]);
	puts("");
}

const int N=1e5+5;

int t[N<<1],nxt[N<<1],v[N<<1],lst[N],l;
void add(int x,int y,int z) {t[++l]=y;v[l]=z;nxt[l]=lst[x];lst[x]=l;}

int n,m,dis[N],a,b;

void dfs(int x,int y) {
	rep(i,x)
		if (t[i]!=y) {
			dis[t[i]]=dis[x]+v[i];
			dfs(t[i],x);
		}
}

struct Tree{
	int fa[N][17];
	int mx[N],sum[N],son[N],an[N],id[N],m;
	pair<int,int> val[N];

	void dfs(int x,int y) {
		fa[x][0]=y;mx[x]=sum[x];
		rep(i,x)
			if (t[i]!=y) {
				sum[t[i]]=sum[x]+v[i];
				dfs(t[i],x);
				if (mx[t[i]]>mx[x]) {
					son[x]=t[i];
					mx[x]=mx[t[i]];
				}
			}
	}

	void make(int x,int y) {
		if (!son[x]) {
			val[++m]=make_pair(-y,x);
			return;
		}
		rep(i,x) if (t[i]!=fa[x][0]) make(t[i],(t[i]==son[x]?y:0)+v[i]);
	}

	void build(int x) {
		dfs(x,0);
		fo(j,1,16) fo(i,1,n) fa[i][j]=fa[fa[i][j-1]][j-1];
		make(x,0);
		sort(val+1,val+m+1);
		fo(i,1,m) {
			int x=val[i].second;
			for(;x&&!id[x];x=fa[x][0]) id[x]=i;
			an[i]=an[i-1]-val[i].first;
		}
	}

	int solve(int x,int y) {
		y=2*y-1;if (y>m) y=m;
		if (id[x]<=y) return an[y];
		int z=x;
		fd(j,16,0) if (id[fa[z][j]]>y) z=fa[z][j];
		z=fa[z][0];
		return an[y]+max(mx[x]-mx[z],mx[x]-sum[z]+val[y].first);
	}
}t1,t2;

int main() {
	n=read();m=read();
	fo(i,1,n-1) {
		int x=read(),y=read(),z=read();
		add(x,y,z);add(y,x,z);
	}
	dis[1]=0;dfs(1,0);fo(i,1,n) if (dis[i]>dis[a]) a=i;
	dis[a]=0;dfs(a,0);fo(i,1,n) if (dis[i]>dis[b]) b=i;
	t1.build(a);t2.build(b);
	int ans=0;
	for(;m;m--) {
		int x = read(), y = read();
		write(ans=max(t1.solve(x,y),t2.solve(x,y)));
	}
	return 0;
}