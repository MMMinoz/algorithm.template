#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
#define mem(a,b) memset(a,b,sizeof(a))
const int maxn=1e5+5;
int n,m,s,t;

struct Edge
{
    int v,w;
    int next;
}e[maxn<<1];

int head[maxn],cnt;
void addEdge(int u,int v,int w)
{
    e[++cnt]={v,w,head[u]};
    head[u]=cnt;
    e[++cnt]={u,0,head[v]};
    head[v]=cnt;
}

struct Dinic
{
    int cur[maxn],d[maxn];
    bool bfs()
    {
        queue<int> q;
        for(int i=0;i<=n+m+6;i++)
            d[i]=-1;
        d[s]=0;
        q.push(s);
        while(!q.empty())
        {
            int u=q.front();
            q.pop();
            for(int i=head[u];i!=-1;i=e[i].next)
            {
                int v=e[i].v;
                if(d[v]==-1&&e[i].w>0)
                {
                    d[v]=d[u]+1;
                    q.push(v);
                }
            }
        }
        return d[t]!=-1;
    }

    int dfs(int u,int flow)
    {
        int nowflow=0;
        if(u==t) return flow;
        for(int i=cur[u];i!=-1;i=e[i].next)
        {
            cur[u]=i;
            int v=e[i].v;
            if(d[v]==d[u]+1&&e[i].w>0)
            {
                if(int k=dfs(v,min(flow-nowflow,e[i].w)))
                {
                    e[i].w-=k;
                    e[i^1].w+=k;
                    nowflow+=k;
                    if(nowflow==flow)
                        break;
                }
            }
        }
        if(!nowflow) d[u]=-2;
        return nowflow;
    }
    int din()
    {
        int ans=0;
        while(bfs())
        {
            for(int i=0;i<=n+m+6;i++)
                cur[i]=head[i];

            ans+=dfs(s,INF);
        }
        return ans;
    }
}_din;


void Init()
{
    mem(head,-1);
    cnt=-1;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        Init();
        scanf("%d%d",&m,&n);
        s=0,t=m+n+1;
        int sum=0;
        ///源点与项目(正权值)
        for(int i=1;i<=m;i++)
        {
            int a;
            scanf("%d",&a);
            sum+=a;
            addEdge(s,i,a);
        }
        ///工作者(负权值)与汇点
        for(int i=1;i<=n;i++)
        {
            int b;
            scanf("%d",&b);
            addEdge(i+m,t,b);
        }
        ///项目与工作者
        for(int i=1;i<=m;i++)
        {
            int k;
            scanf("%d",&k);
            while(k--)
            {
                int v;
                scanf("%d",&v);
                v++;
                addEdge(i,v+m,INF);
            }
        }
        ///所有权值为正的权值之和-最大流
        printf("%d\n",sum-_din.din());
    }
}
