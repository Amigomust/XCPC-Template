int n, m, s;
vl dist(n + 1, INF);
std::vector<bool> vis(n + 1);
std::vector<PLI > e(n + 1);
 
void spfa(int s){
    rep(i, 1, n) dist[i] = INF;
    dist[s] = 0;
    std::queue<int> q;
    q.push(s);
    vis[s] = true;
    while(q.size()){
        auto u = q.front();
        q.pop();
        vis[u] = false;
        for(auto j : e[u]){
            int v = j.ff; LL w = j.ss;
            if(dist[v] > dist[u] + w){
                dist[v] = dist[u] + w;
                if(!vis[v]){
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
    }
}