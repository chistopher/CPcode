
auto ilog = [](auto i) { return 31 - __builtin_clz(i); };

// assumes your data is in arr of size n
vector rmq(ilog(n)+1, vector(n, arr[0])); // rmq[k][i] stores min of interval [i, i+2^k)
rmq[0] = arr; // init bottom level
// [i, i+2^k) splits into two halves [i, i+2^{k-1}) and [i+2^{k-1}, i+2^k)
for (int k = 1; k <= ilog(n); k++)
    for (int i = 0; i + (1 << k) <= n; i++)
        rmq[k][i] = min(rmq[k-1][i], rmq[k-1][i + (1 << (k-1))]);
auto query = [&rmq, &ilog](int l, int r) { // exclusive query
    auto log = ilog(r-l);
    return min(rmq[log][l], rmq[log][r - (1 << log)]);
};


// RMQ query object generator :)
auto createRMQ = [](int n, auto init, auto combine) { // returns an exclusive query lambda
    vector rmq(ilog(n)+1, vector(n, init(0)));
    for (int i = 1; i < n; ++i) rmq[0][i] = init(i); // init bottom level
    for (int k = 1; k <= ilog(n); k++)
        for (int i = 0; i + (1 << k) <= n; i++)
            rmq[k][i] = combine(rmq[k-1][i], rmq[k-1][i + (1 << (k-1))]);
    return [rmq=move(rmq), combine](int l, int r) mutable { // mutable s.t. combine can take non-const args
        auto log = ilog(r-l);
        return combine(rmq[log][l], rmq[log][r - (1 << log)]);
    };
};
