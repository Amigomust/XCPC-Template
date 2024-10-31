struct line {
    point a, b;

    line(point _a = {}, point _b = {}) { a = _a, b = _b; }

    /* 交点类型为 double */
    friend point iPoint(line p, line q) {
        point v1 = p.b - p.a;
        point v2 = q.b - q.a;
        point u = q.a - p.a;
        return q.a + (q.b - q.a) * ((u ^ v1) * 1. / (v1 ^ v2));
    }

    /* 极角排序 */
    bool operator<(const line& p) const {
        double t1 = std::atan2((b - a).y, (b - a).x);
        double t2 = std::atan2((p.b - p.a).y, (p.b - p.a).x);
        if (fabs(t1 - t2) > eps) {
            return t1 < t2;
        }
        return ((p.a - a) ^ (p.b - a)) > eps;
    }
};