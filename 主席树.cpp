#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+50;

int cnt,root[maxn];///每棵树的根
int a[maxn],b[maxn];///b离散化数组
struct node
{
    int l,r;
    int sum;
    node(){sum=0;}
}seg[maxn*25];

void Init()
{
    cnt=0;
    seg[0].l=0,seg[0].r=0;
    root[0]=0;
}

void build(int l,int r,int &rt)///以前序遍历的方式建树
{
    rt=++cnt;///rt为编号
    if(l==r)
        return ;
    int mid=(r+l)>>1;

    build(l,mid,seg[rt].l);
    build(mid+1,r,seg[rt].r);
}

void update(int l,int r,int &rt,int pos)
{
    seg[++cnt]=seg[rt];///复制前一棵树
    rt=cnt;///因为对新树进行操作，是rt为新树
    seg[rt].sum++;///进行操作了，个数+1

    if(l==r)
        return ;
    int mid=(r+l)>>1;
    if(mid>=pos)
        return update(l,mid,seg[rt].l,pos);
    else
        return update(mid+1,r,seg[rt].r,pos);
}

int query(int L,int R,int l,int r,int k)
{
    int d=seg[seg[R].l].sum-seg[seg[L].l].sum;///利用区间可减性，左子树上一共有d个数
    if(l==r)
        return b[l];

    int mid=(l+r)>>1;
    if(d>=k)///利用 左子树<右子树 前d个在左子树上，其他的在右子树上
        return query(seg[L].l,seg[R].l,l,mid,k);
    else///右子树第一个是第d+1个 找第k个也就是找右子树的第k-d个
        return query(seg[L].r,seg[R].r,mid+1,r,k-d);
}

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        
        int n,m;
        cin>>n>>m;

        for(int i=1;i<=n;i++)
            cin>>a[i],b[i]=a[i];
        
        ///离散化
        sort(b+1,b+1+n);
        int len=unique(b+1,b+n+1)-(b+1);
        
        Init();
        build(1,len,root[0]);
        for(int i=1;i<=n;i++)
        {
            root[i]=root[i-1];///复制前一个树
            int k=upper_bound(b+1,b+1+len,a[i])-b;
            update(1,len,root[i],k-1);
        }

        while(m--)
        {
            int L,R,k;
            cin>>L>>R>>k;
            cout<<query(root[L-1],root[R],1,len,k)<<endl;
        }
    }
}
