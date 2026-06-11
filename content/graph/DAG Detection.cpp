// "Say:He is the Most Merciful,We have believed in him and upon him we have relied" [67:29]
#include<bits/stdc++.h>
using namespace std;
                                                     
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
*/
 
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef pair<int,int> pii;
typedef vector<ll> vll;
typedef vector<int> vii;
typedef map<int,int> mpi;
typedef map<ll,ll> mpl;
typedef unordered_map<int,int> umpi;
typedef unordered_map<ll,ll> umpl;
 
#define ump unordered_map
#define mod 1000000007
#define inf 1000000000000000006
#define ff first
#define ss second
#define pb push_back
#define all(v) v.begin(), v.end()
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
#define pi acos(-1.0)
#define siz(v) (int)(v).size()
#define N 200006
#define int long long

int n,m,cs=-1,ce=-1,u,v,vis[N],par[N];
vii adj[N];

void dfs(int s){
	vis[s]=1;
	for(auto e:adj[s]){
		if(vis[e]==0){
			par[e]=s;
			dfs(e);
		}
		else if(vis[e]==1){
			cs=e;
			ce=s;
		}
	}
	vis[s]=2;
}
void solve(){
	cin >> n >> m;
	while(m--){
		cin >> u >> v;
		adj[u].pb(v);
	}
	for(int i=0;i<n;i++) if(!vis[i+1]) dfs(i+1);
	
	if(cs==-1) cout << "IMPOSSIBLE" << endl;
	else{
		vii path;
		path.pb(cs);
		for(int i=ce;i!=cs;i=par[i]) path.pb(i);
		path.pb(cs);
		reverse(all(path));
		cout << path.size() << endl;
		for(auto x:path) cout << x << " ";
		cout << endl;
	}
}
signed main(){
    fastio;
    int T=1,cs=0;
    //cin >> T;
    while(T--){
    	//cout << "Case " << ++cs << " " << ; 
    	solve();
    } 
}