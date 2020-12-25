
struct SuffixAutomaton {
    struct State {
        int link = -1, len;
        int cnt=0, first=0; // extra data
        array<int, 26> next;
        State(int l) : len(l) {
            next.fill(-1);
        }
    };
    vector<State> st{State(0)};
    int last = 0;
    void extend(char c) {
        int cur = size(st);
        st.emplace_back(st[last].len + 1);
        st[cur].cnt = 1;
        st[cur].first = st[cur].len-1;
        int p = last;
        last = cur;
        while (p != -1 && st[p].next[c] == -1) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if(p==-1) {
            st[cur].link = 0;
            return;
        }
        int q = st[p].next[c];
        if (st[q].len == st[p].len + 1) {
            st[cur].link = q;
            return;
        }
        int clone = size(st);
        st.emplace_back(st[q]);
        st[clone].cnt = 0;
        st[clone].first = st[q].first;
        st[clone].len = st[p].len + 1;
        while (p >= 0 && st[p].next[c] == q) {
            st[p].next[c] = clone;
            p = st[p].link;
        }
        st[q].link = st[cur].link = clone;
    }

    void finalizeCounts() {
        // csort
        vector byLen(size(st), 0); // result permutation
        vector lc(st[last].len+1, 0); // length counts
        rep(i,size(st)) lc[st[i].len]++;
        rep(i,size(lc)) if(i) lc[i] += lc[i-1];
        rep(i,size(st)) byLen[--lc[st[i].len]] = i;

        reverse(all(byLen));
        for(auto i : byLen) if(i) st[st[i].link].cnt += st[i].cnt;
    }

    auto interval(int i) { return pair( i==0 ? 0 : st[st[i].link].len+1, st[i].len); }
};
