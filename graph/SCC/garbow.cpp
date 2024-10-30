int n, m;
int e[N], ne[N], h[N], idx;
int belong[N], stack1[N], stack2[N], low[N], timestamp, p1, p2, scc_cnt;
void add(int a, int b){
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}
int garbow(int u){
    stack1[++p1] = u;
    stack2[++p2] = u;
    low[u] = ++timestamp;
    for (int i = h[u]; i != -1; i = ne[i]){
        int v = e[i];
        if (!low[v]){
            garbow(v);
        }
        else if (!belong[v]){
            while (low[stack2[p2]] > low[v]) p2--;
        }
    }
    if (stack2[p2] == u){
        p2--;
        scc_cnt++;
        do{
            belong[stack1[p1]] = scc_cnt;
        } while (stack1[p1--] != u);
    }
    return 0;
}
void init(){
    timestamp = scc_cnt = 0;
    p1 = p2 = 0;
    memset(belong, 0, sizeof(belong));
    memset(low, 0, sizeof(low));
}

int main(){
    cin >> n >> m;
    init();
    memset(h, -1, sizeof(h));
    for (int i = 1; i <= m; i++){
        int a, b;
        cin >> a >> b;
        add(a, b);
    }
    for (int i = 1; i <= n; i++){
        if (!low[i]) garbow(i);
    }
    return 0;
}