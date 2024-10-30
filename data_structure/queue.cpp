std::deque<int> q;
for (int i = 1; i <= n; i++) {
    while (!q.empty and a[q.back()] >= a[i]) p.pop_back();
    if (!q.empty() and i - q.front() >= k) q.pop_front();
    q.push_back(i);
}
