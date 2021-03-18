
vector<int> SCC(const Graph& adj) {
    int n = static_cast<int>(size(adj));
    vector<int> st, discover(n), low(n);
    vector inS(n,false);

    int numComps = 0;
    vector comp(n,-1);

    int time = 0;
    auto dfs = [&](int u, auto&& recur) -> void {
        low[u] = discover[u] = ++time;
        auto stack_size = size(st);
        st.push_back(u);
        inS[u] = true;
        for(int v : adj[u]) {
            if(discover[v]==0) recur(v,recur);
            if(inS[v]) low[u] = min(low[u], low[v]);
        }

        if(low[u]==discover[u]) {
            while(size(st)>stack_size) {
                int v = st.back(); st.pop_back();
                inS[v] = false;
                comp[v] = numComps;
            }
            numComps++;
        }
    };

    rep(i,n) if(discover[i]==0) dfs(i,dfs);

    return comp;
}

