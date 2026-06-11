/**
 * Author: 
 * Date: 
 * License: 
 * Source: 
 * Description: 
 * Time: 
 * Status: 
 */
int n,v[N];
int sz[N];
int st[N],ft[N],tym,koi[N];
 
void dfs(int u,int p){
    sz[u]=1;
    st[u]=tym;
    koi[tym++]=u;
    for(int v:g[u]){
        if(v==p) continue;
        dfs(v,u);
        sz[u]+=sz[v];
    }
    ft[u]=tym;
}
 
int cnt[N],tot,ans[N];
 
void add(int x){
    cnt[v[x]]++;
    if(cnt[v[x]]==1) tot++;
}
void rmv(int x){
    cnt[v[x]]--;
    if(cnt[v[x]]==0) tot--;
}
 
void dsu(int u,int p,int keep){
    int mxsz=-1,bigchild=-1;
    for(auto v:g[u]){
        if(v==p) continue;
        if(mxsz<sz[v]){
            mxsz=sz[v];
            bigchild=v;
        }
    }
    for(auto v:g[u]){
        if(v==bigchild || v==p) continue;
        dsu(v,u,0);
    }
    if(bigchild!=-1) dsu(bigchild,u,1);
    for(auto v:g[u]){
        if(v==bigchild || v==p) continue;
        for(int i=st[v];i<ft[v];i++){
            add(koi[i]);
        }
    }
    add(u);
 
    ans[u]=tot;
    
    if(!keep){
        for(int i=st[u];i<ft[u];i++) rmv(koi[i]);
    }
 
}
void solve(){
    dfs(1,0);
    dsu(1,0,1);
    for(int i=1;i<=n;i++) cout << ans[i] << " ";
}