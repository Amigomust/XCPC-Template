/* Problem: P3369 【模板】普通平衡树 */
struct node {
    int id, l, r;
    int ls, rs;
    int sum;

    node(int _id, int _l, int _r) : id(_id), l(_l), r(_r) {
        ls = rs = 0;
        sum = 0;
    }
};

/* segment tree */
int idx = 1;
std::vector<node> tree = {node{0, 0, 0}};

auto new_node = [&](int l, int r) -> int {
    tree.push_back(node(idx, l, r));
    return idx++;
};

auto push_up = [&](int u) -> void {
    tree[u].sum = 0;
    if (tree[u].ls) tree[u].sum += tree[tree[u].ls].sum;
    if (tree[u].rs) tree[u].sum += tree[tree[u].rs].sum;
};

auto build = [&]() { new_node(-inf, inf); };

std::function<void(int, int, int, int)> insert = [&](int u, int l, int r, int x) {
    if (l == r) {
        tree[u].sum++;
        return;
    }
    int mid = (l + r - 1) / 2;
    if (x <= mid) {
        if (!tree[u].ls) tree[u].ls = new_node(l, mid);
        insert(tree[u].ls, l, mid, x);
    } else {
        if (!tree[u].rs) tree[u].rs = new_node(mid + 1, r);
        insert(tree[u].rs, mid + 1, r, x);
    }
    push_up(u);
};

std::function<void(int, int, int, int)> remove = [&](int u, int l, int r, int x) {
    if (l == r) {
        if (tree[u].sum) tree[u].sum--;
        return;
    }
    int mid = (l + r - 1) / 2;
    if (x <= mid) {
        if (!tree[u].ls) return;
        remove(tree[u].ls, l, mid, x);
    } else {
        if (!tree[u].rs) return;
        remove(tree[u].rs, mid + 1, r, x);
    }
    push_up(u);
};

std::function<int(int, int, int, int)> get_rank_by_key = [&](int u, int l, int r, int x) -> int {
    if (l == r) {
        return 1;
    }
    int mid = (l + r - 1) / 2;
    int ans = 0;
    if (x <= mid) {
        if (!tree[u].ls) return 1;
        ans = get_rank_by_key(tree[u].ls, l, mid, x);
    } else {
        if (!tree[u].rs) return tree[tree[u].ls].sum + 1;
        if (!tree[u].ls) {
            ans = get_rank_by_key(tree[u].rs, mid + 1, r, x);
        } else {
            ans = get_rank_by_key(tree[u].rs, mid + 1, r, x) + tree[tree[u].ls].sum;
        }
    }
    return ans;
};

std::function<int(int, int, int, int)> get_key_by_rank = [&](int u, int l, int r, int x) -> int {
    if (l == r) {
        return l;
    }
    int mid = (l + r - 1) / 2;
    if (tree[u].ls) {
        if (x <= tree[tree[u].ls].sum) {
            return get_key_by_rank(tree[u].ls, l, mid, x);
        } else {
            return get_key_by_rank(tree[u].rs, mid + 1, r, x - tree[tree[u].ls].sum);
        }
    } else {
        return get_key_by_rank(tree[u].rs, mid + 1, r, x);
    }
};

std::function<int(int)> get_prev = [&](int x) -> int {
    int rank = get_rank_by_key(1, -inf, inf, x) - 1;
    debug(rank);
    return get_key_by_rank(1, -inf, inf, rank);
};

std::function<int(int)> get_next = [&](int x) -> int {
    debug(x + 1);
    int rank = get_rank_by_key(1, -inf, inf, x + 1);
    debug(rank);
    return get_key_by_rank(1, -inf, inf, rank);
};
