#include<bits/stdc++.h>
using namespace std;

#define INF 1e9+2

struct edge{
	int from,to,wei;
};

int main(){
	int t;
	cin >> t;
	for(int tc=1;tc<=t;tc++){
		int n,m;
		cin >> n >> m;
		vector<vector<int>> g,wei;
		vector<edge> el;
		g.resize(n+1);
		wei.resize(n+1);
		el.resize(m);

		for(int i=0;i<m;i++){
			cin >> el[i].from >> el[i].to >> el[i].wei;
			g[el[i].from].push_back(el[i].to);
			wei[el[i].from].push_back(el[i].wei);
		}
		for(int i=1;i<=n;i++) el.push_back({0,i,0});

		//Bellman-Ford

		vector<int> h(n+1,INF);
		h[0]=0;
		for(int i=0;i<n;i++){
			for(edge x:el){
				if(h[x.from]!=INF && h[x.from]+x.wei<h[x.to]){
					h[x.to]=h[x.from]+x.wei;
				}
			}
		}
		bool flg=0;
		for(edge x:el){
			if(h[x.from]!=INF && h[x.from]+x.wei<h[x.to]){
				flg=1;
				break;
			}
		}
		if(flg){
			cout << "graph " << tc << " no\n\n";
			continue;
		}
		cout << "graph " << tc << " yes\n\n";

		//Reweighting

		for(int i=1;i<=n;i++){
			for(int j=0;j<wei[i].size();j++){
				wei[i][j]+=h[i]-h[g[i][j]];
			}
		}

		//Dijakstra for all

		vector<vector<int>> dist(n+1);
		for(int i=1;i<=n;i++) dist[i].assign(n+1,INF);

		for(int nd=1;nd<=n;nd++){
			dist[nd][nd]=0;
			priority_queue<pair<int,int>> Q;
			Q.push({0,nd});
			while(!Q.empty()){
				int u=Q.top().second;
				int pw=-Q.top().first;
				Q.pop();

				for(int i=0;i<g[u].size();i++){
					int v=g[u][i];
					int ew=wei[u][i];
					if(dist[nd][v]>dist[nd][u]+ew){
						dist[nd][v]=dist[nd][u]+ew;
						Q.push({-dist[nd][v],v});
					}
				}

			}
		}

		//Undo Weighting
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(dist[i][j]<INF) dist[i][j]+=(h[j]-h[i]);
			}
		}

		for(int i=1;i<=n;i++) cout << h[i] << " ";
		cout << h[0];
		cout << "\n\n";

		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(dist[i][j]<INF) cout << dist[i][j];
				else cout << "#";
				if(j!=n) cout << " "; 
			}
			cout << "\n";
		}
		cout << "\n";







	}

}
