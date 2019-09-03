#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll qpow(ll a,ll b,ll mod)
{
    ll res=1;
    while(b)
    {
        if(b&1)
            res=res*a>mod?res*a%mod+mod:res*a;
        a=a*a>mod?a*a%mod+mod:a*a;
        b>>=1;
    }
    return res;
}

ll phi(ll x)///计算欧拉值
{
    ll res=x;
    for(int i=2;i*i<=x;i++)
    {
        if(x%i==0)
        {
            while(x%i==0)
                x/=i;
            res=res-res/i;
        }
    }
    if(x>1)
        res=res-res/x;
    return res;
}

ll solve(ll a,ll b,ll m)
{
    if(m==1||b==0||a==1)
        return 1ll;

    ll p=phi(m);
    return qpow(a,solve(a,b-1,p),m);
}

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        ll a,b,m;
        ///a的次幂的a次幂...一共b个
        ///对m取模
        cin>>a>>b>>m;
        cout<<solve(a,b,m)%m<<endl;
    }
}
