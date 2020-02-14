#include<bits/stdc++.h>

using namespace std;
#define ll long long

const int N = 100005;
int mx, mx2, n, cnt[4], a[N], b[N], f[N], g[N], vis[N];
ll ans;
bool cmpa(int x, int y){ return a[x]<a[y];}
bool cmpb(int x, int y){ return b[x]>b[y];}
int main() {
	scanf("%d", &n);
	for(int i=1; i<=n; ++i) scanf("%d%d", a+i, b+i), f[i]=g[i]=i;
	sort(f+1, f+n+1, cmpa), sort(g+1, g+n+1, cmpb);
	for(int i=1, x; i<=n; ++i){
		ans+=x=min(a[f[i]], b[g[i]]);
		if(a[f[i]]<b[g[i]]) vis[f[i]]|=1; else vis[g[i]]|=2;
		if(x>mx) mx2=mx, mx=x; else if(x>mx2) mx2=x;
	}
	for(int i=1; i<=n; ++i) ++cnt[vis[i]];
	if(cnt[0] || !cnt[1] || !cnt[2]) printf("%lld\n", ans);
	else{
		ll x=1e18;
		for(int i=1; i<=n; ++i){
			int t=vis[i]==1?b[i]:a[i];
			x=min(x, ans+t-(a[i]+b[i]-t==mx?mx2:mx));
		}
		printf("%lld\n", x);
	}
	return 0;
}