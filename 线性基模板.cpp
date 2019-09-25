ll n;
ll p[65];

///插入
void Insert(ll x)
{
    for(int i=60;i>=0;i--)
    {
        if(x&(1ll<<i))
        {
            if(!p[i])
            {
                p[i]=x;
                break;
            }
            x^=p[i];
        }
    }
}


///查找
bool Find(ll x)
{
    for(int i=60;i>=0;i--)
    {
        if(x&(1ll<<i))
        {
            if(!p[i])
            {
                p[i]=x;
                return true;
            }
            x^=p[i];
        }
    }
    return false;
}


///最大值
ll get_Max()
{
    ll ans=0;
    for(int i=60;i>=0;i--)
        if(x&(1ll<<i))
            ans=max(ans,ans^p[i]);
    
    return ans;
}


///最小值
ll get_Min()
{
    for(int i=0;i<=60;i++)
        if(p[i])
            return p[i];
}


///第k大
ll cnt=0;
ll th[65];
void rebuild()
{
    for(int i=60;i>=0;i--)
        for(int j=i-1;j>=0;j--)
            if(p[i]&(1ll<<j))
                p[i]^=p[j];

    for(int i=0;i<=60;i++)
        if(p[i])
            th[cnt++]=p[i];
}
ll kthquery(ll x)
{
    if (x>=(1ll<<cnt))
        return -1;
    ll ans=0;
    for(ll j=60;j>=0;j--)
        if ((x&1ll<<j))
            ans^=th[j];

    return ans;
}

///在求第k大时里面是包括 0 的
///但是并不是所有的都可以异或出来 0 
///如果构造出来的线性基有 k 位不为 1
///那么说明每个数都提供了 1，则说明不会异或出 0 ，否则可以。
if(cnt!=n)
    x--;
printf("%lld\n", kthquery(x));
