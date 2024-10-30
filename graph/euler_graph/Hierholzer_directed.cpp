struct node{
    int to;
    bool exist;
};
vector<node> edge[N];
vector<int> ans;
int n, m, flag1, flag2;
int d[N], last[N];
bool cmp(node a, node b){
    return a.to < b.to;
}
void hierholzer(int u){
    for(int i = 0; i < edge[u].size(); i = max(i, last[u]) + 1){
        // 比i++能加速 //
        if(edge[u][i].exist){
            edge[u][i].exist = 0;
            last[u] = i;
            hierholzer(edge[u][i].to);
        }
    }
    ans.push_back(u);
}
bool check(){
    for(int i = 1; i <= n; i++){
        if(d[i] > 1 || d[i] < -1) return 0;
        if(d[i] == 1) flag1++;
        else if(d[i] == -1) flag2++;
    }
    if(flag1 > 1 || flag2 > 1) return 0;
    return 1;
}
int main(){
    /* 边：a -> b
        scanf("%d%d", &a, &b);
        edge[a].push_back((node){b, 1});
        d[a]++;
        d[b]--;
    */
    for(int i = 1; i <= n; i++){
        sort(edge[i].begin(), edge[i].end(), cmp);
    }
    // 要求字典序最下，对边排序 //
    if(!check()){
        cout << "No" << endl;
        return 0;
    }
    int id = 1;
    for(int i = 1; i <= n; i++){
        if(d[i] == 1){
            id = i;
            break;
        }
    }
    hierholzer(id);
    for(int i = ans.size() - 1; i >= 0; i--){
        printf("%d ", ans[i]);
    }
    return 0;
}