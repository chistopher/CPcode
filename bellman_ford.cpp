
struct Edge{
    int to;
    int weight;
};

// work also w/o the inq stuff but is slower then
vector<ll> bellman(vector<vector<Edge>>& adj, int source) {
    auto n = adj.size();
    vector dist(n, numeric_limits<ll>::max() / 2);
    dist[source] = 0;
    queue<int> q;
    vector<char> inq(n,false);
    q.emplace(source);
    inq[source] = true;
    while(!q.empty()){
        auto v = q.front(); q.pop();
        inq[v] = false;
        for(auto [nei, w] : adj[v]){
            if(dist[nei] <= dist[v] + w) continue;
            dist[nei] = dist[v] + w;
            if(inq[nei]) continue;
            q.push(nei);
            inq[nei] = true;
        }
    }
    return dist;
}
