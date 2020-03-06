
vector<int> z_function(string& s) {
    int l = 0, r = 0;
    vector z(size(s), 0);
    for(int i = 1; i < size(s); ++i) {
        int zi = 0;
        if(i <= r)
            zi = min(z[i-l], r - i + 1);
        while (zi + i < size(s) && s[zi] == s[zi + i])
            zi++;
        z[i] = zi;
        if (r < i + zi - 1)
            l = i, r = i + zi - 1;
    }
    return z;
}

vector<int> prefix_function(string& s) {
    vector p(size(s), 0);
    for(int i = 1; i < size(s); ++i) {
        auto k = p[i - 1];
        while(k > 0 && s[k] != s[i])
            k = p[k - 1];
        if(s[k] == s[i])
            p[i] = k + 1;
    }
    return p;
}
