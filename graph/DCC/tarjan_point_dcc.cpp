vvi e(n + 1);
vi dfn(n + 1), low(n + 1), is_bcc(n + 1), stk;
int timestamp = 0, bcc_cnt = 0, root = 0;
vvi bcc(2 * n + 1);
std::function<void(int, int)> tarjan = [&](int u, int fa) {
    dfn[u] = low[u] = ++timestamp;
    int child = 0;
    stk.push_back(u);
    if (u == root and e[u].empty()) {
        bcc_cnt++;
        bcc[bcc_cnt].push_back(u);
        return;
    }
    for (auto v : e[u]) {
        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = std::min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                child++;
                if (u != root or child > 1) {
                    is_bcc[u] = 1;
                }
                bcc_cnt++;
                int z;
                do {
                    z = stk.back();
                    stk.pop_back();
                    bcc[bcc_cnt].push_back(z);
                } while (z != v);
                bcc[bcc_cnt].push_back(u);
            }
        } else if (v != fa) {
            low[u] = std::min(low[u], dfn[v]);
        }
    }
};
for (int i = 1; i <= n; i++) {
    if (!dfn[i]) {
        root = i;
        tarjan(i, i);
    }
}