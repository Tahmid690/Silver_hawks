/**
 * Author: 
 * Date: 
 * License: 
 * Source: 
 * Description: 
 * Time: 
 * Status: 
 */
#define mx 100005
vector<int> adj[mx];
vector<ll> cost[mx];
ll dis[mx];
 
void dijkstra(int src){
    fill(dis,dis+mx,1e16+9);
    dis[src]=0;
    priority_queue<pair<ll,int>> Q;
    Q.push({0,src});
    while(!Q.empty()){
        int u=Q.top().second,x=Q.top().first;
        Q.pop();
        if(dis[u]<-x) continue;
        for(int i=0;i<adj[u].size();i++){
            int v=adj[u][i],c=cost[u][i];
            if(dis[v]>dis[u]+c){
                dis[v]=dis[u]+c;
                Q.push({-dis[v],v});
            }
        }
    }
}