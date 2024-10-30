auto Manacher = [&](const std::string& t) {
    std::string s = "#";
    for (char c : t) s += c, s += '#';
    int i, o = 0, r = 0, n = s.size();
    std::vector<int> p(n, 1), q(n);
    for (i = 0; i < n; ++i) {
        if (i <= r) p[i] = std::min(r - i + 1, p[2 * o - i]);
        for (; p[i] <= i && s[i + p[i]] == s[i - p[i]]; ++p[i]);
        if (i + p[i] - 1 > r) r = i + p[i] - 1, o = i;
    }
    return p;
};