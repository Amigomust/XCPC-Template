std::vector<vpi> e(n + 1);
for (int i = 1; i <= m; i++) {
    int u, v;
    std::cin >> u >> v;
    e[u].emplace_back(v, i);
    e[v].emplace_back(u, i);
}
vi dfn(n + 1), low(n + 1), is_ecc(n + 1), fa(n + 1), stk;
int timestamp = 0, ecc_cnt = 0;
vvi ecc(2 * n + 1);
std::function<void(int, int)> tarjan = [&](int u, int id) {
    low[u] = dfn[u] = ++timestamp;
    stk.push_back(u);
    for (auto [v, idx] : e[u]) {
        if (!dfn[v]) {
            tarjan(v, idx);
            low[u] = std::min(low[u], low[v]);
        } else if (idx != id) {
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        ecc_cnt++;
        int v;
        do {
            v = stk.back();
            stk.pop_back();
            ecc[ecc_cnt].push_back(v);
        } while (v != u);
    }
};
for (int i = 1; i <= n; i++) {
    if (!dfn[i]) {
        tarjan(i, 0);
    }
}