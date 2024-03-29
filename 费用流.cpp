#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define INF 0x3f3f3f3f
#define mem(a,b) memset(a,b,sizeof(a))
const int maxn=1e5+5;
int n,m,s,t;
int head[maxn],cnt;
struct Edge
{
    int v,flow,dis;
    int next;
}e[maxn];
void addEdge(int u,int v,int flow,int dis)
{
    e[++cnt]={v,flow,dis,head[u]};
    head[u]=cnt;
    e[++cnt]={u,0,-dis,head[v]};
    head[v]=cnt;
}

struct MCMF
{
    int dis[maxn],pre[maxn],last[maxn];
    bool vis[maxn];
    int flow[maxn];
    bool spfa()
    {
        mem(dis,INF);
        mem(flow,INF);
        mem(vis,0);
        queue<int> q;

        q.push(s);
        vis[s]=1;
        dis[s]=0;
        pre[t]=-1;

        while(!q.empty())
        {
            int u=q.front();
            q.pop();
            vis[u]=0;
            for(int i=head[u];~i;i=e[i].next)
            {
                int v=e[i].v;
                if(e[i].flow&&dis[v]>dis[u]+e[i].dis)
                {
                    dis[v]=dis[u]+e[i].dis;
                    pre[v]=u;
                    last[v]=i;
                    flow[v]=min(flow[u],e[i].flow);
                    if(!vis[v])
                    {
                        vis[v]=1;
                        q.push(v);
                    }
                }
            }
        }
        return pre[t]!=-1;
    }

    int maxflow;ll mincost;
    int mcmf()
    {
        mincost=0,maxflow=0;
        while(spfa())
        {
            ll flow=INF;
            for(int i=t;i!=s;i=pre[i])
                flow=min(flow,(ll)e[last[i]].flow);
            mincost+=dis[t]*flow;
            maxflow+=flow;
            for(int i=t;i!=s;i=pre[i])
            {
                e[last[i]].flow-=flow;
                e[last[i]^1].flow+=flow;
            }
        }
        return mincost;
    }
}_mcmf;

void Init()
{
    mem(head,-1);
    cnt=-1;
}
int main()
{
    mem(head,-1);
    cnt=-1;
    scanf("%d%d%d%d",&n,&m,&s,&t);

    for(int i=1;i<=m;i++)
    {
        int u,v,f,d;
        scanf("%d%d%d%d",&u,&v,&f,&d);

        ///最小费用
        addEdge(u,v,f,d);
        ///最大费用
        addEdge(u,v,-f,d);
    }
    _mcmf.mcmf();
    ///最大费用 -(_mcmf.mincost)
    printf("%d %d",_mcmf.maxflow,_mcmf.mincost);
    return 0;
}
