
using ll = long long;
vector<ll> factor(ll n) {
    vector<ll> res;
    for(ll d=2; d*d<=n; ++d) {
        if(n%d==0) res.push_back(d);
        while(n%d==0) n/=d;
    }
    if(n>1) res.push_back(n);
    return res;
}


ll totient(ll n) {
    ll ans = n;
    for(auto prime : factor(n)) 
        ans -= ans / prime;
    return ans;
}

// factor all numbers <= N in O(N)
auto sieve(int N) {
    vector<ll> lowest(N+1, 0), primes;
    for (int i=2; i<=N; ++i) {
        if (lowest[i] == 0)
            lowest[i]=i, primes.push_back(i);
        for(auto p : primes) {
            if(p>lowest[i] || i*p>N) break;
            lowest[i * p] = p;
        }
    }
    return pair(lowest, primes);
}
