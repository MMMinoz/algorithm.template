#include<bits/stdc++.h>
using namespace std;
#define maxn 10008
#define inf 0x3f3f3f3f
int n,m,s,t,cnt;
int head[maxn],cur[maxn],d[maxn];
struct Edge
{
    int v;
    int w;
    int next;
}edge[200008];
inline void add(int u,int v,int w)
{
    edge[++cnt].v=v;
    edge[cnt].w=w;
    edge[cnt].next=head[u];
    head[u]=cnt;
    return;
}

///bfs找增广路
///d[]点的等级 在这条路径中 u->v 则d[v]=d[u]+1
bool bfs()
{
    queue<int> q;
    while(!q.empty())
        q.pop();
    for(int i=1;i<=n;i++)
        d[i]=-1;
    d[s]=0;
    q.push(s);
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next)
        {
            int v=edge[i].v;
            if(d[v]==-1&&edge[i].w>0)
            {
                d[v]=d[u]+1;
                q.push(v);
            }
        }
    }
    return d[t]!=-1;
}

///u^1 由于 正向边和反向边是相邻建的，v=u^1,u=v^1 但是要从0或2 偶数开始才成立
///if(!nowflow) d[u]=-2; 炸点优化 u流量为0后 此次的分层不会再经过u
int dfs(int u,int flow)
{
    int nowflow=0;
    if(u==t) return flow;
    for(int i=cur[u];i!=-1;i=edge[i].next)
    {
        cur[u]=i;
        int v=edge[i].v;
        if(d[v]==d[u]+1&&edge[i].w>0)
        {
            ///多路增广
            /// flow-nowflow ,即u点所能承载的最大流量
            ///nowflow==flow 即不能再增加流量 可以break
            if(int k=dfs(v,min(flow-nowflow,edge[i].w)))
            {
                edge[i].w-=k;
                edge[i^1].w+=k;
                nowflow+=k;
                if(nowflow==flow) 
                    break;
            }
        }
    }
    if(!nowflow) d[u]=-2;
    return nowflow;
}
int Dinic()
{
    int ans=0;
    while(bfs())
    {
        for(int i=1;i<=n;i++)
            cur[i]=head[i];
        ans+=dfs(s,inf);
    }
    return ans;
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&s,&t);
    int u,v,w;
    cnt=-1;
    memset(head,-1,sizeof(head));
    while(m--)
    {
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
        add(v,u,0);
    }
    printf("%d\n",Dinic());
}
