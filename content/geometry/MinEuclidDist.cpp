/**
 * Author: 
 * Date: 
 * License: 
 * Source: 
 * Description: 
 * Time: 
 * Status: 
 */
 vector<pair<int, int>> poi;

int dis(int i, int j) {
    return (poi[i].ff - poi[j].ff) * (poi[i].ff - poi[j].ff) +
           (poi[i].ss - poi[j].ss) * (poi[i].ss - poi[j].ss);
}

int win(int l, int r) {
    if (r - l + 1 < 4) {
        int mn = dis(l, l + 1);
        for (int i = l; i <= r; i++) {
            for (int j = i + 1; j <= r; j++) {
                mn = min(mn, dis(i, j));
            }
        }
        return mn;
    }

    int mid = (l + r) / 2;
    int ret = min(win(l, mid), win(mid + 1, r));
    int x = sqrt((double)ret) + 2;

    vector<pair<int, int>> ptr;
    for (int i = l; i <= r; i++) {
        if (abs(poi[i].ff - poi[mid].ff) <= x)
            ptr.push_back({poi[i].ss, i});
    }

    sort(all(ptr));

    for (int i = 0; i < ptr.size(); i++) {
        for (int j = i + 1; j < ptr.size() && ptr[j].ff - ptr[i].ff < x; j++) {
            ret = min(ret, dis(ptr[i].second, ptr[j].second));
        }
    }

    return ret;
}

void solve() {
    cin >> n;
    poi.resize(n);
    for (int i = 0; i < n; i++)
        cin >> poi[i].ff >> poi[i].ss;

    sort(all(poi));
    cout << win(0, n - 1) << endl;
}
