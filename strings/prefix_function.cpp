vector<int> pr_fn(string s) {
    int n = s.size();
    vector<int> ans(n);
    int z = 0;
    for (int i = 1; i < n; ++i) {
        while ((z > 0) && (s[z] != s[i])) {
            z = ans[z - 1];
        }
        if (s[z] == s[i]) z++;
        ans[i] = z;
    }
    return ans;
}
