for(int i=0;i<=n;i++) for(int j=0;j<=n;j++) d[i][j]=inf;
	for(int i=0;i<=n;i++) d[i][i]=0;
	for(int i=0;i<m;i++){
		cin >> u >> v >> c;
		d[u][v]=d[v][u]=min(d[u][v],c);
	}
	for(int k=1;k<=n;k++){
    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++){
            if(d[i][k]<inf && d[k][j]<inf)
        	 	d[i][j]=min(d[i][j],d[i][k]+d[k][j]); 
        	}
    	}
	}