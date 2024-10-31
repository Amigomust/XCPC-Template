auto exgcd = [&](auto&& self, LL a, LL b, LL& x, LL& y) {
    if (!b) {
        x = 1, y = 0;
        return;
    }
    self(self, b, a % b, y, x);
    y -= a / b * x;
};