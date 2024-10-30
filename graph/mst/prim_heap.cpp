typedef pair<int, int> PII;
int n, m, ans, cnt;
int h[M], e[M], ne[M], w[M], idx;
int dist[N];
bool vis[N];
void add(int a, int b, int c){
    e[++idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx;
}
void prim(){
    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0;
    priority_queue<PII, vector<PII>, greater<PII> > q;
    q.push({0, 1});
    while(!q.empty() && cnt < n){
        auto t = q.top();
        q.pop();
        int ver = t.second, distance = t.first;
        if(vis[ver]) continue;
        cnt++;
        ans += distance;
        // sum = max(sum, distance);
        vis[ver] = true;
        for(int i = h[ver]; i; i = ne[i]){
            int j = e[i];
            if(dist[j] > w[i]){
                dist[j] = w[i];
                q.push({dist[j], j});
            }
        }
    }
}

int main(){
    // 添边 //
    prim();
    if(cnt == n) cout << ans << endl;
    else // 不连通 //
}