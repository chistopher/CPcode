
// iterative version from https://codeforces.com/blog/entry/18051
struct SegmentTree {
    explicit SegmentTree(vector<int>& arr) {
        m_n = arr.size();
        m_tree.resize(2*m_n, 0);
        // construct base values
        for (int i = 0; i < m_n; ++i)
            m_tree[m_n + i] = arr[i];
        //build tree
        for (int i = m_n - 1; i > 0; --i) m_tree[i] = m_tree[i<<1] + m_tree[i<<1|1];
    }

    void modify(int p, int value) {  // set value at position p
        for (m_tree[p += m_n] = value; p > 1; p >>= 1) m_tree[p>>1] = m_tree[p] + m_tree[p^1];
    }

    int query(int l, int r) {  // sum on interval [l, r)
        int res = 0;
        for (l += m_n, r += m_n; l < r; l >>= 1, r >>= 1) {
            if (l&1) res += m_tree[l++];
            if (r&1) res += m_tree[--r];
        }
        return res;
    }

    int m_n;
    vector<int> m_tree;
};

// segment tree adapted from https://www.geeksforgeeks.org/segment-tree-set-1-sum-of-given-range
using T = int;
const T NEUTRAL = 0;
T combine(T a, T) { return a + b; }
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
