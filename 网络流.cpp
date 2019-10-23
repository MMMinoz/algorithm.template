#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
#define INF 0x3f3f3f3f
#define mem(a,b) memset(a,b,sizeof(a))
const int maxn=100010;
bool vis[maxn];
int n,m,s,t;
int dis[maxn],pre[maxn],last[maxn],flow[maxn];
int maxflow,mincost;
//dis最小花费;pre每个点的前驱；last每个点的所连的前一条边；flow源点到此处的流量
struct Edge
{
    int v,flow,dis;//flow流量 dis花费
    int next;
}e[maxn];
int head[maxn],cnt;

void addEdge(int u,int v,int flow,int dis)
{
    e[++cnt]={v,flow,dis,head[u]};
    head[u]=cnt;
    e[++cnt]={u,0,-dis,head[v]};
    head[v]=cnt;
}

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
            if(e[i].flow>0&&dis[v]>dis[u]+e[i].dis)//正边
            {
                dis[v]=dis[u]+e[i].dis;
                pre[v]=u;
                last[v]=i;
                flow[v]=min(flow[u],e[i].flow);//
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

void MCMF()
{
    while(spfa())
    {
        int now=t;
        maxflow+=flow[t];
        mincost+=flow[t]*dis[t];
//        for(int now=t;now!=s;now=pre[now])
        while(now!=s)
        {//从源点一直回溯到汇点
            e[last[now]].flow-=flow[t];
            e[last[now]^1].flow+=flow[t];
            now=pre[now];
        }
    }
}

int main()
{
    mem(head,-1);
    cnt=-1;
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for (int i=1;i<=m;i++)
    {
        int u,v,f,d;
        scanf("%d%d%d%d",&u,&v,&f,&d);
        addEdge(u,v,f,d);
    }
    MCMF();
    printf("%d %d",maxflow,mincost);
    return 0;
}
