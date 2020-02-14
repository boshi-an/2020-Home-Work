#include<bits/stdc++.h>
using namespace std;

#define int long long

#define rep(i,n) for(int i=0;i<(n);i++)
#define pb push_back
#define eb emplace_back
#define all(v) (v).begin(),(v).end()
#define fi first
#define se second

using vint=vector<int>;
using pint=pair<int,int>;
using vpint=vector<pint>;

template<typename A,typename B>inline void chmin(A &a,B b){if(a>b)a=b;}
template<typename A,typename B>inline void chmax(A &a,B b){if(a<b)a=b;}

template<class A,class B>
ostream& operator<<(ostream& ost,const pair<A,B>&p){
    ost<<"{"<<p.first<<","<<p.second<<"}";
    return ost;
}

template<class T>
ostream& operator<<(ostream& ost,const vector<T>&v){
    ost<<"{";
    for(int i=0;i<v.size();i++){
        if(i)ost<<",";
        ost<<v[i];
    }
    ost<<"}";
    return ost;
}

inline int topbit(unsigned long long x){
    return x?63-__builtin_clzll(x):-1;
}

inline int popcount(unsigned long long x){
    return __builtin_popcountll(x);
}

inline int parity(unsigned long long x){
    return __builtin_parity(x);
}

template<uint32_t mod>
struct ModInt{
    uint32_t a;
    ModInt& s(uint32_t vv){
        a=vv<mod?vv:vv-mod;
        return *this;
    }

    ModInt(int64_t x=0){s(x%mod+mod);}

    ModInt& operator+=(const ModInt &x){return s(a+x.a);}
    ModInt& operator-=(const ModInt &x){return s(a+mod-x.a);}
    ModInt& operator*=(const ModInt &x){
        a=uint64_t(a)*x.a%mod;
        return *this;
    }
    ModInt& operator/=(const ModInt &x){
        *this*=x.inv();
        return *this;
    }

    ModInt operator+(const ModInt &x)const{return ModInt(*this)+=x;}
    ModInt operator-(const ModInt &x)const{return ModInt(*this)-=x;}
    ModInt operator*(const ModInt &x)const{return ModInt(*this)*=x;}
    ModInt operator/(const ModInt &x)const{return ModInt(*this)/=x;}
    bool operator==(const ModInt &x)const{return a==x.a;}
    bool operator!=(const ModInt &x)const{return a!=x.a;}
    bool operator<(const ModInt &x)const{return a<x.a;}

    ModInt operator-()const{return ModInt()-*this;}
    ModInt pow(int64_t n)const{
        ModInt res(1),x(*this);
        while(n){
            if(n&1)res*=x;
            x*=x;
            n>>=1;
        }
        return res;
    }

    ModInt inv()const{return pow(mod-2);}
};

template<uint32_t mod>
istream& operator>>(istream& in,ModInt<mod>& a){
    return (in>>a.a);
}
template<uint32_t mod>
ostream& operator<<(ostream& out,const ModInt<mod>& a){
    return (out<<a.a);
}
using mint=ModInt<1000000007>;
template<class Mint,int32_t lg>
struct ModIntTable{
    int N;
    vector<Mint>facts,finvs,invs;
    ModIntTable():N(1<<lg),facts(N),finvs(N),invs(N){
        const uint32_t mod=Mint(-1).a+1;
        invs[1]=1;
        for(int i=2;i<N;i++)invs[i]=invs[mod%i]*(mod-mod/i);

        facts[0]=1;
        finvs[0]=1;
        for(int i=1;i<N;i++){
            facts[i]=facts[i-1]*i;
            finvs[i]=finvs[i-1]*invs[i];
        }
    }
    inline Mint fact(int n)const{return facts[n];}
    inline Mint finv(int n)const{return finvs[n];}
    inline Mint inv(int n)const{return invs[n];}
    inline Mint binom(int n,int k)const{
        if(n<0||k<0||k>n)return 0;
        return facts[n]*finvs[k]*finvs[n-k];
    }
    inline Mint perm(int n,int k)const{
        if(n<0||k<0||k>n)return 0;
        return facts[n]*finvs[n-k];
    }
    inline Mint catalan(int n){
        return facts[2*n]*finvs[n+1]*finvs[n];
    }
};
ModIntTable<mint,20>mt;
int N,K,M;
int A[33333];

namespace AL{
mint solve(){
    return mint(K).pow(N-M)*(N-M+1);
}
}

namespace D{
mint dp[2][444][2];
mint solve(){
    dp[0][0][0]=1;
    rep(i,N){
        rep(j,K){
            rep(k,2){
                if(j+1<K)dp[(i+1)&1][j+1][k]+=dp[i&1][j][k]*(K-j);
            }
        }
        for(int k=0;k<2;k++){
            mint sum=0;
            for(int j=K-1;j>0;j--){
                sum+=dp[i&1][j][k];
                dp[(i+1)&1][j][k]+=sum;
            }
        }
        rep(j,K)rep(k,2)dp[i&1][j][k]=0;

        for(int j=M;j<K;j++)dp[(i+1)&1][j][1]+=dp[(i+1)&1][j][0];
    }

    mint ret=0;
        rep(i,K)ret+=dp[N&1][i][1];
        return ret/mt.perm(K,M);
}

}

namespace LR{
    mint dp[2][444];
mint mem[444][444];
mint solve(int pre,int suf){
    dp[0][0]=1;

    for(int i=0;i<=K;i++){
        for(int j=0;j<=i;j++)mem[i][j]=mt.perm(i,j).inv();
    }

    vector<mint>pw(N),sw(N);
    rep(i,N){
        rep(t,2){
            for(int j=pre;j<K;j++){
                pw[i]+=dp[i&1][j]*mt.perm(K-pre,j-pre)*mem[K][j];
            }


            swap(pw,sw);
            swap(pre,suf);
        }

        rep(j,K){
            if(j+1<K)dp[(i+1)&1][j+1]+=dp[i&1][j]*(K-j);
        }
        mint sum=0;
        for(int j=K-1;j>0;j--){
            sum+=dp[i&1][j];
            dp[(i+1)&1][j]+=sum;
        }
        rep(j,K)dp[i&1][j]=0;
    }

    mint ret=0;
    for(int i=0;i+M<=N;i++){
        ret+=pw[i+pre]*sw[N-i-M+suf];
    }
    return ret;
}
}

signed main(){
    cin>>N>>K>>M;
    rep(i,M)cin>>A[i],A[i]--;

    bool ex=false;
    for(int i=0;i+K<=M;i++){
        vint cnt(K);
        rep(j,K)cnt[A[i+j]]++;
        if(*max_element(all(cnt))==1)ex=true;
    }
    if(ex){
        cout<<AL::solve()<<endl;
        return 0;
    }

    vint mem(K);
    int pre=-1,suf=-1;
    rep(i,M){
        if(mem[A[i]]){
            pre=i;
            break;
        }
        mem[A[i]]=1;
    }

    fill(all(mem),0);
    for(int i=M-1;i>=0;i--){
        if(mem[A[i]]){
            suf=M-1-i;
            break;
        }
        mem[A[i]]=1;
    }
    mint ans=AL::solve();
    if(pre==-1){
        ans-=D::solve();
    }
    else{
        ans-=LR::solve(pre,suf);
    }
    cout<<ans<<endl;

    return 0;
}