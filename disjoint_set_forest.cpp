
struct DSF {
    vector<int> parent;
    DSF(int n) : parent(n) {
        iota(begin(parent),end(parent),0);
    }
    int find(int v) {
        if(parent[v] == v) return v;
        return parent[v] = find(parent[v]);
    }
    void join(int u, int v) {
        parent[find(u)] = find(v);
    }
};
