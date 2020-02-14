#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int MAX_N = 1e5 + 10;
const ll MOD = 1e9 + 7;
 
struct Edge {
    int a, b, xa, xb, id;
};
 
int N, M, coe_self[MAX_N], coe_global;
bool vis[MAX_N];
vector<Edge> edges[MAX_N];
ll G[2];
 
void solve(int st) {
    if (edges[st].size() == 0) {
        vis[st] = true;
        if (coe_self[st]) {
            (G[0] += G[1]) %= MOD;
            G[1] = G[0];
        } else {
            (G[0] *= 2) %= MOD;
            (G[1] *= 2) %= MOD;
        }
        return;
    }
    int x_fi, x_la;
    bool is_loop = false;
    vector<int> chain;
    vector<pair<int, int>> chain_equ;
    int pa_id = 0, cu = st;
    while (true) {
        chain.push_back(cu);
        vis[cu] = true;
        Edge nxt_e;
        bool found = false;
        for (Edge e : edges[cu]) {
            if (e.id == pa_id) continue;
            int nxt = e.a ^ e.b ^ cu;
            if (e.id != pa_id && nxt == st) {
                is_loop = true;
                x_fi = e.xa;
                x_la = e.xb;
                if (st != e.a) swap(x_fi, x_la);
                break;
            }
            found = true;
            nxt_e = e;
        }
        if (!found) break;
        int nxt = nxt_e.a ^ nxt_e.b ^ cu;
        if (nxt_e.a == cu) chain_equ.emplace_back(nxt_e.xa, nxt_e.xb);
        else chain_equ.emplace_back(nxt_e.xb, nxt_e.xa);
        cu = nxt;
        pa_id = nxt_e.id;
    }
    ll t[2]; memset(t, 0, sizeof(t));
    for (int a = 0; a < 2; a++) {
        ll f[2][2]; memset(f, 0, sizeof(f));
        f[a][coe_self[st] & a] = 1;
        for (int id = 0; id < chain_equ.size(); id++) {
            pair<int, int> equ = chain_equ[id];
            ll nf[2][2]; memset(nf, 0, sizeof(nf));
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    for (int k = 0; k < 2; k++) {
                        (nf[j][(j & coe_self[chain[id + 1]]) ^ (i ^ equ.first | j ^ equ.second) /* WA! */ ^ k] += f[i][k]) %= MOD;
                    }
                }
            }
            memcpy(f, nf, sizeof(f));
        }
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                (t[j ^ (is_loop ? x_fi ^ a | x_la ^ i : 0)] += f[i][j]) %= MOD;
            }
        }
    }
    ll ng[2]; memset(ng, 0, sizeof(ng));
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            (ng[i ^ j] += t[i] * G[j]) %= MOD;
        }
    }
    memcpy(G, ng, sizeof(G));
}
 
int main() {
    scanf("%d%d", &M, &N);
    for (int i = 1; i <= M; i++) {
        int k; scanf("%d", &k);
        if (k == 1) {
            int a; scanf("%d", &a);
            if (a < 0) coe_global ^= 1, a *= -1;
            coe_self[a] ^= 1;
        } else {
            int a, b, xa = 0, xb = 0; scanf("%d%d", &a, &b);
            if (a < 0) xa ^= 1, a *= -1;
            if (b < 0) xb ^= 1, b *= -1;
            if (a == b) {
                if (xa != xb) coe_global ^= 1;
                else {
                    coe_global ^= xa;
                    coe_self[a] ^= 1;
                }
            } else {
                edges[a].push_back(Edge({a, b, xa, xb, i}));
                edges[b].push_back(Edge({a, b, xa, xb, i}));
            }
        }
    }
    G[0] = 1;
    for (int i = 1; i <= N; i++) {
        if (!vis[i] && edges[i].size() < 2) {
            solve(i);
        }
    }
    for (int i = 1; i <= N; i++) {
        if (!vis[i]) {
            solve(i);
        }
    }
    printf("%lld\n", G[1 ^ coe_global]);
}
