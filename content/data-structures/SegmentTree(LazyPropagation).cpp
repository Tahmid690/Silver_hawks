/**
 * Author: 
 * Date: 
 * License: 
 * Source: 
 * Description: 
 * Time: 
 * Status: 
 */
struct segtree{
	ll tree[4*N],rep[4*N],prop[4*N];
	void propagate(int node,int l,int r){
		rep[node*2]=rep[node];
		rep[node*2+1]=rep[node];
		prop[node*2]=0;
		prop[node*2+1]=0;
		int xx=rep[node];
		rep[node]=0;
		int mid=(l+r)/2;
		tree[node*2]=(mid-l+1)*xx;
		tree[node*2+1]=(r-(mid+1)+1)*xx;
	}
	void propagate2(int node,int l,int r){
		prop[node*2]+=prop[node];
		prop[node*2+1]+=prop[node];
		int xx=prop[node];
		prop[node]=0;
		int mid=(l+r)/2;	
		tree[node*2]+=(mid-l+1)*xx;
		tree[node*2+1]+=(r-(mid+1)+1)*xx;
	}
	void update(int node,int l,int r,int a,int b,int u){
		if(b<l || a>r) return;
		if(l>=a && r<=b){
			tree[node]=(r-l+1)*u;
			rep[node]=u;
			prop[node]=0;
			return;
		}	
		if(rep[node]!=0) propagate(node,l,r);
		propagate2(node,l,r);
		update(node*2,l,(l+r)/2,a,b,u);
		update(node*2+1,(l+r)/2 +1,r,a,b,u);
		tree[node]=tree[node*2]+tree[node*2+1];
	}
	void update2(int node,int l,int r,int a,int b,int u){
		if(b<l || a>r) return;
		if(l>=a && r<=b){
			tree[node]+=(r-l+1)*u;
			prop[node]+=u;
			return;
		}
		if(rep[node]!=0) propagate(node,l,r);
		propagate2(node,l,r);
		update2(node*2,l,(l+r)/2,a,b,u);
		update2(node*2+1,(l+r)/2 +1,r,a,b,u);
		tree[node]=tree[node*2]+tree[node*2+1];
	}
	int query(int node,int l,int r,int a,int b){
		if(r<a || l>b) return 0;
		if(l>=a && r<=b) return tree[node];
		if(rep[node]!=0) propagate(node,l,r);
		propagate2(node,l,r);
		return query(node*2,l,(l+r)/2,a,b)+query(node*2+1,(l+r)/2 +1,r,a,b);
	}
}sg;
// Range Maximize
void propagate(int node,int l,int r){
    prop[node*2]=max(prop[node*2],prop[node]);
    prop[node*2+1]=max(prop[node*2+1],prop[node]);
    int u=prop[node];
    prop[node]=0;
    int mid=(l+r)/2;    
    trmx[node*2]=max(trmx[node*2],u);
    trmn[node*2]=max(trmn[node*2],u);
    trmx[node*2+1]=max(trmx[node*2+1],u);
    trmn[node*2+1]=max(trmn[node*2+1],u);
}
