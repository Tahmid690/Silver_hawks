/**
 * Author: 
 * Date: 
 * License: 
 * Source: 
 * Description: 
 * Time: 
 * Status: 
 */
 using Matrix = vector<vector<bool>>;

vector<bool> gaussianEliminationMod2(Matrix& A, int n, int m) {
    vector<bool> solution(n, false);
    int row = 0;

    for (int col = 0; col < n && row < m; ++col) {
        int pivot = row;
        while (pivot < m && !A[pivot][col]) {
            ++pivot;
        }

        if (pivot == m) continue;

        swap(A[row], A[pivot]);

        for (int i = 0; i < m; ++i) {
            if (i != row && A[i][col]) {
                for (int j = col; j <= n; ++j) {
                    A[i][j] ^= A[row][j]; // XOR for GF(2)
                }
            }
        }
        ++row;
    }

    for (int i = row; i < m; ++i) {
        if (A[i][n]) return {}; // No solution
    }

    for (int i = 0; i < n; ++i) {
        solution[i] = A[i][n];
    }

    return solution;
}
