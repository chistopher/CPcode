
// iterative version from https://codeforces.com/blog/entry/18051
struct SegmentTree {
    int n;
    vector<int> tree;
    explicit SegmentTree(int n_) : n(n_), tree(2*n) { }
    void add(int p, int value) {  // set value at position p
        for (tree[p += n] += value; p > 1; p >>= 1) tree[p>>1] = tree[p] + tree[p^1];
    }
    int query(int l, int r) {  // sum on interval [l, r)
        int res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) res += tree[l++];
            if (r&1) res += tree[--r];
        }
        return res;
    }
};

// segment tree adapted from https://www.geeksforgeeks.org/segment-tree-set-1-sum-of-given-range
using T = int;
const T NEUTRAL = 0;
T combine(T a, T b) { return a + b; }
T init(int a) { return T(a); }
// tree.resize(4*n, 0);
// construct(0,0,n,arr);
struct SegmentTree {
    vector<T> tree; // sum of interval for all nodes in segment tree
    T construct(int idx, int l, int r, vector<int>& arr) {
        if(r-l==1) return tree[idx] = init(arr[l]); // leaf
        return tree[idx] = combine(construct(2*idx+1,l,(l+r)/2,arr), construct(2*idx+2,(l+r)/2,r,arr));
    }
    T update(int idx, int l, int r, int index, int value) {
        if (index < l || r <= index) return tree[idx]; // index outside node segment
        if (r-l==1) return tree[idx] = init(value); // leaf
        return tree[idx] = combine(update(2*idx+1,l,(l+r)/2,index,value), update(2*idx+2,(l+r)/2,r,index,value));
    }
    T query(int idx, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) return NEUTRAL; // node outside of range
        if (ql <= l && r <= qr) return tree[idx]; // node fully in range
        return combine(query(2*idx+1,l,(l+r)/2,ql,qr), query(2*idx+2,(l+r)/2,r,ql,qr));
    }
};


struct SegmentTree2D {
    int n,m; // x_dim, y_dim
    vector<vector<int>> trees;
    SegmentTree2D(const vector<vector<int>>& mat) {
        n = mat.size(); m = mat[0].size();
        trees = vector(4*n, vector(4*m, 0));
        construct(0,0,n,mat);
    }
    void construct(int vo, int lo, int ro, const vector<vector<int>>& mat) {
        if(ro-lo==1) { // leaf
            inner_construct(0,0,m,vo,mat[lo]);
        } else { // combine along outer axis
            construct(2*vo+1,lo,(lo+ro)/2,mat);
            construct(2*vo+2,(lo+ro)/2,ro,mat);
            rep(vi,4*m) trees[vo][vi] = combine(trees[2*vo+1][vi], trees[2*vo+2][vi]);
        }
    }
    int inner_construct(int vi, int li, int ri, int vo, const vector<int>& row) {
        if(ri-li==1) return trees[vo][vi] = row[li]; // leaf
        return trees[vo][vi] = combine(
                inner_construct(2*vi+1,li,(li+ri)/2,vo,row),
                inner_construct(2*vi+2,(li+ri)/2,ri,vo,row));
    }

    void update(int vo, int lo, int ro, pair<int,int> index, int value) {
        if(index.first<lo || ro<=index.first) return; // not for me
        if(ro-lo>1) { // no leaf
            update(2*vo+1,lo,(lo+ro)/2,index,value);
            update(2*vo+2,(lo+ro)/2,ro,index,value);
        }
        inner_update(vo,lo,ro,0,0,m,index.second,value); // leaf
    }
    int inner_update(int vo, int lo, int ro, int vi, int li, int ri, int index, int value) {
        if (index<li || ri<=index) return NEUTRAL; // index outside node segment
        if(ri-li==1) { // inner leaf
            if(ro-lo==1) // outer leaf -> we got a single cell
                return trees[vo][vi] = value;
            else // outer not leaf -> combine at outer level
                return trees[vo][vi] = combine(trees[2*vo+1][vi], trees[2*vo+2][vi]);
        } else { // inner no leaf -> combine at inner level
            return trees[vo][vi] = combine(
                    inner_update(vo,lo,ro,2*vi+1,li,(li+ri)/2,index,value),
                    inner_update(vo,lo,ro,2*vi+2,(li+ri)/2,ri,index,value));
        }
    }

    int query(int vo, int lo, int ro, int qlo, int qro, int qli, int qri) {
        if (qro <= lo || ro <= qlo) return NEUTRAL; // node outside of range NEUTRAL ELEMENT HERE!!!
        if (qlo <= lo && ro <= qro) return inner_query(vo,0,0,m,qli,qri); // node fully in range
        return combine(
                query(2*vo+1,lo,(lo+ro)/2,qlo,qro,qli,qri),
                query(2*vo+2,(lo+ro)/2,ro,qlo,qro,qli,qri));
    }
    int inner_query(int vo, int vi, int li, int ri, int qli, int qri) {
        if (qri <= li || ri <= qli) return NEUTRAL; // node outside of range
        if (qli <= li && ri <= qri) return trees[vo][vi]; // node fully in range
        return combine(
                inner_query(vo,2*vi+1,li,(li+ri)/2,qli,qri),
                inner_query(vo,2*vi+2,(li+ri)/2,ri,qli,qri));
    }
};


// lazy propagation
struct Seg {
    using T = int; // data type
    using L = int; // lazy type
    const T NEUTRAL = 0;
    auto combine(T a, T b) { return a+b; }

    vector<T> seg; // sum of interval for all nodes in segment tree
    vector<L> lazy; // exclusive lazy
    int m_n;
    Seg(int n) : seg(4*n), lazy(4*n), m_n(n) {};
    T apply(int idx, int l, int r, L lazy) {
        lazy[idx] += lazy;
        return seg[idx] += (r-l)*lazy;
    }
    void push(int idx, int l, int r) {
        int m = (r+l)/2;
        if(m-l) apply(2*idx+1, l, m, lazy[idx]);
        if(r-m) apply(2*idx+2, m, r, lazy[idx]);
        lazy[idx] = 0;
    }
    T update(int idx, int l, int r, int index, T value) {
        if (index < l || r <= index) return seg[idx]; // index outside node segment
        if (r-l==1) return seg[idx] = value; // leaf
        push(idx,l,r);
        return seg[idx] = combine(update(2*idx+1,l,(l+r)/2,index,value), update(2*idx+2,(l+r)/2,r,index,value));
    }
    T update(int index, T value) { return update(0,0,m_n,index,value); }
    T query(int idx, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) return NEUTRAL; // node outside of range
        if (ql <= l && r <= qr) return seg[idx]; // node fully in range
        push(idx,l,r);
        return combine(query(2*idx+1,l,(l+r)/2,ql,qr), query(2*idx+2,(l+r)/2,r,ql,qr));
    }
    T query(int ql, int qr) { return query(0,0,m_n,ql,qr); }
    T range_update(int idx, int l, int r, int ql, int qr, L lazy) {
        if (qr <= l || r <= ql) return seg[idx];
        if (ql <= l && r <= qr) return apply(idx,l,r,lazy);
        push(idx,l,r);
        return seg[idx] = combine(range_update(2*idx+1,l,(l+r)/2,ql,qr,lazy), range_update(2*idx+2,(l+r)/2,r,ql,qr,lazy));
    }
    T range_update(int ql, int qr, L lazy) { return range_update(0,0,m_n,ql,qr,lazy); }
};
