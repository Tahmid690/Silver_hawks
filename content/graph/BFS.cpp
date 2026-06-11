vector<int> adj[N]; 
int dis[N], par[N];
 
void bfs(int src){
    memset(dis,-1,sizeof dis);
    dis[src]=0;
    par[src]=-1;
    queue<int>Q;
    Q.push(src);
    while(!Q.empty()){
        int u = Q.front();
        Q.pop();
        for(int v:adj[u]){
            if(dis[v]==-1){
                dis[v]=dis[u]+1;
                par[v]=u;
                Q.push(v);
            }
        }
    }
}
 

void path(int src,int dst){
    vector<int>path;
    int u=dst;
    while(u!=-1){
        path.push_back(u);
        u=par[u];
    }
    reverse(path.begin(),path.end());
    for(int u:path){
        cout<<u<<" ";
    }
    cout<<endl;
}






//0-1 BFS
vector<int> adj[N],cost[N]; 
int bfs(int src){
    fill(dis,dis+mx,1e9);
    dis[src]=0;
    deque<int>Q;
    Q.push_back(src);
    while(!Q.empty()){
        int u = Q.front();
        Q.pop_front();
        for(int i=0;i<adj[u].size();i++){
            int c = cost[u][i];
            int v = adj[u][i];
            if(dis[v] > dis[u]+c){
                dis[v]=dis[u]+c;
                if(c==0) Q.push_front(v);
                else Q.push_back(v);
            }
        }
    }
}