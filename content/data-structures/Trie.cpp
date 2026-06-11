struct node{
	int to[26],flag,r,b;
	node(){
    	memset(to, -1, sizeof to);
    	flag=0;
	}
}t[100005];

int ptr = 1;

void insert(string s) {
	int cur = 0;
	for(char c : s) {
    	if(t[cur].to[c - 'a'] == -1) {
    		t[cur].to[c - 'a'] = ptr++;
    	}
    	cur = t[cur].to[c - 'a'];
	}
	t[cur].flag = 1;
}

bool query(string s) {
	int cur = 0;
	for(char c : s) {
    	if(t[cur].to[c-'a'] == -1) return 0;
    	cur = t[cur].to[c-'a'];
	}
	return t[cur].flag;
}