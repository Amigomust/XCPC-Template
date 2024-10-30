vvi e(n + 1);
vi dfn(n + 1), low(n + 1), is_ecc(n + 1), fa(n + 1);
int timestamp = 0, ecc = 0;
std::function<void(int, int)> tarjan = [&](int u, int faa) {
    fa[u] = faa;
    low[u] = dfn[u] = ++timestamp;
    for (auto v : e[u]) {
        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = std::min(low[u], low[v]);
            if (low[v] > dfn[u]) {
                is_ecc[v] = 1;
                ecc++;
            }
        } else if (dfn[v] < dfn[u] && v != faa) {
            low[u] = std::min(low[u], dfn[v]);
        }
    }
};
for (int i = 1; i <= n; i++) {
    if (!dfn[i]) {
        tarjan(i, i);
    }
}

// TODO