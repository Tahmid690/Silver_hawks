/**
 * Author: 
 * Date: 
 * License: 
 * Source: 
 * Description: 
 * Time: 
 * Status: 
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node{
    int val, pr, sz;
    ll sum;
    bool rev;
    Node *l, *r;
    Node(int v): val(v), pr(rand()<<16 ^ rand()), sz(1), sum(v), rev(false), l(nullptr), r(nullptr){}
};

int sz(Node* t){ return t ? t->sz : 0; }
ll sum(Node* t){ return t ? t->sum : 0; }

void pull(Node* t){
    if(!t) return;
    t->sz = 1 + sz(t->l) + sz(t->r);
    t->sum = t->val + sum(t->l) + sum(t->r);
}

void apply_rev(Node* t){
    if(!t) return;
    t->rev ^= 1;
    swap(t->l, t->r);
}

void push(Node* t){
    if(!t || !t->rev) return;
    if(t->l) apply_rev(t->l);
    if(t->r) apply_rev(t->r);
    t->rev = false;
}

// split first 'cnt' nodes into a, rest into b
void split(Node* t, int cnt, Node*& a, Node*& b){
    if(!t){ a = b = nullptr; return; }
    push(t);
    if(sz(t->l) >= cnt){
        split(t->l, cnt, a, t->l);
        b = t;
        pull(b);
    }else{
        split(t->r, cnt - sz(t->l) - 1, t->r, b);
        a = t;
        pull(a);
    }
}

Node* merge(Node* a, Node* b){
    if(!a || !b) return a ? a : b;
    if(a->pr > b->pr){
        push(a);
        a->r = merge(a->r, b);
        pull(a);
        return a;
    }else{
        push(b);
        b->l = merge(a, b->l);
        pull(b);
        return b;
    }
}

struct ImplicitTreap{
    Node* root = nullptr;
    ImplicitTreap(){ ios::sync_with_stdio(false); cin.tie(nullptr); }

    int size(){ return sz(root); }

    // build from vector in O(n) using stack (monotonic on priority)
    void build(const vector<int>& v){
        root = nullptr;
        vector<Node*> stk;
        for(int x: v){
            Node* cur = new Node(x);
            Node* last = nullptr;
            while(!stk.empty() && stk.back()->pr < cur->pr){
                last = stk.back(); stk.pop_back();
                pull(last);
            }
            cur->l = last;
            if(!stk.empty()) stk.back()->r = cur;
            stk.push_back(cur);
        }
        while(stk.size()>1){ pull(stk.back()); stk.pop_back(); }
        if(!stk.empty()) { pull(stk.back()); root = stk.back(); }
    }

    // insert value x at position pos (0-indexed, insert before pos)
    void insert(int pos, int x){
        Node *a, *b;
        split(root, pos, a, b);
        root = merge(merge(a, new Node(x)), b);
    }

    // erase element at position pos (0-indexed)
    void erase(int pos){
        Node *a, *b, *c;
        split(root, pos, a, b);
        split(b, 1, b, c); // b is the node to delete
        // delete b;
        root = merge(a, c);
    }

    // get value at position pos
    int kth(int pos){
        Node *a, *b, *c;
        split(root, pos, a, b);
        split(b, 1, b, c);
        int ans = b ? b->val : INT_MIN;
        root = merge(merge(a, b), c);
        return ans;
    }

    // set value at position pos
    void set_val(int pos, int x){
        Node *a, *b, *c;
        split(root, pos, a, b);
        split(b, 1, b, c);
        if(b) b->val = x;
        pull(b);
        root = merge(merge(a, b), c);
    }

    // range reverse [l, r] inclusive (0-indexed)
    void range_reverse(int l, int r){
        Node *a, *b, *c;
        split(root, l, a, b);
        split(b, r - l + 1, b, c);
        if(b) apply_rev(b);
        root = merge(merge(a, b), c);
    }

    // range sum [l, r] inclusive
    ll range_sum(int l, int r){
        Node *a, *b, *c;
        split(root, l, a, b);
        split(b, r - l + 1, b, c);
        ll ans = sum(b);
        root = merge(merge(a, b), c);
        return ans;
    }

    // inorder collect
    void collect(Node* t, vector<int>& out){
        if(!t) return; push(t);
        collect(t->l, out);
        out.push_back(t->val);
        collect(t->r, out);
    }
    vector<int> to_vector(){ vector<int> out; collect(root, out); return out; }
};

// Example usage
int main(){
    srand(time(nullptr));
    ImplicitTreap tr;
    vector<int> a = {1,2,3,4,5};
    tr.build(a);

    tr.insert(2, 99); // 1 2 99 3 4 5
    tr.erase(4);      // remove element at index 4 -> 1 2 99 3 5
    tr.set_val(0, 10); // 10 2 99 3 5
    tr.range_reverse(1,3); // 10 3 99 2 5
    cout << "size=" << tr.size() << '\n';
    cout << "sum[1,3]=" << tr.range_sum(1,3) << '\n';
    auto v = tr.to_vector();
    for(int x: v) cout << x << ' '; cout << '\n';
    return 0;
}

