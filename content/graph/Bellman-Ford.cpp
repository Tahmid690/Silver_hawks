/**
 * Author: 
 * Date: 
 * License: 
 * Source: 
 * Description: 
 * Time: 
 * Status: 
 */
vector<pair<int,pii>> e;
int d[N],par[N];
for(int i=1;i<=n;i++) d[i]=inf;
d[v] = 0;
    while(1){
        bool chk=0;
        for (int j=0;j<m;j++){
        	if (d[e[j].ss.ff] < inf){
        	        if (d[e[j].ss.ss]>d[e[j].ss.ff]+e[j].ff){
	                    d[e[j].ss.ss]=d[e[j].ss.ff]+e[j].ff;
                    	    chk=1;
                    	    par[e[j].ss.ss]=e[j].ss.ff;
                	}
                }
        }
        if (!chk) break;
    }