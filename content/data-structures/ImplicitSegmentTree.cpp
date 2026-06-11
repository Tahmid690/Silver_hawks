/**
 * Author: 
 * Date: 
 * License: 
 * Source: 
 * Description: 
 * Time: 
 * Status: 
 */

struct node{
	int sum,prop;
	node *l,*r;
	node(): sum(0),prop(0),l(NULL),r(NULL) { }
};
struct segtree{
	
	void propagate(node *v,int l,int r){
		v->l->prop=v->prop;
		v->r->prop=v->prop;
		int xx=v->prop;
		v->prop=0;
		int mid=(l+r)/2;
		
		v->l->sum=(mid-l+1)*xx;
		v->r->sum=(r-(mid+1)+1)*xx;
	}
	void update(node *v,int l,int r,int a,int b,int u){
		if(b<l || a>r) return;
		if(l>=a && r<=b){
			v -> sum = (r-l+1)*u;
			v -> prop =u;
			return;
		}
		if(v->l==NULL) v->l=new node();
		if(v->r==NULL) v->r=new node();
		if(v->prop!=0) propagate(v,l,r);
		update(v->l,l,(l+r)/2,a,b,u);
		update(v->r,(l+r)/2 +1,r,a,b,u);
		v -> sum= v->l->sum + v->r->sum;
	}
	int query(node *v,int l,int r,int a,int b){
		if(r<a || l>b) return 0;
		if(l>=a && r<=b){
			return v -> sum;
		} 
		if(v->prop!=0) propagate(v,l,r);
		return query(v->l,l,(l+r)/2,a,b)+query(v->r,(l+r)/2 +1,r,a,b);
	}
}sg;

void solve(){
	node *root =new node();
	sg.update(root,1,1000000005,a,b,1);
	sg.query(root,1,1000000000,1,1000000005);
}