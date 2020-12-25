
auto sorted_cyclic_shifts(const string& s) {
    int n = size(s);
    int log_n = 1;
    while((1<<log_n)<n) ++log_n;

    vector c(log_n+1, vector(n,0));
    vector p(n,0);
    iota(all(p),0);
    sort(all(p), [&](int i, int j){ return s[i]<s[j]; });
    for(int i=1; i<n; ++i)
        c[0][p[i]] = s[p[i]]==s[p[i-1]] ? c[0][p[i-1]] : i;

    rep(k,log_n) {
        vector<int> pn(n), cnt(n);
        rep(i, n) {
            pn[i] = p[i] - (1 << k);
            if (pn[i] < 0) pn[i] += n;
        }
        // csort
        rep(i,n) cnt[c[k][i]]++;
        rep(i,n) if(i) cnt[i] += cnt[i-1];
        for(int i=n-1;i>=0;--i)
            p[--cnt[c[k][pn[i]]]] = pn[i];

        auto get_pair = [&](int i) { return pair(c[k][p[i]], c[k][(p[i] + (1<<k)) % n]); };
        for(int i=1; i<n; ++i)
            c[k+1][p[i]] = get_pair(i)==get_pair(i-1) ? c[k+1][p[i-1]] : i;
    }

    return p;
}
