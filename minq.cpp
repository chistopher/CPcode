
struct MinQ {
    using T = pair<int, int>;
    T INF{1e9, 0};
    vector<pair<T,T>> inbox;
    vector<pair<T,T>> outbox;
    auto mn(vector<pair<T,T>>& stack) { return size(stack) ? stack.back().second : INF; }
    auto mn() { return min(mn(inbox), mn(outbox)); }
    auto sz() { return size(inbox) + size(outbox); }
    auto push(T v) { inbox.emplace_back(v, min(v,mn(inbox))); }
    auto top() { if(!size(outbox)) shift(); return outbox.back().first; }
    auto pop() { if(!size(outbox)) shift(); outbox.pop_back(); }
    void shift() {
        while(size(inbox)) {
            outbox.emplace_back(inbox.back().first, min(inbox.back().first, mn(outbox)));
            inbox.pop_back();
        }
    }
};
