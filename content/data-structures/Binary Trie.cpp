#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<int, int>;
using vii = vector<int>;
#define all(v) begin(v), end(v)
#define sz(v) (int)(v).size()
#define fi first
#define se second
#define pb push_back

struct node{
	int to[2],flag,cnt=0;
	node(){
    	memset(to,-1,sizeof to);
    	flag=0;
	}
}t[6500000];

int ptr=1;

void insert(string s) {
	int cur=0;
	for(char c : s) {
    	if(t[cur].to[c-'0']==-1) {
    		t[cur].to[c-'0']=ptr++;
    	}
    	cur=t[cur].to[c-'0'];
    	t[cur].cnt++;
	}
	t[cur].flag = 1;
}

int query(string s) {
	int cur = 0;
	vii ans;
	for(char c : s) {
		ll x=((c-'0') ^ 1);
		if(t[cur].to[x]!=-1 && t[t[cur].to[x]].cnt>0){
			cur = t[cur].to[x];
			ans.pb(x);
		}
		
    	else{
    		x=(c-'0');
    		cur = t[cur].to[x];
			ans.pb(x);
    	}

	}
	ll xx=1,num=0,mn=0;
	reverse(all(ans));
	for(int i=0;i<ans.size();i++){
		num+=(xx*ans[i]);
		xx*=2;
	}
	
	xx=1;
	reverse(all(s));
	for(int i=0;i<s.size();i++){
		mn+=(xx*(s[i]-'0'));
		xx*=2;
	}
	//cout << num << " " << mn << endl;
	return (num ^ mn);
}

void erase(string s){
	int cur = 0;
	for(char c : s) {
    	//if(t[cur].to[c-'0'] == -1) return;
    	//int cc=cur;
    	cur=t[cur].to[c-'0'];
    	//if(t[cc].cnt==0) t[cc].to[c-'0']=-1;
    	t[cur].cnt--;
	}
}

int q,x;
char typ;
int main(){
	cin >> q;
	string vv;
	for(int i=0;i<32;i++) vv.pb('0');
	insert(vv);
	while(q--){
		cin >> typ;
		if(typ=='+'){
			cin >> x;
			string tmp;
			for(int i=0;i<32;i++){
				if(x & (1<<i)) tmp.pb('1');
				else tmp.pb('0');
			}
			reverse(all(tmp));
			insert(tmp);
		}
		else if(typ=='-'){
			cin >> x;
			string tmp;
			for(int i=0;i<32;i++){
				if(x & (1<<i)) tmp.pb('1');
				else tmp.pb('0');
			}
			reverse(all(tmp));
			erase(tmp);
		}
		else{
			cin >> x;
			string tmp;
			for(int i=0;i<32;i++){
				if(x & (1<<i)) tmp.pb('1');
				else tmp.pb('0');
			}
			reverse(all(tmp));
			cout << query(tmp) << endl;
		}
		
	}
}
