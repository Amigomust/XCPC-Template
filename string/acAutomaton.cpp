/* AC auto */
int cnt = 0;
const int N = 2e5 + 10;
static std::array<std::array<int, 26>, N> tr;
static std::array<int, N> exist, fail, ans, point;
vi order;

auto insert = [&](const auto& s) {
    int p = 0;
    for (const auto& ch : s) {
        int c = ch - 'a';
        if (!tr[p][c]) tr[p][c] = ++cnt;
        p = tr[p][c];
    }
    exist[p]++;
    return p;
};

auto build = [&]() {
    std::queue<int> q;
    for (int i = 0; i < 26; i++) {
        if (tr[0][i]) q.push(tr[0][i]);
    }
    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        order.push_back(u);
        for (int i = 0; i < 26; i++) {
            if (tr[u][i]) {
                fail[tr[u][i]] = tr[fail[u]][i];
                q.push(tr[u][i]);
            } else {
                tr[u][i] = tr[fail[u]][i];
            }
        }
    }
};

auto query = [&](const auto& s) {
    int p = 0;
    for (const auto ch : s) {
        p = tr[p][ch - 'a'];
        ans[p]++;
    }
    return;
};
/* AC auto */

std::vector<std::string> v(n);
for (int i = 0; i < n; i++) {
    auto& t = v[i];
    std::cin >> t;
    point[i] = insert(t);
}
build();
std::string s;
std::cin >> s;
query(s);
/* fail 树上子树求和 */
reverse(all(order));
for (const auto& i : order) ans[fail[i]] += ans[i];