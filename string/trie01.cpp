/* trie: 单词匹配 */
int cnt;
std::vector<std::array<int, 26>> trie(n + 1);
vi exist(n + 1);

auto insert = [&](const std::string& s) -> void {
    int p = 0;
    for (const auto ch : s) {
        int c = ch - 'a';
        if (!trie[p][c]) trie[p][c] = ++cnt;
        p = trie[p][c];
    }
    exist[p] = true;
};

auto find = [&](const string& s) -> bool {
    int p = 0;
    for (const auto ch : s) {
        int c = ch - 'a';
        if (!trie[p][c]) return false;
        p = trie[p][c];
    }
    return exist[p];
};