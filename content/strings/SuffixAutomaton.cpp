/**
 * Author: 
 * Date: 
 * License: 
 * Source: 
 * Description: 
 * Status: 
 */
const int MAXLEN = 250005; 

struct State {
    int len, link;
    int next[26];
    int first_pos; // Stores the 0-indexed ending position of the first occurrence of this state's substring in S
};

State st[MAXLEN * 2];
int sz, last;

int cnt[MAXLEN * 2];        // cnt[i] = Number of times any substring in state i occurs in S
int paths[MAXLEN * 2];      // paths[i] = Number of distinct paths (substrings) starting from state i
int order[MAXLEN * 2];      // Array of state indices sorted by 'len' in descending order
int head[MAXLEN];           // Bucket headers for fast counting-sort by length

void sam_init() {
    st[0].len = 0;
    st[0].link = -1;
    st[0].first_pos = -1;
    memset(st[0].next, -1, sizeof(st[0].next));
    sz = 1;
    last = 0;
}

void sam_extend(char c, int idx) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    st[cur].first_pos = idx; // The substring ends at current character index
    memset(st[cur].next, -1, sizeof(st[cur].next));
    cnt[cur] = 1; // It is a primary prefix state, so initial occurrence count is 1
    
    int p = last;
    int weight = c - 'a';
    
    while (p != -1 && st[p].next[weight] == -1) {
        st[p].next[weight] = cur;
        p = st[p].link;
    }
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[weight];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].first_pos = st[q].first_pos; // Cloned state inherits first occurrence pos
            memcpy(st[clone].next, st[q].next, sizeof(st[q].next));
            st[clone].link = st[q].link;
            cnt[clone] = 0; // Cloned states are not primary prefix states
            
            while (p != -1 && st[p].next[weight] == q) {
                st[p].next[weight] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}

void sam_finalize(int n) {
    for (int i = 0; i <= n; i++) head[i] = 0;
    for (int i = 0; i < sz; i++) head[st[i].len]++;
    for (int i = 1; i <= n; i++) head[i] += head[i - 1];
    for (int i = 0; i < sz; i++) order[--head[st[i].len]] = i;

    // 2. Propagate string frequencies down the Suffix Link Tree
    // Going backwards through 'order' processes longer lengths before shorter lengths
    for (int i = sz - 1; i > 0; i--) {
        int u = order[i];
        if (st[u].link != -1) {
            cnt[st[u].link] += cnt[u];
        }
    }
    cnt[0] = 0; // Root represents empty string, its frequency is irrelevant
    // 3. Calculate path counts via DP (Going from shortest length to longest)
    for (int i = sz - 1; i >= 0; i--) {
        int u = order[i];
        paths[u] = 1; // Staying at node 'u' constitutes a valid terminal choice
        for (int c = 0; c < 26; c++) {
            if (st[u].next[c] != -1) {
                paths[u] += paths[st[u].next[c]];
            }
        }
    }
}

// Recipe A: Get total distinct substrings
int get_distinct_substrings() {
    int total = 0;
    for (int i = 1; i < sz; i++) {
        total += (st[i].len - st[st[i].link].len);
    }
    return total;
}
// Recipe B: Query how many times string P appears in S
int query_occurrence_count(const string &p) {
    int curr = 0;
    for (char c : p) {
        int weight = c - 'a';
        if (st[curr].next[weight] == -1) return 0;
        curr = st[curr].next[weight];
    }
    return cnt[curr];
}
// Bonus Recipe: Returns 0-indexed position where P first appears in S
int query_first_occurrence_idx(const string &p) {
    int curr = 0;
    for (char c : p) {
        int weight = c - 'a';
        if (st[curr].next[weight] == -1) return -1;
        curr = st[curr].next[weight];
    }
    // Ending index minus length of pattern gives the 0-indexed starting index
    return st[curr].first_pos - p.length() + 1;
}

