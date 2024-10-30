std::vector<std::tuple<int, int, int>> edge;

// DSU //

auto kruskal = [&]() -> int {
    std::sort(all(edge), [&](std::tuple<int, int, int> a, std::tuple<int, int, int> b) {
        auto [x1, y1, w1] = a;
        auto [x2, y2, w2] = b;
        return w1 < w2;
    });
    int res = 0, cnt = 0;
    for (int i = 0; i < m; i++) {
        auto [a, b, w] = edge[i];
        a = find(a), b = find(b);
        if (a != b) {
            fa[a] = b;
            res += w;
            // res = std::max(res, w);
            cnt++;
        }
    }
    if (cnt < n - 1) return -1;
    return res;
}