
// assumes pos weights
ll arb(vector<vector<pair<int, int>>> &inc, int root) {
    int n = size(inc);

    DSU dsu2(n);
    DSU dsu3(n);

    queue<int> q;
    rep(v, n)
    if (v != root)
        q.emplace(v);

    vector from(n, 0);
    ll ans = 1;

    while (size(q)) {
        int v = q.front();
        q.pop();

        if (!size(inc[v])) return 0;

        auto[cost, orig] = *min_element(all(inc[v]));
        from[v] = orig;
        ans += cost;
        for (auto&[c, f] : inc[v]) c -= cost;
        if (dsu2.join(v, dsu2.find(orig)))
            continue;

        for (int vb = v;;) {
            int vn = dsu3.find(from[vb]);
            if (vn == dsu3.find(v)) break;
            dsu3.join(vb, vn);
            copy(all(inc[vn]), back_inserter(inc[v]));
            inc[vn].clear();
            vb = vn;
        }
        int crep = dsu3.find(v); // cycle rep
        swap(inc[v], inc[crep]);

        // remove self-loops
        while (size(inc[crep])) {
            auto it = min_element(all(inc[crep]));
            if (!dsu3.same(crep, it->second))
                break;
            inc[crep].erase(it);
        }

        from[crep] = 0;
        q.emplace(crep);
    }

    return ans;
}

