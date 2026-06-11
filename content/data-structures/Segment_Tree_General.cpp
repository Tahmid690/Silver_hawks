struct segtree{
	int tree[4*N],a[N];
	void init(int node,int l,int r){
		if(l==r){ tree[node]=a[l];return;}
		init(node*2,l,(l+r)/2);
		init(node*2+1,(l+r)/2 +1,r);
		tree[node]=tree[node*2]+tree[node*2+1];
	}
	void update(int node,int l,int r,int p,int x){
		if(p<l || p>r) return;
		if(l==r){ tree[node]=x; return;}
		update(node*2,l,(l+r)/2,p,x);
		update(node*2+1,(l+r)/2 +1,r,p,x);
		tree[node]=tree[node*2]+tree[node*2+1];
	}
	int query(int node,int l,int r,int a,int b){
		if(r<a || l>b) return 0;
		if(l>=a && r<=b) return tree[node];
		return query(node*2,l,(l+r)/2,a,b)+query(node*2+1,(l+r)/2 +1,r,a,b);
	}
};