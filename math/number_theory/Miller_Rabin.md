# Miller Rabin 素性检验

原理基于：对奇素数 $p$，$a^2 \equiv 1 \bmod p$ 的解为 $x \equiv 1 \bmod p$ 或 $x \equiv p - 1 \bmod p$，以及费马小定理。

随机一个底数 $x$，将 $a ^ {p - 1} \bmod p$ 的指数 $p - 1$ 分解为 $a \times 2^b$，计算出 $x^a$，之后进行最多 $b$ 次平方操作，若发现非平凡平方根时即可判断出其不是素数，否则通过此轮测试。

$test\_time$ 为测试次数，建议设为不小于 $8$ 的整数以保证正确率，但也不宜过大，否则会影响效率。

事实上底数没必要随机 $10$ 次，检验如下数即可。快速幂记得也要 i128。

1. $int$ 范围：$2$，$7$，$61$。
2. $long \ long$ 范围：$2$，$325$，$9375$，$28178$，$450775$，$9780504$，$1795265022$。

```cpp
vl vv = {2, 7, 61};
vl vv = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
vl vv = {2, 3, 5, 7, 11, 13, 17, 23, 29};

auto miller_rabin = [&](LL n) -> bool {
    auto test = [&](LL n, LL a) {
        if (n == a) return true;
        if (n % 2 == 0) return false;
        LL d = (n - 1) >> __builtin_ctzll(n - 1);
        LL r = quick_power(a, d, n);
        while (d < n - 1 and r != 1 and r != n - 1) {
            d <<= 1;
            r = (i128) r * r % n;
        }
        return r == n - 1 or d & 1;
    };
    if (n == 2 or n == 3) return true;
    for (auto p : vv) {
        if (test(n, p) == 0) return false;
    }
    return true;
};
```

上面的有 bug, 对于 {5, 13, 19, 73, 193} 均会判 no. 

下面是一个通过 library checker 的版本.

```cpp
vl vv = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

auto quick_power = [&](LL a, LL n, LL mod) {
    LL ans = 1;
    while (n) {
        if (n & 1) ans = (i128) ans * a % mod;
        a = (i128) a * a % mod;
        n >>= 1;
    }
    return ans;
};

auto millerRabin = [&](LL n) {
    if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
    int s = __builtin_ctzll(n - 1);
    LL d = n >> s;
    for (auto a : vv) {
        LL p = quick_power(a % n, d, n);
        int i = s;
        while (p != 1 and p != n - 1 and a % n and i--) p = (i128) p * p % n;
        if (p != n - 1 and i != s) return false;
    }
    return true;
};
```

