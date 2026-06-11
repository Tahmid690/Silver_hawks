int fx[]={1,-1,0,0}; 
int fy[]={0,0,1,-1};
ll d[2005][2005],vis[2005][2005]; 

void bfs(int sx,int sy){
	memset(vis,0,sizeof vis);
	memset(d,0,sizeof d);
	vis[sx][sy]=1;
	queue<pii>q; 
	q.push(pii(sx,sy));
	if(c[sx][sy]!=0) vv=min(vv,c[sx][sy]);
	while(!q.empty())
	{		
		pii top=q.front(); q.pop();
		for(int k=0;k<4;k++){
			int tx=top.ff+fx[k];
			int ty=top.ss+fy[k]; 
			if(tx>=0 and tx<n and ty>=0 and ty<m and c[tx][ty]!=-1 and vis[tx][ty]==0){
				vis[tx][ty]=1;
				d[tx][ty]=d[top.ff][top.ss]+w; 
				if(c[tx][ty]!=0) vv=min(vv,c[tx][ty]+d[tx][ty]);
				q.push(pii(tx,ty));
			}
		}
	}
}