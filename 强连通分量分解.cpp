#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
#define mem(a,b) memset(a,b,sizeof a)
const int maxn=1e5+50;

int n,m;//n个节点,m条边
int head[maxn];
int col[maxn];//标号染色数组
struct Edge
{
    int to;
    int next;
}G[10*maxn];
int cnt;
void addEdge(int u,int v)
{
    G[++cnt].to=v;
    G[cnt].next=head[u];
    head[u]=cnt;
}
struct SCC
{
    bool vis[maxn];
    vector<int> vs;
    void DFS(int u)
    {
        vis[u]=true;
        for(int i=head[u];i;i=G[i].next)
        {
            int v=G[i].to;
            if(!(i&1) || vis[v])///正向边，num为奇数
                continue;
            DFS(v);
        }
        vs.push_back(u);///拓扑序
    }
    void RDFS(int u,int k)///反向求解强连通分量
    {
        vis[u]=true;
        col[u]=k;
        for(int i=head[u];i;i=G[i].next)
        {
            int v=G[i].to;
            if((i&1) || vis[v])///反向边，num为偶数
                continue;
            RDFS(v,k);
        }
    }
    int scc()
    {
        vs.clear();
        mem(vis,false);
        for(int i=1;i <= n;++i)///注意编号，根据题意而定，有的是从0开始的
            if(!vis[i])
                DFS(i);

        int k=0;
        mem(vis,false);
        for(int i=vs.size()-1;i >= 0;--i)///从拓扑序的最大值开始查找SCC
            if(!vis[vs[i]])
                RDFS(vs[i],++k);
                
        return k;///强连通分量的个数
    }
}_scc;
void Init()
{
    cnt=0;
}
