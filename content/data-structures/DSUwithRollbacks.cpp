/**
 * Author: 
 * Date: 
 * License: 
 * Source: 
 * Description: 
 * Time: 
 * Status: 
 */

class DSUWithRollbacks{
public:
    int par[N],siz[N];
    stack<tuple<int,int,int,int>> history;

    int sets;
    void init(int n){
        for(int i=1;i<=n;i++) par[i]=i,siz[i]=1;
        sets=n;
    }

    int find(int x){
        while(x!=par[x]) x=par[x];
        return x;
    }
    void union_sets(int x,int y){
        int rootX=find(x);
        int rootY=find(y);

        if(rootX==rootY){
            history.push({rootY,par[rootY],siz[rootX],sets});
            return;
        }

        if(siz[rootX]<siz[rootY]) swap(rootX,rootY);
        history.push({rootY,par[rootY],siz[rootX],sets});

        

        sets--;
        par[rootY]=rootX;
        siz[rootX]+=siz[rootY];
    }
    void rollback(){
        if(history.empty()) return;

        auto [child,oldPar,oldSiz,setno]=history.top();
        history.pop();

        sets=setno;
        siz[find(child)]=oldSiz;
        par[child]=oldPar;
        
    }
}dsu;
