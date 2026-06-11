/**
 * Author: 
 * Date: 
 * License: 
 * Source: 
 * Description: 
 * Time: 
 * Status: 
 */
const int N = 1e6 + 5; // Max possible sum or value
int n, g[N], r[N], cnt[N];
vector<pair<int, int>> nums; // {value, count}

// Solves bounded subset sum: find all possible sums with at most cnt[i] times value i
void solve() {
    cin >> n;

    int total_sum = 0;
    int overall_gcd = 0;
    bool has_zero = false;

    // Count frequencies of g[i], compute total sum and GCD of all r[i]
    for (int i = 1; i <= n; ++i) {
        cin >> g[i] >> r[i];
        cnt[g[i]]++;
        total_sum += g[i];
        overall_gcd = __gcd(overall_gcd, r[i]);
        if (g[i] == 0) has_zero = true;
    }

    // Collect unique {value, count} pairs
    for (int i = 1; i < N; ++i) {
        if (cnt[i]) nums.pb({i, cnt[i]});
    }

    vector<int> dp(N, 0); // dp[i] = 1 means sum 'i' is reachable
    dp[0] = 1;

    // SOS-style bounded knapsack using modular buckets
    for (auto [val, freq] : nums) {
        vector<int> new_dp = dp;

        for (int rem = 0; rem < val; ++rem) {
            int sum = 0, window = 0;

            for (int j = rem; j < N; j += val) {
                if (window > freq) {
                    sum -= dp[j - val * window];
                    window--;
                }
                if (sum > 0) new_dp[j] = 1;
                sum += dp[j];
                window++;
            }
        }
        swap(dp, new_dp);
    }

    // Example output: list all reachable sums
    // for (int i = 0; i <= total_sum; ++i)
    //     if (dp[i]) cout << i << " ";

    // You can now use dp[i] for queries like:
    // - Is sum 'S' achievable?
    // - Count total achievable sums
    // etc.
}
