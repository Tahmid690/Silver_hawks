/**
 * Author: Victor Lecomte, chilli, Brock
 * Date: 2025-09-22
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf, folklore
 * Description: Computes the Minkowski sum of two convex polygons $A$ and $B$ in CCW order.
 * Returns the convex polygon $A \oplus B$ in CCW order.
 * Runs in $O(n+m)$ where $n,m$ are the number of vertices.
 * Assumes both polygons are given without duplicate last point, and are convex CCW.
 * Status: Tested
 */
// Assumes polygons A, B are convex and given in CCW order without duplicate last point.
// Returns convex Minkowski sum in CCW order.
template<class T>
vector<Point<T>> minkowski(vector<Point<T>> A, vector<Point<T>> B) {
	auto shiftLowest = [&](vector<Point<T>>& P) {
		int n = sz(P), pos = 0;
		rep(i,1,n) if (make_pair(P[i].y, P[i].x) < make_pair(P[pos].y, P[pos].x)) pos = i;
		rotate(P.begin(), P.begin()+pos, P.end());
		P.push_back(P[0]); // wrap around for edges
	};

	shiftLowest(A);
	shiftLowest(B);

	vector<Point<T>> res;
	int i = 0, j = 0;
	while (i < sz(A)-1 || j < sz(B)-1) {
		res.push_back(A[i] + B[j]);
		auto cross = (A[i+1]-A[i]).cross(B[j+1]-B[j]);
		if (j == sz(B)-1 || (i < sz(A)-1 && cross >= 0)) i++;
		else j++;
	}
	return res;
}