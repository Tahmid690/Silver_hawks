/**
 * Author: 
 * Date: 
 * License: 
 * Source: 
 * Description: 
 * Time: 
 * Status: 
 */
struct mergesortree{
	vll tree[4*N];
	vll merge(vll x,vll y){
    	int i=0,j=0,k;
	    vll temp;
	    while(temp.size()<(x.size()+y.size())){
			if(i==x.size()) temp.push_back(y[j++]);
			else if(j==y.size()) temp.push_back(x[i++]);
			else if(x[i]<y[j]) temp.push_back(x[i++]);
			else temp.push_back(y[j++]);
		}
    	return temp;
	}

	void init(int node,int l,int r){
    	if(l==r){
        	tree[node].push_back(a[l]);
        	return;
    	}
    	init(2*node,l,(l+r)/2); 
    	init(2*node+1,(l+r)/2+1,r);
    	tree[node]=merge(tree[2*node],tree[2*node+1]); 
	}
	int query(int node,int l,int r,int x,int y,int k){
    	if(r<x || l>y) return 0; 
    	if(x<=l && r<=y) return upper_bound(all(tree[node]),k)-tree[node].begin();
    	return query(2*node,l,(l+r)/2,x,y,k)+query(2*node+1,(l+r)/2+1,r,x,y,k);
	}
}sg;
