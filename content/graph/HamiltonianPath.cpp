/**
 * Author: 
 * Date: 
 * License: 
 * Source: 
 * Description: 
 * Time: 
 * Status: 
 */
int n;                                    
vector<vector<int>> adj;                  
vector<bool> visited;                     
vector<int> path;                         
bool foundHamiltonian = false;            
void dfsHamiltonian(int u, int depth) {
    if (foundHamiltonian) return;
    visited[u] = true;
    path.push_back(u);
    if (depth == n) {
        foundHamiltonian = true;
        return;
    }
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfsHamiltonian(v, depth + 1);
            if (foundHamiltonian) return;
        }
    }
    visited[u] = false;
    path.pop_back();
}
bool findHamiltonianPath() {
    // optional: sort neighbors for deterministic order
    for (int u = 1; u <= n; ++u)
        sort(adj[u].begin(), adj[u].end());
    for (int start = 1; start <= n; ++start) {
        fill(visited.begin(), visited.end(), false);
        path.clear();
        foundHamiltonian = false;
        dfsHamiltonian(start, 1);
        if (foundHamiltonian) {
            cout << "Hamiltonian Path found starting at " << start << ": ";
            for (int x : path) cout << x << ' ';
            cout << "\n";
            return true;
        }
    }
    cout << "No Hamiltonian Path exists.\n";
    return false;
}
