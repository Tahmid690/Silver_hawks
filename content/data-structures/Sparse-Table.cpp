/**
 * Author: 
 * Date: 
 * License: 
 * Source: 
 * Description: 
 * Time: 
 * Status: 
 */
#define N 200005
int sparse[N][25],a[N];
void build_sparse(int n){
    for(int i=1;i<=n;i++) sparse[i][0]=a[i];
    for(int j=1;j<25;j++){
        for(int i=1;i+(1<<j)-1<=n;i++){
            sparse[i][j]=sparse[i][j-1]+sparse[i+(1<<(j-1))][j-1];
        }
    }
}
int query_sum(int l,int r){
    long long sum=0;
    for(int j=25;j>=0;j--){
        if((1<<j)<=(r-l+1)){
            sum+=sparse[l][j];
            l+=(1<<j);
        }
    }
    return sum;
}
int query(int l,int r){
    int j=31 - __builtin_clz(r-l+1);
    int mini=min(sparse[l][j],sparse[r-(1<<j)+1][j]);
    return mini;
}
