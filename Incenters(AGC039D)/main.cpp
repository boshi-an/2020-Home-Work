#include <bits/stdc++.h>

using namespace std;

typedef complex<double> Z;

const int MX = 6005;
const double pi = acos(-1);

int n, len;
int pos[MX];

int main()
{
	scanf("%d%d", &n, &len);
	for(int i=1; i<=n; i++) scanf("%d", &pos[i]), pos[n+i] = pos[i]+len;
	Z sum(0, 0);
	for(int i=n+1; i<=n*2; i++)
	{
		Z s_ang(0, 0);
		for(int j=i-1; j>i-n; j--)
		{
			Z mid = exp(Z(0, pi*(pos[i]+pos[j])/len));
			Z lft = exp(Z(0, 2*pi*pos[i]/len));
			Z rgt = exp(Z(0, 2*pi*pos[j]/len));
			sum += mid * Z(i-j-1, 0) + (lft-mid) * s_ang;
			s_ang += exp(Z(0, pi*(pos[j]-pos[i])/len));
		}
	}
	sum /= (1.0*n*(n-1)*(n-2) / 6);
	printf("%.12lf %.12lf\n", -sum.real(), -sum.imag());
	return 0;
}