/**
 * Author: 
 * Date: 
 * License: 
 * Source: 
 * Description: 
 * Time: 
 * Status: 
 */
vector<int> g[N],r[N];
stack<int> st;
int vis[N];
vector<int> scc[N];
void dfs1(int x){
	if(vis[x]) return;
	vis[x]=1;
	for(auto u:g[x]){
		if(!vis[u]) dfs1(u);
	}
	st.push(x);
}
void dfs2(int x,int mark){
	if(vis[x]) return;
	vis[x]=1;
	scc[mark].pb(x);
	for(auto u:r[x]){
		if(!vis[u]) dfs2(u,mark);
	}
}
int a[N];
void solve(){
	cin >> n >> m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin >> u >> v;
		g[u].pb(v);
		r[v].pb(u);
	}
	
	for(int i=1;i<=n;i++) dfs1(i);
	memset(vis,0,sizeof vis);
	int marker=0;
	while(!st.empty()){
		int x=st.top();
		st.pop();
		if(!vis[x]) dfs2(x,marker++);
	}
	cout << marker << endl;
	for(int i=0;i<marker;i++){
		for(int j=0;j<scc[i].size();j++){
		}
	} 
}
