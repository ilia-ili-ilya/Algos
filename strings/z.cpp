vector<int> z(string s) {
    int n = s.size();
    int l = -1, r = -1;
    vector<int> ans(n);
    ans[0] = n;
    for (int i = 1; i < n; ++i) {
        if (i > r) {
            ans[i] = 0;
        } else {
            ans[i] = min(ans[i - l], r - i + 1);
        }
        while ((i + ans[i] < n) && (s[i + ans[i]] == s[ans[i]])) {
            ans[i]++;
        }
        if (i + ans[i] > r) {
            l = i;
            r = i + ans[i] - 1;
        }
    }
    return ans;
}
