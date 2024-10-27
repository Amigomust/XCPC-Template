/* suffix array and ST table @ jiangly */
auto suffixArray = [&](const std::string& s) {
    int n = s.length();
    vi sa(n), rk(n);
    std::iota(all(sa), 0);
    std::sort(all(sa), [&](int a, int b) { return s[a] < s[b]; });
    rk[sa[0]] = 0;
    for (int i = 1; i < n; ++i) {
        rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
    }
    int k = 1;
    vi tmp(n), cnt(n);
    tmp.reserve(n);
    while (rk[sa[n - 1]] < n - 1) {
        tmp.clear();
        for (int i = 0; i < k; ++i) tmp.push_back(n - k + i);
        for (const auto& i : sa) {
            if (i >= k) tmp.push_back(i - k);
        }
        std::fill(all(cnt), 0);
        for (int i = 0; i < n; i++) cnt[rk[i]]++;
        for (int i = 1; i < n; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) sa[--cnt[rk[tmp[i]]]] = tmp[i];
        std::swap(rk, tmp);
        rk[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            rk[sa[i]] = rk[sa[i - 1]] + (tmp[sa[i - 1]] < tmp[sa[i]] or sa[i - 1] + k == n or
                                         tmp[sa[i - 1] + k] < tmp[sa[i] + k]);
        }
        k *= 2;
    }
    vi height(n);
    for (int i = 0, j = 0; i < n; ++i) {
        if (rk[i] == 0) continue;
        if (j) --j;
        while (s[i + j] == s[sa[rk[i] - 1] + j]) ++j;
        height[rk[i]] = j;
    }
    return std::make_tuple(sa, rk, height);
};
auto [sa, rk, height] = suffixArray(s);
vvi f(n, vi(30, inf));
vi Log2(n);
auto init = [&]() -> void {
    for (int i = 0; i < n; i++) {
        f[i][0] = height[i];
        if (i > 1) Log2[i] = Log2[i / 2] + 1;
    };
    int t = Log2.back();
    for (int j = 1; j <= t; j++) {
        for (int i = 0; i <= n - (1 << j); i++) {
            f[i][j] = std::min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
        }
    }
};
init();
auto query = [&](int l, int r) -> int {
    int t = Log2[r - l + 1];
    return std::min(f[l][t], f[r - (1 << t) + 1][t]);
};
auto lcp = [&](int i, int j) {
    i = rk[i], j = rk[j];
    if (i > j) std::swap(i, j);
    return query(i + 1, j);
};