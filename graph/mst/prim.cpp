int n, m, ans;
int g[N][N], dist[N];
bool vis[N];
int prim(){
    memset(dist, 0x3f, sizeof dist);
    for(int i = 1; i < n - 1; i++){
        int t = -1;
        for(int j = 1; j <= n; j++){
            if(!st[j] && (t == -1 || dist[t] > dist[j])) t = j;
        }      
        if(i && dist[t] == INF) return 0x3f3f3f3f;
        if(i) ans += dist[t];
        // if(i) ans = max(ans, dist[t]);
        vis[t] = true;
        for(int j = 1; j <= n; j++) dist[j] = min(dist[j], g[t][j]);
    }
    return ans;
}

int main() {
    // 添边，g[i][j]的值和Floyd一样储存 //
    int t = prim();
    if(t == 0x3f3f3f3f) // 不连通 //
    else cout << t << endl;
}