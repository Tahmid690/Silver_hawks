void solve(){
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> x[i];
        pre[i]=pre[i-1]+x[i];
        dp[i][i]=0;
        opt[i][i]=i;
    }

    for(int len=2;len<=n;len++){
        for(int l=1;l+len-1<=n;l++){
            int r=l+len-1;
            dp[l][r]=INF;
            for(int k=opt[l][r-1];k<=opt[l+1][r];k++){
                int val=dp[l][k]+dp[k+1][r]+pre[r]-pre[l-1];
                if(dp[l][r]>val){
                    dp[l][r]=val;
                    opt[l][r]=k;
                }
            }
        }
    }

    cout << dp[1][n] << endl;
}