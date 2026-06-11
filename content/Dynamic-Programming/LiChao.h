/**
 * Author: 
 * Date: 
 * License: 
 * Source: 
 * Description: 1-based dnc optimization
 * Time: 
 * Status: 
 */
using ll = long long;
const ll INF = 4e18; // Large value for min queries
struct Line {
    ll m, c;
    ll eval(ll x) const {
        return m * x + c;
    }
};
struct Node {
    Line line;
    Node *lc = nullptr;
    Node *rc = nullptr;
    Node(Line l) : line(l), lc(nullptr), rc(nullptr) {}
    ~Node() {
        delete lc; delete rc;
    }
};
class DynamicLiChaoTree {
private:
    Node* root;
    ll L_bound, R_bound;
    void insert(Node*& node, ll l, ll r, Line nw) {
        // If the current node doesn't exist, create it with the new line
        if (!node) {
            node = new Node(nw);
            return;
        }
        ll mid = l + (r - l) / 2;
        bool mid_better = nw.eval(mid) < node->line.eval(mid);
        bool left_better = nw.eval(l) < node->line.eval(l);
        if (mid_better) swap(node->line, nw);
        if (l == r) return;
        if (mid_better != left_better) insert(node->lc, l, mid, nw);
        else insert(node->rc, mid + 1, r, nw);
    }
    ll query(Node* node, ll l, ll r, ll x) {
        if (!node) return INF;   
        ll current_val = node->line.eval(x);
        if (l == r) return current_val;
        ll mid = l + (r - l) / 2;
        if (x <= mid) return min(current_val, query(node->lc, l, mid, x));
        else return min(current_val, query(node->rc, mid + 1, r, x));
    }
    // Optional: Iterative insertion to squeeze out extra speed and prevent stack overhead
    void insert_iterative(Line nw) {
        Node** curr = &root;
        ll l = L_bound, r = R_bound;   
        while (l <= r) {
            if (!(*curr)) {
                *curr = new Node(nw);
                return;
            }
            ll mid = l + (r - l) / 2;
            bool mid_better = nw.eval(mid) < (*curr)->line.eval(mid);
            bool left_better = nw.eval(l) < (*curr)->line.eval(l);
            if (mid_better) swap((*curr)->line, nw);
            if (l == r) break;
            if (mid_better != left_better) {
                curr = &((*curr)->lc);
                r = mid;
            } else {
                curr = &((*curr)->rc);
                l = mid + 1;
            }
        }
    }
public:
    // Define the coordinate boundaries here (e.g., -1e9 to 1e9)
    DynamicLiChaoTree(ll l_bound, ll r_bound) {
        L_bound = l_bound;
        R_bound = r_bound;
        root = new Node(Line{0, INF});
    }
    ~DynamicLiChaoTree() {
        delete root;
    }
    void insert(Line nw) {
        insert(root, L_bound, R_bound, nw);
    }
    ll query(ll x) {
        return query(root, L_bound, R_bound, x);
    }
};