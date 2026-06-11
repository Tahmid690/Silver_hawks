int n,m,u,v,vis[N],f;
vii g[N];
vii order;
void dfs(int s){
	vis[s]=1;
	for(int x:g[s]){
		if(vis[x]==0) dfs(x);
		else if(vis[x]==1) f=1;
	}
	order.pb(s);
	vis[s]=2;
}
void solve(){
	cin >> n >> m;
	while(m--){
		cin >> u >> v;
		g[u].pb(v);
	}
	for(int i=1;i<=n;i++) if(vis[i]==0) dfs(i);
	reverse(all(order));
	if(!f) for(int x:order) cout << x << " ";
	else cout << "IMPOSSIBLE" << endl;
}
