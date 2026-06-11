int parent[N],sz[N];
void make_set(int v) {
    parent[v] = v;
    sz[v] = 1;
}
int find_set(int v) {
    if (v == parent[v]) return v;
    return parent[v]=find_set(parent[v]);
}
void union_sets(int a,int b) {
    a=find_set(a);
    b=find_set(b);
    if (a!=b) {
        if(sz[a]<sz[b]) swap(a,b);
        parent[b]=a;
        sz[a]+=sz[b];
    }
}



vector<pair<int,pii>> edges;
int cost =0;
vector<pair<int,pii>> mst;
for(int i=0;i<n;i++) make_set(i);

sort(all(edges));

for(auto u:edges) {
    if(find_set(u.ss.ff)!=find_set(u.ss.ss)) {
        cost+=u.ff;
        mst.push_back(u);
        union_sets(u.ss.ff,u.ss.ss);
    }
}