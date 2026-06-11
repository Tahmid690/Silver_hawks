/**
 * Author: 
 * Date: 
 * License: 
 * Source: 
 * Description: 
 * Time: 
 * Status: 
 */
vii adj[N];
int dt[N],low[N],vis[N];
int timer=0;
vector<pii> bridges;
void dfs(int v,int p){
	vis[v]=1;
	dt[v]=low[v]=timer++;
	for(auto u:adj[v]){
		if(u==p) continue;
		if(vis[u]) low[v]=min(low[v],dt[u]);
		else{
			dfs(u,v);
			low[v]=min(low[v],low[u]);
			if(low[u]>dt[v]) bridges.pb({v,u});
		}
	}
}

for(int i=1;i<=n;i++){
		vis[i]=0;
		dt[i]=-1;
		low[i]=-1;
	} 
	for(int i=1;i<=n;i++){
		if(!vis[i]) dfs(i,-1);
	}