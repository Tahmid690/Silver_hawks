vector<int> adj[N],jad[N];
int vis[N];
vector<int> ord,scc;

void dfs1(int v) {
    vis[v]=1;
    for (auto u:adj[v]) if(!vis[u]) dfs1(u);
    ord.push_back(v);
}

void dfs2(int v) {
    vis[v] =1;
    scc.push_back(v);
    for (auto u:jad[v]) if(!vis[u]) dfs2(u);
}

for(int i=0;i<n;i++) vis[i]=0;
for(int i=0;i<n;i++) if(!vis[i]) dfs1(i);
for(int i=0;i<n;i++) vis[i]=0;
reverse(all(ord));
for(auto v:ord){
	if(!vis[v]){
		dfs2(v);
            	//process
            	scc.clear();
        }
    }
ord.clear();