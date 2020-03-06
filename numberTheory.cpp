
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

