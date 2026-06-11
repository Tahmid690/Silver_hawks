/**
 * Author: 
 * Date: 
 * License: 
 * Source: 
 * Description: 
 * Time: 
 * Status: 
 */
const int mod=1000000007;
const int N=200005;
 
int n,v[N],q;
vector<int> g[N];
 
struct segtree{
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
    dfs(1,0);
    hld(1,0);
	node_upd(s,x);
	path_qry(u,v);
}
