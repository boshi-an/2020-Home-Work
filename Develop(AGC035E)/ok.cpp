#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 150;
int N, K, M;
int add(int a, int b) {return (a + b)%M;}
int mul(int a, int b) {return 1LL*a*b%M;}
int f[MAXN + 5][MAXN + 5];
void solve1() {
    K /= 2, f[0][0] = 1;
    for(int i=1;i<=N;i++) {
        for(int j=0;j<=K;j++)
            f[i][0] = add(f[i][0], f[i-1][j]);
        for(int j=0;j<K;j++)
            f[i][j+1] = add(f[i][j+1], f[i-1][j]);
    }
    int ans1 = 0, ans2 = 0;
    for(int i=0;i<=K;i++)
        ans1 = add(ans1, f[N/2][i]);
    for(int i=0;i<=K;i++)
        ans2 = add(ans2, f[(N+1)/2][i]);
    printf("%d\n", mul(ans1, ans2));
}
int g[2*MAXN + 5][MAXN + 5][MAXN + 5];
void solve2() {
    int p; g[0][0][0] = 1;
    for(int i=2;i-K<=N;i+=2) {
        for(int j=0;j<=N;j++)
            for(int k=0;k<=K+1;k++)
                g[i][0][0] = add(g[i][0][0], g[i-2][j][k]);
        if( i <= N ) {
            for(int j=0;j<=N;j++)
                for(int k=0;k<=K+1;k++)
                    g[i][j+1][0] = add(g[i][j+1][0], g[i-2][j][k]);
        }
        if( i - K >= 1 ) {
            for(int j=0;j<=N;j++) {
                for(int k=1;k<=K;k++)
                    g[i][0][k+1] = add(g[i][0][k+1], g[i-2][j][k]);
                g[i][0][0] = add(g[i][0][0], g[i-2][j][0]);
            }
        }
        if( i <= N && i - K >= 1 ) {
            for(int j=0;j<=N;j++)
                for(int k=0;max(k,j+1)<=K;k++)
                    g[i][j+1][max(k+1,j+2)] = add(g[i][j+1][max(k+1,j+2)], g[i-2][j][k]);
        }
        p = i;
    }
    int ans = 0;
    for(int j=0;j<=N;j++)
        for(int k=0;k<=K+1;k++)
            ans = add(ans, g[p][j][k]);
    printf("%d\n", ans);
}
int main() {
    scanf("%d%d%d", &N, &K, &M);
    if( K % 2 == 0 ) solve1();
    else solve2();
}