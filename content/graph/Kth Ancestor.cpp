struct kthanc{
	int anc[N][25];
	void init(int par[],int n){
		memset(anc,-1,sizeof anc);
		for(int i=1;i<=n;i++) anc[i][0]=par[i];
		for(int j=1;(1<<j)<n;j++){
			for(int i=1;i<=n;i++){
				if(anc[i][j-1]!=-1) anc[i][j]=anc[anc[i][j-1]][j-1];
			}
		}
	}
	int findanc(int node,int kn){
		for(int i=0;(1<<i)<=n;i++){
			if(kn & (1<<i)){
				node=anc[node][i];
				if(node==-1) break;
			}
		}
		return node;
	}
};