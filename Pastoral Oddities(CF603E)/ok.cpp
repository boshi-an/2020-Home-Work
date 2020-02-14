#include<bits/stdc++.h>
using namespace std;
#define gc getchar()
#define pc putchar
#define li long long
inline li read(){
    li x = 0,y = 0,c = gc;
    while(!isdigit(c)) y = c,c = gc;
    while(isdigit(c)) x = (x << 1) + (x << 3) + (c ^ '0'),c = gc;
    return y == '-' ? -x : x;
}
inline void print(li q){
    if(q < 0) pc('-'),q = -q;
    if(q >= 10) print(q / 10);
    pc(q % 10 + '0');
}
int n,m;
int f[400010],l[400010],r[400010],mx[400010];
bool c[400010],sz[400010],zs[400010];
struct edge{
    int u,v,w;
}e[300010];
int ee[300010],ans[300010];
inline bool cmp(int q,int w){
    return e[q].w < e[w].w;
}
inline bool is(int q){
    return l[f[q]] != q && r[f[q]] != q;
}
inline void ud(int q){
    sz[q] = sz[l[q]] ^ sz[r[q]] ^ zs[q];
    mx[q] = max(max(mx[l[q]],mx[r[q]]),q <= n ? 0 : q);
}
inline void rv(int q){
    c[q] ^= 1;swap(l[q],r[q]);
}
inline void ps(int q){
    if(!c[q]) return;
    if(l[q]) rv(l[q]);
    if(r[q]) rv(r[q]);
    c[q] = 0;
}
inline void ro(int q){
    int p = f[q];
    if(l[f[p]] == p) l[f[p]] = q;
    else if(r[f[p]] == p) r[f[p]] = q;
    f[q] = f[p];f[p] = q;
    if(l[p] == q){
        l[p] = r[q];r[q] = p;
        if(l[p]) f[l[p]] = p;
    }
    else{
        r[p] = l[q];l[q] = p;
        if(r[p]) f[r[p]] = p; 
    }
    ud(p);ud(q);
}
inline void gx(int q){
    if(!is(q)) gx(f[q]);
    ps(q);
}
inline void sp(int q){
    gx(q);
    while(!is(q)){
        int p = f[q];
        if(!is(p)){
            if((l[f[p]] == p) ^ (l[p] == q)) ro(q);
            else ro(p);
        }
        ro(q);
    }
}
inline void ac(int q){
    int p = 0;
    while(q){
        sp(q);
        zs[q] ^= sz[r[q]];
        r[q] = p;
        zs[q] ^= sz[r[q]];
        ud(q);
        p = q;
        q = f[q];
    }
}
inline void mk(int q){
    ac(q);sp(q);rv(q);
}
inline void si(int u,int v){
    mk(u);ac(v);sp(v);
}
int main(){
    int i,j,u,v,w;
    n = read();m = read();
    if(n & 1){
        for(i = 1;i <= m;++i) puts("-1");
        return 0;
    }
    for(i = 1;i <= m;++i){
        e[i].u = read();e[i].v = read();e[i].w = read();ee[i] = i;
    }
    sort(ee + 1,ee + m + 1,cmp);
    for(i = 1;i <= n;++i) sz[i] = zs[i] = 1,mx[i] = 0;
    for(i = 1;i <= m;++i) mx[i + n] = i + n;
    int nw = n;
    for(i = m,j = 1;i;--i){
        for(;j <= m && nw;++j){
            if(ee[j] > i) continue;
            w = ee[j] + n;u = e[w - n].u;v = e[w - n].v;
            si(u,v);
            if(f[u]){
                if(mx[v] <= w) continue;
                w = mx[v];u = e[w - n].u;v = e[w - n].v;
                si(u,v);sp(w);l[w] = r[w] = f[u] = f[v] = sz[w] = zs[w] = 0;
                w = ee[j] + n;u = e[w - n].u;v = e[w - n].v;
                mk(u);mk(v);f[u] = f[v] = w;sz[w] = zs[w] = sz[u] ^ sz[v];
            }
            else{
                rv(v);f[u] = f[v] = w;sz[w] = zs[w] = sz[u] ^ sz[v];
                if(sz[u] && sz[v]) nw -= 2;
            }
        }
        if(j > m && nw) ans[i] = -1;
        else{
            ans[i] = e[ee[j - 1]].w;
            w = i + n;u = e[i].u;v = e[i].v;
            si(u,v);sp(w);
            if(!f[v]) continue;
            l[w] = r[w] = f[u] = f[v] = sz[w] = zs[w] = 0;
            if(sz[u] && sz[v]) nw += 2;
        }
    }
    for(i = 1;i <= m;++i) print(ans[i]),pc('\n');
    return 0;
}