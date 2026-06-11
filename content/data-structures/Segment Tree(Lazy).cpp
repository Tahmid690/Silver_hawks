struct segtree{
	ll tree[4*N],prop[4*N];
	
	void update(int node,int l,int r,int a,int b,int u){
		if(b<l || a>r) return;
		if(l>=a && r<=b){
			tree[node]+=(r-l+1)*u;
			prop[node]+=u;
			return;
		}
		update(node*2,l,(l+r)/2,a,b,u);
		update(node*2+1,(l+r)/2 +1,r,a,b,u);
	}
	int query(int node,int l,int r,int p){
		if(r<p || l>p) return 0;
		if(l==p && r==p) return prop[node];
		if(p<=((l+r)/2)) return prop[node]+query(node*2,l,(l+r)/2,p);
		else return prop[node]+query(node*2+1,(l+r)/2 +1,r,p);
	}
}sg;