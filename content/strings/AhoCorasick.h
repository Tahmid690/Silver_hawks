/**
 * Author: Simon Lindholm
 * Date: 2015-02-18
 * License: CC0
 * Source: marian's (TC) code
 * Description: Aho-Corasick automaton, used for multiple pattern matching.
 * Time: construction takes $O(26N)$, where $N =$ sum of length of patterns.
 * Status: stress-tested
 */
struct AhoCorasick {
    static const int K = 26;
    
    struct Node {
        int next[K];
        int fail = 0;

        Node() {
            fill(next, next + K, -1);
        }
    };

    vector<Node> t;
    vector<int> end_node; // end_node[i] = the node index where pattern i ends
    vector<vector<int>> fail_tree; // Adjacency list for the Fail Tree
    vector<int> cnt; // To store visit counts for each node

    AhoCorasick() {
        t.emplace_back();
    }

    // Insert pattern with a specific ID (0-indexed)
    void insert(const string& s, int id) {
        int u = 0;
        for (char c : s) {
            int v = c - 'a';
            if (t[u].next[v] == -1) {
                t[u].next[v] = t.size();
                t.emplace_back();
            }
            u = t[u].next[v];
        }
        if (id >= end_node.size()) end_node.resize(id + 1);
        end_node[id] = u;
    }

    void build() {
        queue<int> q;
        for (int i = 0; i < K; i++) {
            if (t[0].next[i] != -1) {
                q.push(t[0].next[i]);
            } else {
                t[0].next[i] = 0;
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int i = 0; i < K; i++) {
                if (t[u].next[i] != -1) {
                    t[t[u].next[i]].fail = t[t[u].fail].next[i];
                    q.push(t[u].next[i]);
                } else {
                    t[u].next[i] = t[t[u].fail].next[i];
                }
            }
        }

        fail_tree.assign(t.size(), vector<int>());
        for (int i = 1; i < t.size(); i++) {
            fail_tree[t[i].fail].push_back(i);
        }
    }
    void dfs_propagate(int u) {
        for (int v : fail_tree[u]) {
            dfs_propagate(v);
            cnt[u] += cnt[v];
        }
    }
    // Returns a vector where result[i] is the number of times pattern i appeared
    vector<int> query_all_patterns(const string& text, int num_patterns) {
        cnt.assign(t.size(), 0);
        int u = 0;
        for (char c : text) {
            u = t[u].next[c - 'a'];
            cnt[u]++; 
        }
        dfs_propagate(0); 
        vector<int> result(num_patterns);
        for (int i = 0; i < num_patterns; i++) {
            result[i] = cnt[end_node[i]];
        }
        return result;
    }
};