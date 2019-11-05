#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=998244353;
const int maxn=5e4+10;

ll n,k;

///求过 (xi, yi) 的 n-1 次的多项式
ll inv[maxn];          ///逆元
ll a[maxn];            ///1 到 n，n个点，  也就是yi，视题目而定
ll pre[maxn],suf[maxn];  ///前缀积 后缀积
ll fac[maxn];          ///阶乘的逆元

ll qpow(ll x,ll y)
{
    ll ans=1;
    while(y)
    {
        if(y&1)
            ans=ans*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return ans;
}

///连续型 O(n)
ll csolve(int n,ll k)
{
    /// 1到n，n个点插值 直接返回
    if(k<=n)
        return a[k];
    k%=mod;
    ll ans=0;
    pre[0]=suf[n+1]=1;    ///边界
    for(ll i=1;i<=n;i++)      ///(x-i) 前缀积
        pre[i]=pre[i-1]*(k-i)%mod;

    for(ll i=n;i>=1;i--)   ///(x-i) 后缀积
        suf[i]=suf[i+1]*(k-i)%mod;

    for(ll i=1;i<=n;i++)
    {
        ll f=fac[i-1]*fac[n-i]%mod; ///从0到n时，fac[i-1] 变为 fac[i];
        f=(n-i)&1?-f:f;           ///判断正负
        (ans+=a[i]*f%mod*pre[i-1]%mod*suf[i+1])%=mod;
    }
    ans+=ans<0?mod:0;
    return ans;
}

///离散型 O(n^2)
ll x[maxn],y[maxn];
ll lsolve(int n,ll k)
{
    ll ans=0,cur;
    for(int i=1;i<=n;i++)
    {
        ll cur=1;
        for(int j=1;j<=n;j++)
            if(i!=j)
                cur=cur*(x[i]+mod-x[j])%mod;
        cur=qpow(cur,mod-2);
        for(int j=1;j<=n;j++)
            if(i!=j)
                cur=cur*(k+mod-x[j])%mod;
        cur=cur*y[i]%mod;
        ans=(ans+cur)%mod;
    }
    return ans;
}

ll ans;
int main()
{
    ///预处理逆元
    inv[1]=1;
    for(int i=2;i<=maxn;i++)
        inv[i]=-(mod/i)*inv[mod%i];

    ///预处理阶乘逆元
    fac[0]=1;
    for(int i=1;i<maxn;i++)
        fac[i]=fac[i-1]*inv[i]%mod;

    ///已知e个点，求第n个
    scanf("%lld%lld",&n,&k);

    ///连续型
    for(int i=1;i<=n;i++)
        scanf("%d",a+i);
    printf("%lld\n",csolve(n,k));

    ///离散型
    for(int i=1;i<=n;i++)
        scanf("%lld%lld",x+i,y+i);
    printf("%lld\n",lsolve(n,k));
    return 0;
}




///////////////////////
区间
///////////////////////
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=1e5+5;
//mod一定要是质数
const int mod=998244353;

ll a[maxn];         ///前几项, 前面无效值用0占位
int st=1,ed=maxn-1; ///使用上面数组下标为[st,ed]的数据

ll fac[maxn+5],inv[maxn+5],facinv[maxn+5];
ll pre[maxn+5],saf[maxn+5];

ll qpow(ll x,ll y)
{
    ll ans=1;
    while(y)
    {
        if(y&1)
            ans=ans*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return ans;
}

///预处理: fac[]阶乘, inv[]逆元, facinv[]阶乘逆元
///只需要main函数内调用一次!
void init()
{
    fac[0]=inv[0]=facinv[0]=1;
    fac[1]=inv[1]=facinv[1]=1;
    for(int i=2;i<ed+3;++i)
    {
        fac[i]=fac[i-1]*i%mod;
        inv[i]=mod-(mod/i*inv[mod%i]%mod);
        facinv[i]=facinv[i-1]*inv[i]%mod;
    }
}

///连续型：
///计算第k项的值
///复杂度O(ed-st)
ll cal(ll k)
{
    int n=ed-st;
    k=((k%mod)+mod)%mod;
    pre[0]=((k-st)%mod+mod)%mod;
    saf[n]=((k-st-n)%mod+mod)%mod;
    for(int i=1;i<=n;++i)
    {
        pre[i]=((pre[i-1]*(k-st-i))%mod+mod)%mod;
        saf[n-i]=((saf[n-i+1]*(k-st-n+i))%mod+mod)%mod;
    }
    ll res=0;
    for(int i=0;i<=n;++i)
    {
        ll fz=1;
        if(i!=0)fz=fz*pre[i-1]%mod;
        if(i!=n)fz=fz*saf[i+1]%mod;
        ll fm=facinv[i]*facinv[n-i]%mod;
        if((n-i)&1)fm=mod-fm;
        (res+=a[i+st]*(fz*fm%mod)%mod)%=mod;
    }
    return res;
}

///离散型 O(n^2)
ll x[maxn],y[maxn];
ll lsolve(int n,ll k)
{
    ll ans=0,cur;
    for(int i=1;i<=n;i++)
    {
        ll cur=1;
        for(int j=1;j<=n;j++)
            if(i!=j)
                cur=cur*(x[i]+mod-x[j])%mod;
        cur=qpow(cur,mod-2);
        for(int j=1;j<=n;j++)
            if(i!=j)
                cur=cur*(k+mod-x[j])%mod;
        cur=cur*y[i]%mod;
        ans=(ans+cur)%mod;
    }
    return ans;
}

int main()
{
    init();
    int n,q;
    scanf("%d%d",&n,&q);
    ///连续型
    ///已知前多少项，前ed项
    ///若最高项为p,则有p+1项
    st=1;
    ed=n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=n+1;i<=n+5;i++)
        a[i]=cal(i);
    for(int i=1;i<=n+5;i++)
        a[i]+=a[i-1];
    st=1;
    ed=n+5;
    while(q--)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        l,r;
        ll ans=(cal(r)-cal(l-1)+mod)%mod;
        printf("%lld\n",ans);
    }

    ///离散型
    for(int i=1;i<=n;i++)
        scanf("%lld%lld",x+i,y+i);
    while(q--)
    {
        int k;
        scanf("%d",&k);
        printf("%lld\n",lsolve(n,k));
    }
}
