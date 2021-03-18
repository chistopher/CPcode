
/* PSEUDOCODE OF ACTUAL ALGO
void dfs(int v) {
    for(auto nei : g[v])
        if(twin not used)
            dfs(nei);
    tour.push_back(v);
}
*/


vector<int> euler_tour(Graph& g) {

    int n = size(g);
    int start = 0;
    int odd_cnt = 0;
    rep(i,n) if(size(g[i])%2) odd_cnt++, start = i;
    if(odd_cnt>2 || odd_cnt==1) return {};

    // we use a flat vector of edges to find twins with ^1
    vector<int> nxt(n,-1), tour;
    struct Edge { int to; int nxt; };
    vector<Edge> edges;
    rep(a,n) for(auto b : g[a]) {
        if(a>b) continue;
        edges.push_back({b, nxt[a]});
        edges.push_back({a, nxt[b]});
        nxt[a] = size(edges)-2;
        nxt[b] = size(edges)-1;
    }

    // dfs
    vector st{start};
    while(size(st)) {
        int v = st.back();
        while(nxt[v]!=-1 && edges[nxt[v]].to==-1)
            nxt[v] = edges[nxt[v]].nxt; // skip used edges
        int e_id = nxt[v];
        if(e_id!=-1) {
            nxt[v] = edges[e_id].nxt;
            edges[e_id^1].to = -1;
            st.push_back(edges[e_id].to);
        } else {
            st.pop_back();
            tour.push_back(v);
        }
    }

    return tour;
}

