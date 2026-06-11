/**
 * Author: Benjamin Qi, Oleksandr Kulkov, chilli
 * Date: 2020-01-12
 * License: CC0
 * Source: https://codeforces.com/blog/entry/53170, https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
 * Description: Decomposes a tree into vertex disjoint heavy paths and light
 * edges such that the path from any leaf to the root contains at most log(n)
 * light edges. Code does additive modifications and max queries, but can
 * support commutative segtree modifications/queries on paths and subtrees.
 * Takes as input the full adjacency list. VALS\_EDGES being true means that
 * values are stored in the edges, as opposed to the nodes. All values
 * initialized to the segtree default. Root must be 0.
 * Time: O((\log N)^2)
 * Status: stress-tested against old HLD
 */

#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
 
template <typename T> using o_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename R> using o_map = tree<T, R, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
// #define int long long
#define endl "\n"
#define ff first
#define ss second
 
const int mod=1000000007;
const int N=200005;
 
int n,v[N],q;
vector<int> g[N];
 
struct segtree{
  // int tree[4*N]={0};
  // void update(int node,int l,int r,int p,int x){
  //   if(p<l || p>r) return;
  //   if(l==r){ tree[node]=x; return;}
  //   update(node*2,l,(l+r)/2,p,x);
  //   update(node*2+1,(l+r)/2 +1,r,p,x);
  //   tree[node]=max(tree[node*2],tree[node*2+1]);
  // }
  // int query(int node,int l,int r,int a,int b){
  //   if(r<a || l>b) return 0;
  //   if(l>=a && r<=b) return tree[node];
  //   return max(query(node*2,l,(l+r)/2,a,b),query(node*2+1,(l+r)/2 +1,r,a,b));
  // }
  int st[4*N]={0};
 
  void update(int idx, int val) {
    st[idx += n] = val;
    for (idx /= 2; idx; idx /= 2) st[idx] = max(st[2 * idx], st[2 * idx + 1]);
  }
 
  int query(int lo, int hi) {
    int ra = 0, rb = 0;
    for (lo += n, hi += n + 1; lo < hi; lo /= 2, hi /= 2) {
      if (lo & 1) ra = max(ra, st[lo++]);
      if (hi & 1) rb = max(rb, st[--hi]);
    }
    return max(ra, rb);
}
}sg;
 
 
 
int sz[N],dep[N],par[N];
void dfs(int x,int p){
  sz[x]=1;
  dep[x]=dep[p]+1;
  par[x]=p;
  for(auto u:g[x]){
    if(u==p) continue;
    dfs(u,x);
    sz[x]+=sz[u];
  }
}
 
int matha[N],konchain[N],koi[N];
int chain_count=1,idx=1;
 
void hld(int u,int p){
  if(!matha[chain_count]) matha[chain_count]=u;
  konchain[u]=chain_count;
  koi[u]=idx++;
 
  int heavy=-1,siz=-1;
  for(auto v:g[u]){
    if(v==p) continue;
    if(sz[v]>siz){
      siz=sz[v];
      heavy=v;
    }
  }
  if(heavy!=-1) hld(heavy,u);
 
  for(auto v:g[u]){
    if(v==p || v==heavy) continue;
    chain_count++;
    hld(v,u);
  }
 
}
 
int path_qry(int u,int v){
  int ans=0;
  while(konchain[u]!=konchain[v]){
    if(dep[matha[konchain[u]]]<dep[matha[konchain[v]]]) swap(u,v);
    ans=max(ans,sg.query(koi[matha[konchain[u]]],koi[u]));
    u=par[matha[konchain[u]]];
  }
  if(koi[u]>koi[v]) swap(u,v);
  ans=max(ans,sg.query(koi[u],koi[v]));
  return ans;
}
void node_upd(int u,int x){
  sg.update(koi[u],x);
}
 
 
 
void solve(){
    cin >> n >> q;
    for(int i=1;i<=n;i++) cin >> v[i];
    for(int i=1;i<n;i++){
      int u,v;
      cin >> u >> v;
      g[u].push_back(v);
      g[v].push_back(u);
    }
    dfs(1,0);
    hld(1,0);
    for(int i=1;i<=n;i++) node_upd(i,v[i]);
 
    while(q--){
      int typ;
      cin >> typ;
      if(typ==1){
        int s,x;
        cin >> s >> x;
        node_upd(s,x);
      }
      else{
        int u,v;
        cin >> u >> v;
        cout << path_qry(u,v) << " ";
      }
    }
 
}
 
 
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t=1;
    // cin >> t;
 
    while(t--){
        solve();
    }
}
