/**
 * Author: 
 * Date: 
 * License: 
 * Source: 
 * Description: 
 * Time: 
 * Status: 
 */
    vector<int> freq(SZ, 0);
    for(int x : a) freq[x]++;
    // g[mask] = sum of freq[submask] for submask (subset of) mask
    vector<int> g = freq;
    for(int i = 0; i < M; i++){
        for(int mask = 0; mask < SZ; mask++){
            if(mask & (1<<i))
                g[mask] += g[mask ^ (1<<i)];
        }
    }
    //submask iteration
    for (int m=0; m<(1<<n); ++m) for (int s=m; s; s=(s-1)&m)