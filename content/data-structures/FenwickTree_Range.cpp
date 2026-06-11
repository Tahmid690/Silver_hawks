/**
 * Author: 
 * Date: 
 * License: 
 * Source: 
 * Description: 
 * Time: 
 * Status: 
 */
//1D Point update, Range query
int lowbit(int idx){
	return (idx & (-idx));
}
int A[N], B[N], n;
void upd(int x, int v) {
  for(int i = x ; i <= n ; i += lowbit(i)) B[i] += v;
}
int sum(int x) {
  int ans = 0;
  for(int i = x ; i > 0 ; i -= lowbit(i)) ans += B[i];
  return ans;
}
int query(int l, int r) {
  return sum(r) - sum(l - 1);
}
void init() {
  fill(B, B + n + 1, 0);
  for(int i = 1 ; i <= n ; ++i) upd(i, A[i]);
}

//1D Range update, Point query

int A[N], B[N], n;
void upd(int x, int v) {
  for(int i = x ; i <= n ; i += lowbit(i)) B[i] += v;
}
int sum(int x) {
  int ans = 0;
  for(int i = x ; i > 0 ; i -= lowbit(i)) ans += B[i];
  return ans;
}
void update(int l, int r, int v) {
  upd(r + 1, -v); upd(l, v);
}
void init() {
  fill(B, B + n + 1, 0); A[0] = 0;
  for(int i = 1 ; i <= n ; ++i) upd(i, A[i] - A[i - 1]);
}

//1D Range update, Range query

int A[N], B1[N], B2[N], n;
void upd(int* B, int x, int v) {
  for(int i = x ; i <= n ; i += lowbit(i)) B[i] += v;
}
int sum(int* B, int x) {
  int ans = 0;
  for(int i = x ; i > 0 ; i -= lowbit(i)) ans += B[i];
  return ans;
}
void update(int l, int r, int v) {
  upd(B1, r + 1, -v); upd(B1, l, v);
  upd(B2, r + 1, -(r + 1) * v); upd(B2, l, l * v);
}
int query(int l, int r) {
  return ((r + 1) * sum(B1, r) - sum(B2, r)) - (l * sum(B1, l - 1) - sum(B2, l - 1));
}
void init() {
  A[0] = 0;
  fill(B1, B1 + n + 1, 0);
  fill(B2, B2 + n + 1, 0);
  for(int i = 1 ; i <= n ; ++i) upd(i, A[i] - A[i - 1]);
}

//2D Point update, Range query

int A[N][N], B[N][N], n, m;
void upd(int x, int y, int v) {
  for(int i = x ; i <= n ; i += lowbit(i)) {
    for(int j = y ; j <= m ; j += lowbit(j)) {
      B[i][j] += v;
    }
  }
}
int sum(int x, int y) {
  int ans = 0;
  for(int i = x ; i > 0 ; i -= lowbit(i)) {
    for(int j = y ; j > 0 ; j -= lowbit(j)) {
      ans += B[i][j];
    }
  }
  return ans;
}
int query(int x1, int y1, int x2, int y2) {
  return sum(x2, y2) - sum(x1 - 1, y2) - sum(x2, y1 - 1) + sum(x1 - 1, y1 - 1);
}
void init() {
  memset(B, 0, sizeof(B));
  for(int i = 1 ; i <= n ; ++i) {
    for(int j = 1 ; j <= m ; ++j) {
      upd(i, j, A[i][j]);
    }
  }
}

//2D Range update, Point query

int A[N][N], B[N][N], n, m;
void upd(int x, int y, int v) {
  for(int i = x ; i <= n ; i += lowbit(i)) {
    for(int j = y ; j <= m ; j += lowbit(j)) {
      B[i][j] += v;
    }
  }
}
int sum(int x, int y) {
  int ans = 0;
  for(int i = x ; i > 0 ; i -= lowbit(i)) {
    for(int j = y ; j > 0 ; j -= lowbit(j)) {
      ans += B[i][j];
    }
  }
  return ans;
}
int update(int x1, int y1, int x2, int y2, int v) {
  upd(x2 + 1, y2 + 1, v);
  upd(x1, y1, v);
  upd(x1, y2 + 1, -v);
  upd(x2, y1 + 1, -v);
}
void init() {
  memset(B, 0, sizeof(B));
  for(int i = 1 ; i <= n ; ++i) {
    for(int j = 1 ; j <= m ; ++j) {
      upd(i, j, A[i][j]);
    }
  }
}


//2D Range update, Range query
int n, m, A[N][N], B[N][N][4];
void upd(int x, int y, int v) {
  for(int i = x ; i <= n ; i += lowbit(i)) {
    for(int j = y ; j <= m ; j += lowbit(j)) {
      B[i][j][0] += v;
      B[i][j][1] += x * v;
      B[i][j][2] += y * v;
      B[i][j][3] += x * y * v;
    }
  }
}
int qry(int x, int y) {
  int ans = 0;
  for(int i = x ; i > 0 ; i -= lowbit(i)) {
    for(int j = y ; j > 0 ; j -= lowbit(j)) {
      ans += (x + 1) * (y + 1) * B[i][j][0] - (y + 1) * B[i][j][1] - (x + 1) * B[i][j][2] + B[i][j][3];
    }
  }
  return ans;
}
void update(int x1, int y1, int x2, int y2, int v) {
  upd(x1, y1, v);
  upd(x1, y2 + 1, -v);
  upd(x2 + 1, y1, -v);
  upd(x2 + 1, y2 + 1, v);
}
int query(int x1, int y1, int x2, int y2) {
  return qry(x2, y2) - qry(x1 - 1, y2) - qry(x2, y1 - 1) + qry(x1 - 1, y1 - 1);
}
void init() {
  for(int i = 1 ; i <= n ; ++i) {
    for(int j = 1 ; j <= m ; ++j) {
      upd(i, j, A[i][j]);
    }
  }
}



