int n, m, s;
int dist[N];
struct node{
    int from, to, w;
}edge[M];
void bellman_fold(int s){
    memset(dist, 0x3f, sizeof(dist));
    dist[s] = 0;
    for(int i = 1; i <= n; i++){
        bool flag = true;
        for(int j = 1; j <= m; j++){
            int a = edge[j].from, b = edge[j].to, w = edge[j].w;
            if(dist[a] == 0x3f3f3f3f) continue;
            if(dist[b] > dist[a] + w){
                dist[b] = dist[a] + w;
                flag = false;
            }
        }
        if(flag) break;
    }
}