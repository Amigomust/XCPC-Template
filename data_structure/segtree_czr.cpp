const int N = 100010;
struct node {
    int l, r;
    ll sum, maxn, add, set;
    bool addflag, setflag;
}tr[N << 2];

void push_up(int u) {
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
    tr[u].maxn = max(tr[u << 1].maxn, tr[u << 1 | 1].maxn);
}
// 0 4 0 0 0
// 2 6 2 2 2
// 2 6 2 4 4

void push_down(int u) {
    auto& root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
    if (root.setflag) {
        assert(!root.addflag);
        left.add = 0, left.set = root.set, left.addflag = false, left.setflag = true;
        right.add = 0, right.set = root.set, right.addflag = false, right.setflag = true;
        left.sum = root.set * (left.r - left.l + 1);
        right.sum = root.set * (right.r - right.l + 1);
        left.maxn = root.set;
        right.maxn = root.set;
        root.set = 0, root.setflag = false;
    }
    if (root.addflag) {
        assert(!root.setflag);
        if (left.setflag) left.set += root.add;
        else left.add += root.add, left.addflag = true;
        if (right.setflag) right.set += root.add;
        else right.add += root.add, right.addflag = true;
        
        left.sum += root.add * (left.r - left.l + 1);
        right.sum += root.add * (right.r - right.l + 1);
        left.maxn += root.add;
        right.maxn += root.add;
        root.add = 0, root.addflag = false;
    }
    assert(root.add == 0);
}

void build(int u, int l, int r, vector<ll>& a) {
    if (l == r) {
        tr[u].l = tr[u].r = l, tr[u].sum = tr[u].maxn = a[l];
        tr[u].add = 0, tr[u].set = 0;
        tr[u].addflag = tr[u].setflag = false;
    } else {
        tr[u].l = l, tr[u].r = r, tr[u].add = 0, tr[u].set = 0;
        tr[u].addflag = tr[u].setflag = false;
        int mid = l + r >> 1;
        build(u << 1, l, mid, a);
        build(u << 1 | 1, mid + 1, r, a);
        push_up(u);
    }
}

// 区间加
void modify(int u, int l, int r, ll d) {
    if (l > r) return;
    if (tr[u].l >= l && tr[u].r <= r) {
        if (tr[u].setflag) tr[u].set += d;
        else tr[u].add += d, tr[u].addflag = true;
        tr[u].sum += d * (tr[u].r - tr[u].l + 1);
        tr[u].maxn += d;
    } else {
        push_down(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(u << 1, l, r, d);
        if (r > mid) modify(u << 1 | 1, l, r, d);
        push_up(u); 
    }
}

// 区间赋值
void update(int u, int l, int r, ll x) {
    if (l > r) return;
    if (tr[u].l >= l && tr[u].r <= r) {
        tr[u].set = x, tr[u].setflag = true;
        tr[u].add = 0, tr[u].addflag = false;
        tr[u].sum = x * (tr[u].r - tr[u].l + 1);
        tr[u].maxn = x;
    } else {
        push_down(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) update(u << 1, l, r, x);
        if (r > mid) update(u << 1 | 1, l, r, x);
        push_up(u);
    }
}

ll query_sum(int u, int l, int r) {
    if (l > r) return 0;
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].sum;
    else {
        ll res = 0;
        push_down(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) res += query_sum(u << 1, l, r);
        if (r > mid) res += query_sum(u << 1 | 1, l, r);
        return res;
    }
}

ll query_maxn(int u, int l, int r) {
    if (l > r) return -1e18;
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].maxn;
    else {
        ll res = -1e18;
        push_down(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) res = max(res, query_maxn(u << 1, l, r));
        if (r > mid) res = max(res, query_maxn(u << 1 | 1, l, r));
        return res;
    }
}

// 找到最小 i 使得 sum(l，i) >= k
ll find_presum_idx(int u, int l, int r, int x) {
    if (tr[u].l == tr[u].r) return tr[u].l;
    else {
        push_down(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (r <= mid) {
            return find_presum_idx(u << 1, l, r, x);
        } else if (l > mid) {
            return find_presum_idx(u << 1 | 1, l, r, x);
        } else {
            ll lsum = query_sum(u << 1, l, r);
            if (lsum >= x) return find_presum_idx(u << 1, l, mid, x);
            else return find_presum_idx(u << 1 | 1, mid + 1, r, x - lsum);
        }
    }
}
