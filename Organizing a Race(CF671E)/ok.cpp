#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define lson x<<1
#define rson x<<1|1
using namespace std;
 
const int maxn=100010;
typedef long long ll;
int n,K,top,cnt,ans;
int st[maxn],to[maxn],nxt[maxn],head[maxn],nt[maxn];
ll g[maxn],w[maxn],pre[maxn],suf[maxn];
ll mp[maxn<<2],sp[maxn<<2]; //mp:max_p(p=cost-suf),sp:min_{max_suf{l..j-1}+p}
ll ms[maxn<<2],tag[maxn<<2];    //ms:max_suf,tag:区间+标记,cost+=tag,suf+=tag,所以p不变。
inline void add(int,int);
inline void upd(int,ll);
inline void pushdown(int);
ll calc(int,int,int,ll);
inline void pushup(int,int,int);
void build(int,int,int);
void updata(int,int,int,int,int,ll);
int solve(int,int,int,ll);
int query(int,int,int,ll);
void dfs(int);
inline int rd();
int main()
{
    memset(head,-1,sizeof(head));
    n=rd(),K=rd();
    int i;
    for(i=1;i<n;i++) w[i]=rd();
    w[n]=1e17;
    for(i=1;i<=n;i++)    g[i]=rd(),pre[i]=pre[i-1]+g[i]-w[i],suf[i]=suf[i-1]+g[i]-w[i-1];    //预处里pre,suf
    for(st[top=0]=n,i=n-1;i>=0;i--)  //求next
    {
        while(top&&pre[st[top]]>=pre[i]) top--;
        nt[i+1]=st[top]+1,add(st[top]+1,i+1),st[++top]=i;
    }
    build(1,n,1);
    top=0,dfs(n+1);
    printf("%d\n",ans);
    return 0;
}
//------------------------------按照顺序从往下看------------------------------
 
inline void add(int a,int b)    //略
{
    to[cnt]=b,nxt[cnt]=head[a],head[a]=cnt++;
}
void dfs(int x) //首先按照之前说的,我们先建出next树,然后遍历next树。
{
    st[++top]=x;
    if(x!=n+1)
    {
		cout<<"add "<<1<<" "<<x-1<<" "<<-1e17<<endl;
        updata(1,n,1,1,x-1,-1e17);  //排除掉i左面的点的干扰
		cout<<"add "<<nt[x]-1<<" "<<n<<" "<<pre[x-1]-pre[nt[x]-1]<<endl;
        updata(1,n,1,nt[x]-1,n,pre[x-1]-pre[nt[x]-1]);  //维护cost和suf
        int l=1,r=top,mid;
        while(l<r)
        {
            mid=(l+r)>>1;
            if(pre[x-1]-pre[st[mid]-1]<=K)   r=mid;
            else    l=mid+1;
        }
		cout<<"add "<<st[r-1]<<" "<<n<<" "<<1e17<<endl;
        updata(1,n,1,st[r-1],n,1e17);   //二分,排除掉i右面过远的点的干扰（如果往右走过不去,则不考虑往左走的情况）。
		cout<<x<<" "<<st[r-1]<<endl;
		cout<<x<<" "<<query(1,n,1,-1e17)<<endl;
        ans=max(ans,query(1,n,1,-1e17)-x+1);    //更新答案
		cout<<"add "<<st[r-1]<<" "<<n<<" "<<-1e17<<endl;
        updata(1,n,1,st[r-1],n,-1e17);  //复原
		cout<<"add "<<1<<" "<<x-1<<" "<<1e17<<endl;
        updata(1,n,1,1,x-1,1e17);
    }
    for(int i=head[x];i!=-1;i=nxt[i])   dfs(to[i]);
    if(x!=n+1)
    {
        updata(1,n,1,nt[x]-1,n,-(pre[x-1]-pre[nt[x]-1]));   //复原
    }
    top--;
}
void build(int l,int r,int x)   //预处理结束时,构建线段树。
{
    if(l==r)
    {
        ms[x]=suf[l];
        mp[x]=-suf[l];
        return ;
    }
    int mid=(l+r)>>1;
    build(l,mid,lson),build(mid+1,r,rson);
    pushup(l,r,x),mp[x]=min(mp[lson],mp[rson]);
}
void updata(int l,int r,int x,int a,int b,ll t) //区间加操作也跟普通线段树没什么区别。
{
    if(a>b)  return ;
    if(a<=l&&r<=b)
    {
        upd(x,t);
        return ;
    }
    pushdown(x);
    int mid=(l+r)>>1;
    if(a<=mid)   updata(l,mid,lson,a,b,t);
    if(b>mid)    updata(mid+1,r,rson,a,b,t);
    pushup(l,r,x);
}
inline void pushup(int l,int r,int x)   //pushup和pushdown两个操作慢慢讲。
{
    ms[x]=max(ms[lson],ms[rson]);   //ms(max_suf)：直接取最值即可,max_p:由于永远不会改变,所以不用维护。
    int mid=(l+r)>>1;
    sp[x]=calc(mid+1,r,rson,ms[lson]);  //sp数组维护起来比较复杂,我们引入calc函数,下面讲。
}
inline void pushdown(int x) //pushdown比较简单
{
    if(tag[x])
    {
        upd(lson,tag[x]),upd(rson,tag[x]);
        tag[x]=0;
    }
}
inline void upd(int x,ll y) //比较简单
{
    tag[x]+=y,ms[x]+=y,sp[x]+=y;
}
ll calc(int l,int r,int x,ll t) //***关键函数*** calc(...,t)=min{max(max_suf{l..i-1},t)+p[i],l<=i<=r} 即我们已知了左边
                                //的max_suf,现在要求这个区间中答案的最小值。如何计算呢？
{
    if(l==r)    return t+mp[x];
    pushdown(x);
    int mid=(l+r)>>1;
    if(ms[lson]>=t)  return min(calc(l,mid,lson,t),sp[x]);   //如果max_suf{l,mid}>=t,则t对[mid+1,r]的答案都没有影响,
                                                            //所以直接调用之前的答案sp即可（注意sp维护的是什么！）。
                                                            //然后我们只递归左边就行了。
    return min(t+mp[lson],calc(mid+1,r,rson,t));    //否则,左边的max_suf{l..i-1}都应该取t,则用t+max_p{l,mid}更新答案
                                                    //然后只递归右面就行了。
}                               //整个calc的复杂度是O(log)的。
 
//--------------------分割线-------------------- 上面主要是修改,下面主要是查询。
 
int query(int l,int r,int x,ll t)   //***关键函数*** 查询函数（即树上二分操作）,我们想找到最右面那个答案<=m的点
                                    //t的定义和calc()里的一样,我们已知了左边的max_suf{l..i-1}=t。实现过程也和calc类似。
{
    if(l==r)    return t+mp[x]<=K?l:0;
    pushdown(x);
    int mid=(l+r)>>1;
    if(ms[lson]>=t)  //讨论：如果max_suf{l,mid}>=t,则t对[mid+1,r]没有影响,我们可以直接调用sp数组。
    {
        if(sp[x]<=K) return query(mid+1,r,rson,ms[lson]);    //如果[mid+1,r]中的最小值<=K,显然我们应该进入右面查询。
        else    return query(l,mid,lson,t); //否则呢,显然右面的都不合法，我们进入左边查询。
    }
    else    //如果max_suf{l,mid}<t，则左面的max_suf都应该取t,我们引入solve函数，表示的就是
            //当一个区间的max_suf{..i-1}都取t时的查询结果。而对于右面的，我们还需要递归查询。
    {
        return max(solve(l,mid,lson,t),query(mid+1,r,rson,t));
    }
}
int solve(int l,int r,int x,ll t)   //说白了就是已知区间的max_suf{..i-1}=t时的query函数，但是相对简单一些。
{
    if(l==r)    return t+mp[x]<=K?l:0;
    pushdown(x);
    int mid=(l+r)>>1;
    if(t+mp[rson]<=K)    return solve(mid+1,r,rson,t);   //如果右边的答案<=K,则去右面
    return solve(l,mid,lson,t); //否则去左边
}                                   //一次solve的复杂度是O(log)的
inline int rd()
{
    int ret=0,f=1;  char gc=getchar();
    while(gc<'0'||gc>'9') {if(gc=='-')    f=-f;   gc=getchar();}
    while(gc>='0'&&gc<='9')   ret=ret*10+(gc^'0'),gc=getchar();
    return ret*f;
}