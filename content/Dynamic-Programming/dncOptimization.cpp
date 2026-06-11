/**
 * Author: 
 * Date: 
 * License: 
 * Source: 
 * Description: 1-based dnc optimization
 * Time: 
 * Status: 
 */
vector<ll> dp_prev,dp_cur;
inline ll cost(int l, int r){
}
void compute(int L,int R,int optL,int optR){
    if(L>R) return;
    int mid=(L+R)>>1;
    ll bv=INF; int bj=0;
    int up=min(mid-1,optR);
    for(int j=optL;j<=up;j++){
        ll v=dp_prev[j]+cost(j+1,mid);
        if(v<bv){bv=v;bj=j;}
    }
    dp_cur[mid]=bv;
    compute(L,mid-1,optL,bj);
    compute(mid+1,R,bj,optR);
}
void dnc_solve(){
    dp_prev.assign(n+1,INF);
    dp_cur.assign(n+1,INF);
    dp_prev[1]=cost(1,1);
    for(int i=2;i<=n;i++) dp_prev[i]=cost(1,i);
    for(int k=2;k<=K;k++){
        fill(dp_cur.begin(),dp_cur.end(),INF);
        compute(1,n,1,n-1);
        dp_prev.swap(dp_cur);
    }
}
dnc_solve(); cout << dp_prev[n] << endl;
