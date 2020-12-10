
struct AhoCorasick {
    const static int A = 3;
    struct Vert {
        array<int,A> next = {};
        // custom data
    };
    vector<Vert> trie = {{}};

    int addWord(string& s) {
        int v = 0;
        for(auto c : s) {
            c-='a';
            if(!trie[v].next[c]) {
                trie[v].next[c] = trie.size();
                trie.emplace_back();
            }
            v = trie[v].next[c];
        }
        return v;
    }

    void finalize() {
        queue<array<int,4>> q{{{0,0,0,0}}};
        while(size(q)) {
            auto [v, parent, plink, pch] = q.front(); q.pop();
            int link = parent == 0 ? 0 : trie[plink].next[pch];
            rep(c,A) {
                if(!trie[v].next[c]) trie[v].next[c] = trie[link].next[c];
                else q.push({trie[v].next[c], v, link, c});
            }
            // compute aggregates here
        }
    }
};
