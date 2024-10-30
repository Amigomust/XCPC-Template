/* linear basis */
vl p(63), s(63);  /* basis and case */
auto insert = [&](LL x, int id) {
    LL ans = 0;
    for (int i = 62; i >= 0; i--) {
        if (~(x >> i) & 1) continue;
        if (!p[i]) {
            p[i] = x;
            s[i] = ans ^ (1ll << id);
            break;
        }
        x ^= p[i], ans ^= s[i];
    }
    return x;
};
auto query = [&](LL x) {
    LL ans = 0;
    for (int i = 62; i >= 0; i--) {
        if (~(x >> i) & 1) continue;
        x ^= p[i], ans ^= s[i];
    }
    return (x ? -1 : ans);
};
auto queryMax = [&]() {
    LL ans = 0;
    for (int i = 62; i >= 0; i--)
        if ((ans ^ p[i]) > ans) ans ^= p[i];
    return ans;
};