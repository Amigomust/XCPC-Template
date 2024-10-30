for (int i = 1; i <= n; i++) {
    while (!stk.empty() and stk.back() > a[i]) stk.pop_back();
    stk.pop_back(a[i]);
}
