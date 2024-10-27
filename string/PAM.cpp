/* PAM @ ddl */
std::vector<node> tr;
std::vector<int> stk;
auto newnode = [&](int len) {
    tr.emplace_back();
    tr.back().len = len;
    return (int) tr.size() - 1;
};
auto PAMinit = [&]() {
    newnode(0), tr.back().fail = 1;
    newnode(-1), tr.back().fail = 0;
    stk.push_back(-1);
};
PAMinit();
auto getfail = [&](int v) {
    while (stk.end()[-2 - tr[v].len] != stk.back()) {
        v = tr[v].fail;
    }
    return v;
};
auto insert = [&](int last, int c, int cnt) {
    stk.emplace_back(c);
    int x = getfail(last);
    if (!tr[x].ch[c]) {
        int u = newnode(tr[x].len + 2);
        tr[u].fail = tr[getfail(tr[x].fail)].ch[c];
        tr[x].ch[c] = u;
        /* tr[u].size = tr[tr[u].fail].size + 1; */
        /* Can be used to count the number of types of palindromic strings ending at the current
         * position */
    }
    tr[tr[x].ch[c]].size += cnt;
    return tr[x].ch[c];
};
auto build = [&]() {  /* DP on fail tree */
    int ans = 0;
    for (int i = (int) tr.size() - 1; i > 1; i--) {
        tr[tr[i].fail].size += tr[i].size;
        /* options */
    }
    return ans;
};
/* PAM */
int ans = 0, last = 0;
for (int i = 0; i < n; i++) {
    last = insert(last, s[i] - 'a', 1);
}
