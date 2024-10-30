int n, m;
int belong[N], stk[N], tops, cc_cnt;
bool vis[N];
vector<int> g1[N], g2[N];
void add(int a, int b){
    g1[a].push_back(b);
    g2[b].push_back(a);
}
void dfs1(int u){
    vis[u] = true;
    for (int v : g1[u]){
        if (!vis[v]) dfs1(v);
    }
    stk[++top] = u;
}
void dfs2(int u){
    belong[u] = scc_cnt;
    for (int v : g2[u]){
        if (!belong[v]) dfs2(v);
    }
}
void kosaraju(){
    scc_cnt = 0;
    for (int i = 1; i <= n; i++){
        if (!vis[i]) dfs1(i);
    }
    for (int i = n; i >= 1; i--){
        if (!belong[stk[i]]){
            scc_cnt++;
            dfs2(stk[i]);
        }
    }
}

int main(){
    cin >> n >> m;
    for (int i = 1; i <= m; i++){
        int a, b;
        cin >> a >> b;
        add(a, b);
    }
    kosaraju();
    return 0;
}