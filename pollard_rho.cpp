
ll mult(ll a, ll b, ll m) {
#ifdef __GNUC__
    return static_cast<__int128>(a) * static_cast<__int128>(b) % m;
#else
    return (mult((a+a)%m,b/2,m) + (b%2 ? a : 0)) % m;
#endif
}

ll pow(ll a, ll b, ll m) {
    if(b==0) return 1;
    return mult( pow(mult(a,a,m),b/2,m), b%2?a:1, m);
}

bool isPrime(ll n) {
    static array wits{2,3,5,7,11,13,17,19,23,29,31,37,41};
    if(n<42) return find(all(wits), n) != end(wits);
    ll d=n-1, s=0;
    while(d%2==0) s+=1, d/=2;
    for(auto a : wits) {
        auto x = pow(a,d,n);
        bool comp = x!=1 && x!=n-1;
        for(ll r=0; r<s-1 && comp; ++r) {
            x = mult(x,x,n);
            comp &= (x!=n-1);
        }
        if(comp) return false;
    }
    return true;
}

auto factor(ll n) {
    vector<ll> factors;
    vector toCheck{n};
    while(!empty(toCheck)) {
        auto x = toCheck.back(); toCheck.pop_back();
        if(isPrime(x)) { factors.push_back(x); continue; }
        if(x%2==0) { factors.push_back(2); toCheck.push_back(x/2); continue; }
        ll g = x; // try some pollard rho until g is a proper divisor of x
        for(ll x0=2, c=1; g==x ; c++, x0+=2) {
            auto f = [c,x](ll a) { return (mult(a,a,x) + c) % x; };
            ll a = x0, b = x0;
            for(g=1; g==1; g=gcd(abs(a-b), x))
                a=f(a), b=f(f(b));
        }
        toCheck.push_back(g);
        toCheck.push_back(x/g);
    }
    return factors;
}
