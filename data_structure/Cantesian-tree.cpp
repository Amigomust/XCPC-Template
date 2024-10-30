/* Cartesian tree */
vi ls(n + 1), rs(n + 1), stk(n + 1);
int top = 1;
for (int i = 1; i <= n; i++) {
    int k = top;
    while (k and a[stk[k]] > a[i]) k--;
    if (k) rs[stk[k]] = i;
    if (k < top) ls[i] = stk[k + 1];
    stk[++k] = i;
    top = k;
}
