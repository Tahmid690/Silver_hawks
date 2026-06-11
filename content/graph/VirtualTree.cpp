/**
 * Author: 
 * Date: 
 * License: 
 * Source: 
 * Description: 
 * Time: 
 * Status: 
 */
//Add LCA.cpp before using this
vector<pair<int, int>> adj_vt[N]; 
bool is_key[N];

void add_vt_edge(int u, int v) {
    int w = depth[v] - depth[u]; 
    adj_vt[u].push_back({v, w});
    adj_vt[v].push_back({u, w});
}

void build_virtual_tree(vector<int>& nodes) {
    auto cmp = [&](int a, int b) { return tin[a] < tin[b]; };
    sort(nodes.begin(), nodes.end(), cmp);
    vector<int> st;
    st.push_back(1);
    for (int u : nodes) {
        if (u == 1) continue;
        int lca = get_lca(u, st.back());
        if (lca != st.back()) {
            while (st.size() > 1 && depth[st[st.size() - 2]] >= depth[lca]) {
                add_vt_edge(st[st.size() - 2], st.back());
                st.pop_back();
            }
            if (st.back() != lca) {
                add_vt_edge(lca, st.back());
                st.pop_back();
                st.push_back(lca);
            }
        }
        st.push_back(u);
    }
    while (st.size() > 1) {
        add_vt_edge(st[st.size() - 2], st.back());
        st.pop_back();
    }
}
void solve(){
    timer = 0;
    dfs_lca(1, 1, 0);
    cin >> q;
    while(q--){
        int k;
        cin >> k;
        vector<int> Q;
        Q.resize(k);
        for(int i=0;i<k;i++){
            cin >> Q[i];
            is_key[Q[i]]=true;
        }
        build_virtual_tree(Q);
        //Use the virtual tree stored in adj_vt for processing
        function<void(int, int)> cleanup = [&](int u, int p) {
            is_key[u] = false;
            for (auto& edge : adj_vt[u]) {
                int v = edge.first;
                if (v != p) cleanup(v, u);
            }
            adj_vt[u].clear();
        };
        cleanup(1, -1);
    }

}