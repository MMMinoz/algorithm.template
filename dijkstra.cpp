#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pli pair<ll ,int >
#define INFll 0x3f3f3f3f3f3f3f3f
#define mem(a,b) memset(a,b,sizeof(a))
const int maxn=1e5+50;

int cnt;
int head[maxn];
struct Edge
{
    int to;
    ll w;
    int next;
}G[maxn*2];
void addEdge(int u,int v,ll w)
{
    G[++cnt]={v,w,head[u]};
    head[u]=cnt;
}
struct Dij
{
    priority_queue<pli ,vector<pli>,greater<pli> >q;
    ll dis[maxn];
    bool vis[maxn];
    void dijkstra(int s,int n)
    {
        while(!q.empty())
            q.pop();
        for(int i=0;i <= n;++i)
        {
            dis[i]=INFll;
            vis[i]=false;
        }
        dis[s]=0;

        q.push({0,s});
        while(!q.empty())
        {
            int u=q.top().second;
            q.pop();

            if(vis[u])
                continue;

            vis[u]=true;
            for(int i=head[u];~i;i=G[i].next)
            {
                int v=G[i].to;
                ll w=G[i].w;
                if(!vis[v]&&dis[v]>dis[u]+w)
                {
                    dis[v]=dis[u]+w;
                    q.push({dis[v],v});
                }
            }
        }
    }
}_dij;
void Init()
{
    cnt=-1;
    mem(head,-1);
}
int main()
{
    Init();
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i <= m;++i)
    {
        int u,v;
        ll w;
        scanf("%d%d",&u,&v);
        scanf("%lld",&w);

        addEdge(u,v,w);
    }

    _dij.dijkstra(1,n);
    cout<<_dij.dis[n]<<endl;
}
