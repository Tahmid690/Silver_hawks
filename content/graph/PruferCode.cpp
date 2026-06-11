/**
 * Author: 
 * Date: 
 * License: 
 * Source: 
 * Description: Converts a labeled tree to its Prufer code sequence.
 * A Prufer code is a unique sequence of n-2 integers that represents
 * a labeled tree with n vertices. Repeatedly removes the smallest
 * leaf and adds its parent to the sequence. Used for counting
 * labeled trees (Cayley's formula: $n^(n-2)$ trees on n vertices).
 * To convert a labeled tree into its Prüfer code, follow these steps until only two nodes remain:
 * 1. Find the leaf (node with degree 1) with the smallest label.
 * 2. Add the label of its only neighbor to the sequence.
 * 3. Remove that leaf from the tree.
 * 4. Repeat the process until only two nodes are left.
 * Time: O(n)
 * Status: 
 */
vector<int> pruefer_code() {
    int n = adj.size();
    parent[n-1] = -1;
    dfs(n-1); //save parents
    int ptr = -1;
    vector<int> degree(n);
    for (int i = 0; i < n; i++) {
        degree[i] = adj[i].size();
        if (degree[i] == 1 && ptr == -1)
            ptr = i;
    }
    vector<int> code(n - 2);
    int leaf = ptr;
    for (int i = 0; i < n - 2; i++) {
        int next = parent[leaf];
        code[i] = next;
        if (--degree[next] == 1 && next < ptr) {
            leaf = next;
        } else {
            ptr++;
            while (degree[ptr] != 1)
                ptr++;
            leaf = ptr;
        }
    }
    return code;
}