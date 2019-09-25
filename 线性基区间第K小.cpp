#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int base[maxn][40],p[maxn][40];
int bbase[40];
int th[40];
int a[maxn];
int n,q;
int cnt=0;

void Insert(int k,int x,int pos)
{
    for(int i=30;i>=0;i--)
    {
        if(x&(1<<i))
        {
            if(!base[k][i])
            {
                base[k][i]=x;
                p[k][i]=pos;
                return ;
            }
            else if(pos>p[k][i])
            {
                swap(p[k][i],pos);
                swap(base[k][i],x);
            }
            x^=base[k][i];
        }
    }
}

void rebuild(int l,int r)
{
    ///复制[l,r]信息到bbase
    memset(bbase,0,sizeof(bbase));
    for(int i=30;i>=0;i--)
        if(p[r][i]>=l)
            bbase[i]=base[r][i];

    for(int i=30;i>=0;i--)
        for(int j=i-1;j>=0;j--)
            if(bbase[i]&(1<<j))
                bbase[i]^=bbase[j];

    for(int i=0;i<=30;i++)
        if(bbase[i])
            th[cnt++]=bbase[i];
}

int query(int l,int r,int k)
{
    cnt=0;
    rebuild(l,r);

    if(cnt!=r-l+1)
        k--;
    if(k>=(1ll<<cnt))
        return -1;
    int ans=0;
    for(int i=30;i>=0;i--)
    {
        if(k&(1<<i))
            ans^=th[i];
    }
    return ans;
}

void Solve()
{
    for(int i=1;i<=n;i++)
    {
        memcpy(base[i],base[i-1],sizeof(base[i-1]));
        memcpy(p[i],p[i-1],sizeof(p[i-1]));

        Insert(i,a[i],i);
    }
    
    cin>>q;
    while(q--)
    {
        int l,r,k;
        cin>>l>>r>>k;
        cout<<query(l,r,k)<<endl;
    }
}


int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];

    Solve();
}
