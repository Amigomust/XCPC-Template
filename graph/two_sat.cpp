auto twoSat = [&](int n, const vpi& v) -> vi {
    /* tarjan */
    vvi e(2 * n);
    vi dfn(2 * n), low(2 * n), stk(2 * n), belong(2 * n);
    int timestamp = 0, top = 0, scc_cnt = 0;
    std::vector<bool> in_stk(2 * n);

    auto tarjan = [&](auto&& self, int u) -> void {
        dfn[u] = low[u] = ++timestamp;
        stk[++top] = u;
        in_stk[u] = true;
        for (const auto& v : e[u]) {
            if (!dfn[v]) {
                self(self, v);
                Min(low[u], low[v]);
            } else if (in_stk[v]) {
                Min(low[u], dfn[v]);
            }
        }
        if (dfn[u] == low[u]) {
            scc_cnt++;
            int v;
            do {
                v = stk[top--];
                in_stk[v] = false;
                belong[v] = scc_cnt;
            } while (v != u);
        }
    };
    /* end tarjan */

    for (const auto& [a, b] : v) {
        e[a].push_back(b ^ 1);
        e[b].push_back(a ^ 1);
    }
    for (int i = 0; i < 2 * n; i++) {
        if (!dfn[i]) tarjan(tarjan, i);
    }
    vi ans;
    for (int i = 0; i < 2 * n; i += 2) {
        if (belong[i] == belong[i + 1]) return vi{};
        ans.push_back(belong[i] > belong[i + 1] ? i + 1 : i);
    }
    return ans;
};