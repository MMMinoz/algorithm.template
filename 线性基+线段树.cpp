///区间线性基
///线性基+线段树
/*给定n和a1 a2 a3...an

a1 a2 a3...an带更新

有q个询问：

给定l,r

求在al...ar中选取任意个

使得他们的异或和最大
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=5e5+5;
int n,q;
int a[maxn];
struct Seg
{
    int l,r;
    int mid(){return l+((r-l)>>1);}
    int p[25];
    void Insert(int x)
    {
        for(int i=20;i>=0;i--)
        {
            if(x&(1<<i))
            {
                if(!p[i])
                {
                    p[i]=x;
                    return ;
                }
                x^=p[i];
            }
        }
   }

   int Max()
   {
        int ans=0;
        for(int i=20;i>=0;i--)
            ans=max(ans,ans^p[i]);

        return ans;
   }
}seg[maxn<<2];

///两组线性基互插
Seg Merge(Seg a,Seg b)
{
    Seg tmp=b;
    for(int i=0;i<=20;i++)
    {
        if(a.p[i])
            tmp.Insert(a.p[i]);
    }
    return tmp;
}

void buildSeg(int l,int r,int pos)
{
    seg[pos].l=l;
    seg[pos].r=r;

    if(l==r)
    {
        seg[pos].Insert(a[l]);
        return ;
    }

    int mid=seg[pos].mid();
    buildSeg(l,mid,pos<<1);
    buildSeg(mid+1,r,pos<<1|1);

    seg[pos]=Merge(seg[pos<<1],seg[pos<<1|1]);
    seg[pos].l=l;
    seg[pos].r=r;
}

Seg Query(int l,int r,int pos)
{
    if(seg[pos].l==l&&seg[pos].r==r)
        return seg[pos];

    int mid=seg[pos].mid();
    if(r<=mid)
        return Query(l,r,pos<<1);
    else if(l>mid)
        return Query(l,r,pos<<1|1);
    else
        return Merge(Query(l,mid,pos<<1),Query(mid+1,r,pos<<1|1));
}


int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    buildSeg(1,n,1);
    scanf("%d",&q);
    for(int i=1;i<=q;++i)
    {
        int l,r;
        scanf("%d%d",&l,&r);

        Seg ans=Query(l,r,1);

        printf("%d\n",ans.Max());
    }
}
