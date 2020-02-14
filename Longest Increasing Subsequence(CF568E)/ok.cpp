#include <bits/stdc++.h>
 
using namespace std;
 
const int MAX_N = 1e5 + 10;
 
int N, M, A[MAX_N], B[MAX_N], F[MAX_N], K;
bool used[MAX_N];
set<int> pos_of_len[MAX_N];
 
int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) scanf("%d", &A[i]);
    scanf("%d", &M);
    for (int i = 1; i <= M; i++) scanf("%d", &B[i]);
    sort(B + 1, B + M + 1);
    for (int i = 1; i <= N; i++) {
        if (A[i] == -1) {
            int p = lower_bound(F + 1, F + 1 + K, B[M]) - F;
            if (p > K) F[++K] = INT_MAX;
            for (int j = M; j; j--) {
                while (p > 1 && B[j] <= F[p - 1]) p--;
                F[p] = min(F[p], B[j]);
            }
        } else {
            int p = lower_bound(F + 1, F + 1 + K, A[i]) - F;
            F[p] = A[i];
            if (p > K) K++;
            pos_of_len[p].insert(i);
        }
    }
    int p = N, last = INT_MAX;
    for (int i = K; i; i--) {
        set<int>::iterator it = pos_of_len[i].lower_bound(p + 1);
        if (it != pos_of_len[i].begin()) {
            it--;
            if (A[*it] < last) {
                p = *it;
                last = A[p];
                continue;
            }
        }
        while (A[p] != -1) p--;
        int q = lower_bound(B + 1, B + M + 1, last) - B - 1;
        last = A[p] = B[q]; used[q] = true;
    }
    int t = 1;
    for (int i = 1; i <= N; i++) {
        if (A[i] == -1) {
            while (used[t]) t++;
            A[i] = B[t]; used[t] = true;
        }
    }
    for (int i = 1; i <= N; i++) printf("%d ", A[i]);
    printf("\n");
}