int segments[100005],segsiz;
void preprocess(int ara[],int n){
    int cur=-1;
    segsiz=sqrt(n);
    for(int i=0;i<n;i++){
        if(i%segsiz==0) cur++;
        segments[cur]+=ara[i];
    }
}
int query(int ara[],int l,int r){
    int sum=0;
    while(l<r && l%segsiz!=0) sum+=ara[l],l++;
    while(l+segsiz<=r){
        sum+=segments[l/segsiz];
        l+=segsiz;
    }
    while(l<=r) sum+=ara[l],l++;
    return sum;
}
void update(int ara[],int i,int val){
    int segno = i / segsiz; 
    segments[segno] -= ara[i];
    segments[segno] += val;
    ara[i] = val;
}