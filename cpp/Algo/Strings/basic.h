vector<int> zFunction(string s) {
    int n = s.length();
    vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        int &cur = z[i];
        if (i <= r) {
            z[i] = min(r-i+1, z[i-l]);
        }
        while (i+z[i] < n && s[cur] == s[i+cur]) {
            cur++;
        }
        if (i+z[i]-1 > r) {
            l = i,  r = i+z[i]-1;
        }
    }
    return z;
}
