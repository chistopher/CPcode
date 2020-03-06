
int INF = 1e9;
// return bfs distance from source
vector<int> bfs(int s, vector<vector<int>>& g) {
    vector dist(size(g),INF);
    queue<int> {{s}};
    dist[s] = 0;
    while(size(q)) {
        auto cur= q.front(); q.pop();
        for(auto nei : g[cur]) {
            if (dist[nei] != INF) continue;
            dist[nei] = dist[cur] + 1;
            q.push(nei);
        }
    }
    return dist;
}
