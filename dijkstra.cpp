
struct Edge{
    int to;
    int weight;
};

auto dijkstra(vector<vector<Edge>>& adj, int source) {
    auto n = adj.size();
    vector dist(n, numeric_limits<int>::max() / 2);
    priority_queue<pair<int,int>> q; // (-dist, id)
    dist[source] = 0;
    q.emplace(0, source);
    while(!q.empty()){
        auto [d,v] = q.top(); q.pop();
        if(-d>dist[v]) continue;
        for(auto [nei, w] : adj[v]){
            if(dist[nei] <= dist[v] + w) continue;
            dist[nei] = dist[v] + w;
            q.emplace(-dist[nei], nei);
        }
    }
    return dist;
}
