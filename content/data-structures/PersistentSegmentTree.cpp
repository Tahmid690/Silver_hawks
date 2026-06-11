/**
 * Author: 
 * Date: 
 * License: 
 * Source: 
 * Description: 
 * Time: 
 * Status: 
 */
const int N = 200005;

int n,q,a[N];

struct perseg{
	struct node{
		int l,r,val;
		node(){
			l=r=val=0;
		}
	}t[40*N];

	int id=0;
	int build(int b,int e){
		int cur=++id;
		if(b==e){
			t[cur].val=0;
			return cur;	
		}
		int mid=(b+e)>>1;
		t[cur].l=build(b,mid);
		t[cur].r=build(mid+1,e);
		t[cur].val=t[t[cur].l].val+t[t[cur].r].val;
		return cur; 
	}
	int upd(int pre,int b,int e,int i,int v){
		int cur=++id;
		t[cur]=t[pre];
		if(b==e){
			t[cur].val+=v;
			return cur;
		}
		int mid=(b+e)>>1;
		if(i<=mid){
			t[cur].l=upd(t[pre].l,b,mid,i,v);
		}
		else{
			t[cur].r=upd(t[pre].r,mid+1,e,i,v);
		}
		t[cur].val=t[t[cur].l].val+t[t[cur].r].val;
		return cur;
	}
	int qry(int cur,int b,int e,int p,int q){
		if(b>q || e<p) return 0;
		if(b>=p && e<=q) return t[cur].val;
		int mid=(b+e)>>1;
		return qry(t[cur].l,b,mid,p,q)+qry(t[cur].r,mid+1,e,p,q);
	}
	int findkth(int lef,int rig,int b,int e,int k){
		if(b==e) return b;
		int mid=(b+e)>>1;
		int cnt=t[t[rig].l].val-t[t[lef].l].val;
		if(cnt>=k) return findkth(t[lef].l,t[rig].l,b,mid,k);
		else return findkth(t[lef].r,t[rig].r,mid+1,e,k-cnt);
	}
}sg;

vector<int> ver;

void solve(){
	cin >> n >> q;
	for(int i=1;i<=n;i++) cin >> a[i];

	int root=sg.build(1,n);
	ver.push_back(root);

	while(q--){
		int t,k;
		cin >> t >> k;
		if(t==1){
			int a,x;
			cin >> a >> x;
			ver[k-1]=sg.upd(ver[k-1],1,n,a,x);
		}
		else if(t==2){
			int a,b;
			cin >> a >> b;
			cout << sg.qry(ver[k-1],1,n,a,b) << endl;
		}
		else{
			ver.push_back(ver[k-1]);
		}
	} 
}

// CSES - Range Queries and Copies
