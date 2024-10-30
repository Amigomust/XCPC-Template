/* 洛谷 P3369 【模板】普通平衡树 */
struct Treap {
    int id = 1, maxlog = 25;
    int ch[N * 25][2], siz[N * 25];

    int newnode() {
        id++;
        ch[id][0] = ch[id][1] = siz[id] = 0;
        return id;
    }

    void merge(int key, int cnt) {
        int u = 1;
        for (int i = maxlog - 1; i >= 0; i--) {
            int v = (key >> i) & 1;
            if (!ch[u][v]) ch[u][v] = newnode();
            u = ch[u][v];
            siz[u] += cnt;
        }
    }

    int get_key_by_rank(int rank) {
        int u = 1, key = 0;
        for (int i = maxlog - 1; i >= 0; i--) {
            if (siz[ch[u][0]] >= rank) {
                u = ch[u][0];
            } else {
                key |= (1 << i);
                rank -= siz[ch[u][0]];
                u = ch[u][1];
            }
        }
        return key;
    }

    int get_rank_by_key(int rank) {
        int key = 0;
        int u = 1;
        for (int i = maxlog - 1; i >= 0; i--) {
            if ((rank >> i) & 1) {
                key += siz[ch[u][0]];
                u = ch[u][1];
            } else {
                u = ch[u][0];
            }
            if (!u) break;
        }
        return key;
    }

    int get_prev(int x) { return get_key_by_rank(get_rank_by_key(x)); }
    int get_next(int x) { return get_key_by_rank(get_rank_by_key(x + 1) + 1); }
} treap;

constexpr int num = 1e7;
int n, op, x;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> op >> x;
        if (op == 1) {
            treap.merge(x + num, 1);
        } else if (op == 2) {
            treap.merge(x + num, -1);
        } else if (op == 3) {
            std::cout << treap.get_rank_by_key(x + num) + 1 << endl;
        } else if (op == 4) {
            std::cout << treap.get_key_by_rank(x) - num << endl;
        } else if (op == 5) {
            std::cout << treap.get_prev(x + num) - num << endl;
        } else if (op == 6) {
            std::cout << treap.get_next(x + num) - num << endl;
        }
    }
    return 0;
}
