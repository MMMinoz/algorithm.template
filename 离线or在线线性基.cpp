/*给定n和a1 a2 a3...an

a1 a2 a3...an一次性给全
有q个询问：

给定l,r

求在al...ar中选取任意个

使得他们的异或和最大
*/
///1.离线线性基
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;

int a[maxn];
int ans[maxn];
int n,m;
struct Q
{
    int l,r;
    int index;
}q[maxn];
bool cmp(Q a,Q b)
{
    return a.r<b.r;
}

int base[maxn],p[maxn];

void Insert(int pos,int x)
{
    for(int i=20;i>=0;i--)
    {
        if(x&(1<<i))
        {
            if(!base[i])
            {
                base[i]=x;
                p[i]=pos;
                return ;
            }
            else if(pos>p[i])
            {
                swap(p[i],pos);
                swap(base[i],x);
            }
            x^=base[i];
        }
    }
}

int getMax(int k)
{
    int l=q[k].l,r=q[k].r;
    int ans=0;

    for(int i=20;i>=0;i--)
        if(p[i]>=l&&p[i]<=r)
            ans=max(ans,ans^base[i]);

    return ans;
}

void Solve()
{
    sort(q+1,q+1+m,cmp);
    int k=1;
    for(int i=1;i<=n;i++)
    {
        Insert(i,a[i]);

        while(i == q[k].r)
        {
            ans[q[k].index]=getMax(k);
            k++;
        }
    }
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i);
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&q[i].l,&q[i].r);
        q[i].index=i;
    }

    Solve();
    for(int i=1;i<=m;i++)
        printf("%d\n",ans[i]);
}

///2.在线线性基
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+50;

int n,q;
int a[maxn];
int base[maxn][40];
int p[maxn][40];

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
                swap(pos,p[k][i]);
                swap(x,base[k][i]);
            }
            x^=base[k][i];
        }
    }
}

int Max(int l,int r)
{
    int ans=0;
    for(int i=30;i>=0;--i)
        if(p[r][i]>=l)
            ans=max(ans,ans^base[r][i]);
    return ans;
}
void Solve()
{
    for(int i=1;i<=n;++i)
    {
        memcpy(base[i],base[i-1],sizeof(base[i-1]));
        memcpy(p[i],p[i-1],sizeof(p[i-1]));

        Insert(i,a[i],i);
    }

    while(q--)
    {
        int l,r;
        scanf("%d%d",&l,&r);

        printf("%d\n",Max(l,r));
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i <= n;++i)
        scanf("%d",a+i);
    scanf("%d",&q);

    Solve();

    return 0;
}
