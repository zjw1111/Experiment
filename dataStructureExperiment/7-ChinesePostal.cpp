//kopyh
#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
#define N 112
using namespace std;
class ChinesePostal
{
private:
    //邮路节点数和路径数
    int n,m;
    //节点间路径个数及路径长度
    int g[N][N],f[N][N];
    int tmp[N],ans[N],pos[N],res,vis[N],sum,prior;
    struct node
    {
        int v;
        int c;
        node(int _v=0,int _c=0):v(_v),c(_c) {}
        bool operator <(const node &r)const
        {
            return c>r.c;
        }
    };
    struct edge
    {
        int v;int cost;
        edge(int _v=0,int _cost=0):v(_v),cost(_cost) {}
    };
    vector<edge>E[N];
    int dist[N],ff[N];
    vector<int>road[N][N];
    void addedge(int u,int v,int w)
    {
        E[u].push_back(edge(v,w));
        E[v].push_back(edge(u,w));
        road[u][v].push_back(0);
        road[v][u].push_back(0);
    }
    //Dijkstra计算最短路
    void Dijkstra(int start)
    {
        memset(vis,false,sizeof(vis));
        for(int i=1;i<=n;i++)dist[i]=INF;
        for(int i=1;i<=n;i++)ff[i]=i;
        priority_queue<node>q;
        while(!q.empty())q.pop();
        dist[start]=0.0;
        q.push(node(start,0.0));
        node t;
        while(!q.empty())
        {
            t=q.top();
            q.pop();
            int u=t.v;
            if(vis[u])continue;
            vis[u]=true;
            for(int i=0; i<E[u].size(); i++)
            {
                int v=E[t.v][i].v;
                int cost=E[u][i].cost;
                if(!vis[v]&&dist[v]>dist[u]+cost)
                {
                    dist[v]=dist[u]+cost;
                    ff[v]=u;
                    q.push(node(v,dist[v]));
                }
            }
        }
    }
    void putRoad(int x)
    {
        for(int i=1;i<=n;i++)
            if(x!=i && road[x][i].empty())
            {
                int y=ff[i];
                while(y!=x)
                {
                    road[i][x].push_back(y);
                    y=ff[y];
                }
                for(int j=road[i][x].size()-1;j>=0;j--)
                    road[x][i].push_back(road[i][x][j]);
            }
    }
    //寻找最优二分点对组合
    void tryTo(int u,int flag,int now,int val)
    {
        if(now==sum)
        {
            if(res>val)
            {
                val=res;
                memcpy(ans,tmp,sizeof(tmp));
            }
            return;
        }
        for(int i=0;i<sum;i++)
            if(!vis[pos[i]])
            {
                if(flag)
                {
                    tmp[u]=pos[i];tmp[pos[i]]=u;
                    vis[pos[i]]=1;
                    tryTo(pos[i],0,now+1,val+f[u][pos[i]]);
                    vis[pos[i]]=0;
                }
                else
                {
                    vis[pos[i]]=1;
                    tryTo(pos[i],1,now+1,val);
                    vis[pos[i]]=0;
                }
            }
    }
    //补边构建欧拉图
    void operate()
    {
        for(int i=0;i<sum;i++)
        {
            Dijkstra(pos[i]);
            for(int j=1;j<=n;j++)
                f[pos[i]][j]=f[j][pos[i]]=dist[j];
            putRoad(pos[i]);
        }
        memset(vis,false,sizeof(vis));
        res=INF;
        tryTo(0,0,0,0);
        for(int i=0;i<sum;i++)
            g[pos[i]][ans[pos[i]]]++;
    }
    //fleury算法寻找欧拉回路
    stack<int> st;
    void dfs(int u)
    {
        for(int i=1;i<=n;i++)
            if(g[u][i])
            {
                g[u][i]--,g[i][u]--;
                st.push(i);
                dfs(i);
                break;
            }
    }
    void fleury(int u)
    {
        while(!st.empty())st.pop();
        st.push(u);
        while(!st.empty())
        {
            int flag=1;
            for(int i=1;i<=n;i++)
                if(g[st.top()][i])
                {
                    flag=0;
                    break;
                }
            if(flag)
            {
                int t=st.top(); st.pop();
                if(prior && road[prior][t][0]!=0)
                {
                    for(int i=0;i<road[prior][t].size();i++)
                        printf("%d ",road[prior][t][i]);
                }
                printf("%d ",t);
                prior=t;
            }
            else
                dfs(st.top());
        }
    }
    //判断奇数点个数判断是否需要补边
    void solve()
    {
        for(int i=1;i<=n;i++)
        {
            int now=0;
            for(int j=1;j<=n;j++)
                now+=g[i][j];
            if(now&1)pos[sum++]=i;
        }
        if(sum)operate();
        fleury(1);
        printf("\n");
    }
    void init()
    {
        memset(g,0,sizeof(g));
        memset(f,0x3f,sizeof(f));
        for(int i=1;i<=n;i++)E[i].clear();
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                road[i][j].clear();
        prior=0;sum=0;
    }
public:
    void input()
    {
        int x,y,z;
        scanf("%d%d",&n,&m);
        init();
        for(int i=0;i<m;i++)
        {
            scanf("%d%d%d",&x,&y,&z);
            g[x][y]=g[y][x]=1;
            f[x][y]=f[y][x]=z;
            addedge(x,y,z);
        }
        solve();
    }
}CP;

int main()
{
    freopen("test.txt","r",stdin);
    CP.input();
    return 0;
}



