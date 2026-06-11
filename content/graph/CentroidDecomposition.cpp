/**
 * Author: 
 * Date: 
 * License: 
 * Source: 
 * Description: 
 * Time: 
 * Status: 
 */
vector<vector<int>> adj;
vector<bool> is_removed;
vector<int> subtree_size;

/**
 * DFS to calculate the size of the subtree rooted at ‘node’
 */
int get_subtree_size(int node, int parent = -1) {
    subtree_size[node] = 1;
    for (int child : adj[node]) {
        if (child == parent || is_removed[child]) continue;
        subtree_size[node] += get_subtree_size(child, node);
    }
    return subtree_size[node];
}

/**
 * Returns a centroid of the subtree rooted at 'node'
 * after excluding removed nodes.
 *
 * @param node       - current node
 * @param tree_size  - size of the current subtree
 * @param parent     - parent of the current node
 * @return           - the centroid node
 */
int get_centroid(int node, int tree_size, int parent = -1) {
    for (int child : adj[node]) {
        if (child == parent || is_removed[child]) continue;
        if (subtree_size[child] * 2 > tree_size) {
            return get_centroid(child, tree_size, node);
        }
    }
    return node;
}

/**
 * Recursively builds the centroid decomposition
 *
 * @param node - root of the current subtree
 */
void build_centroid_decomp(int node = 0) {
    int tree_size = get_subtree_size(node);
    int centroid = get_centroid(node, tree_size);

    // Do something with the centroid (e.g., process it)
    
    is_removed[centroid] = true;

    for (int child : adj[centroid]) {
        if (!is_removed[child]) {
            build_centroid_decomp(child);
        }
    }
}
