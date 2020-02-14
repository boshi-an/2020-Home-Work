#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int f[605][605];
int a[605],b[605];
int h[605],fc[605];
const int mod=1e9+7;
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	n*=2;
	for(int i=1;i<=k;i++){
		scanf("%d%d",&a[i],&b[i]);
		h[a[i]]=1;
		h[b[i]]=1;
	}
	fc[0]=1;
	for(int i=1;i<=n;i++)fc[i]=1ll*(i-1)*fc[i-2]%mod;
	for(int i=1;i<=n;i++)h[i]+=h[i-1];
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			bool ok=1;
			for(int p=1;p<=k;p++)if((i<=a[p]&&a[p]<=j)^(i<=b[p]&&b[p]<=j))ok=0;
			if(!ok)continue;
			f[i][j]=fc[j-i+1-(h[j]-h[i-1])];
			for(int p=i+1;p<j;p++)f[i][j]=(f[i][j]-1ll*f[i][p]*fc[j-p-(h[j]-h[p])]%mod+mod)%mod;
			ans=(ans+1ll*f[i][j]*fc[n-2*k-(j-i+1-(h[j]-h[i-1]))])%mod;
			printf("%d %d %d\n",i,j,f[i][j]);
		}
	}
	printf("%d\n",ans);
	return 0;
}