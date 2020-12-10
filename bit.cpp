
struct BIT {
    int n;
    vector<int> bit;  // one based
    BIT(int _n) : n(_n), bit(_n+1) {}
    int sum(int idx) { // sum [0,idx]
        int ret = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            ret += bit[idx];
        return ret;
    }
    void add(int idx, int delta) {
        for (++idx; idx <= n; idx += idx & -idx)
            bit[idx] += delta;
    }
    int serch(int bound) { // returns rightmost index i s.t. sum till i <= bound
        int pos=0, sum = 0;
        for(int i=1<<30; i>=1; i>>=1)
            if(pos+i<=n && sum+bit[pos+i]<=bound)
                pos+=i, sum+=bit[pos];
        return pos-1;
    }
};
