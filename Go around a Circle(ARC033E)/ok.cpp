#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 501000,mod = 1e9+7;
char s[N];
int a[N],n,m;
void solve1(){
	int f[N][2][2];memset(f,0,sizeof(f));
	f[1][1][1]=f[1][0][0]=1;
	auto upd=[](int&a,int b){a+=b;if(a>=mod)a-=mod;};
	for(int i=2;i<=n;i++){
		upd(f[i][1][1],f[i-1][1][0]);
		upd(f[i][1][1],f[i-1][1][1]);
		upd(f[i][1][0],f[i-1][1][1]);
		upd(f[i][0][1],f[i-1][0][0]);
		upd(f[i][0][1],f[i-1][0][1]);
		upd(f[i][0][0],f[i-1][0][1]);
	}
	cout<<(0ll+f[n][1][1]+f[n][1][0]+f[n][0][1])%mod<<'\n';
}
void solve2(){
	int _f[N],*f;memset(_f,0,sizeof(_f));
	f=_f+100;
	int len=n|1,now=0,pos=m;
	while(a[pos]) pos--;
	for(int i=pos;i;i--)
		if(!a[i]){
			if(now&1) len=min(len,now);
			now=0;
		}
		else now++;
	len=min(len,now|1);
	f[-1]=f[1]=1;
	for(int i=3;i<=n;i+=2){
		f[i]=2ll*f[i-2]%mod;
		if(i>len) f[i]=(f[i]-f[i-len-3]+mod)%mod;
	}
	ll ans=0;
	cout<<len<<endl;
	for(int i=1;i<=len;i+=2)
	{
		cout<<i<<" "<<f[n-i-2]<<endl;
		ans=(1ll*(i+1)*f[n-i-2]+ans)%mod;
	}
	cout<<ans<<'\n';
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m>>s+1;
	for(int i=1;i<=m;i++)
		a[i]=s[i]==s[1];
	int flag=1;
	for(int i=1;i<=m;i++)
		flag&=a[i];
	if(flag) solve1();
	else solve2();
	return 0;
}