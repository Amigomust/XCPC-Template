/* fhq treap */
struct node {
    node *ch[2];
    int key, val;
    int cnt, size;

    node(int _key) : key(_key), cnt(1), size(1) {
        ch[0] = ch[1] = nullptr;
        val = rand();
    }

    // node(node *_node) {
    // key = _node->key, val = _node->val, cnt = _node->cnt, size = _node->size;
    // }

    inline void push_up() {
        size = cnt;
        if (ch[0] != nullptr) size += ch[0]->size;
        if (ch[1] != nullptr) size += ch[1]->size;
    }
};

struct treap {
#define _2 second.first
#define _3 second.second

    node *root;

    pair<node *, node *> split(node *p, int key) {
        if (p == nullptr) return {nullptr, nullptr};
        if (p->key <= key) {
            auto temp = split(p->ch[1], key);
            p->ch[1] = temp.first;
            p->push_up();
            return {p, temp.second};
        } else {
            auto temp = split(p->ch[0], key);
            p->ch[0] = temp.second;
            p->push_up();
            return {temp.first, p};
        }
    }

    pair<node *, pair<node *, node *> > split_by_rank(node *p, int rank) {
        if (p == nullptr) return {nullptr, {nullptr, nullptr}};
        int ls_size = p->ch[0] == nullptr ? 0 : p->ch[0]->size;
        if (rank <= ls_size) {
            auto temp = split_by_rank(p->ch[0], rank);
            p->ch[0] = temp._3;
            p->push_up();
            return {temp.first, {temp._2, p}};
        } else if (rank <= ls_size + p->cnt) {
            node *lt = p->ch[0];
            node *rt = p->ch[1];
            p->ch[0] = p->ch[1] = nullptr;
            return {lt, {p, rt}};
        } else {
            auto temp = split_by_rank(p->ch[1], rank - ls_size - p->cnt);
            p->ch[1] = temp.first;
            p->push_up();
            return {p, {temp._2, temp._3}};
        }
    }

    node *merge(node *u, node *v) {
        if (u == nullptr && v == nullptr) return nullptr;
        if (u != nullptr && v == nullptr) return u;
        if (v != nullptr && u == nullptr) return v;
        if (u->val < v->val) {
            u->ch[1] = merge(u->ch[1], v);
            u->push_up();
            return u;
        } else {
            v->ch[0] = merge(u, v->ch[0]);
            v->push_up();
            return v;
        }
    }

    void insert(int key) {
        auto temp = split(root, key);
        auto l_tr = split(temp.first, key - 1);
        node *new_node;
        if (l_tr.second == nullptr) {
            new_node = new node(key);
        } else {
            l_tr.second->cnt++;
            l_tr.second->push_up();
        }
        node *l_tr_combined = merge(l_tr.first, l_tr.second == nullptr ? new_node : l_tr.second);
        root = merge(l_tr_combined, temp.second);
    }

    void remove(int key) {
        auto temp = split(root, key);
        auto l_tr = split(temp.first, key - 1);
        if (l_tr.second->cnt > 1) {
            l_tr.second->cnt--;
            l_tr.second->push_up();
            l_tr.first = merge(l_tr.first, l_tr.second);
        } else {
            if (temp.first == l_tr.second) temp.first = nullptr;
            delete l_tr.second;
            l_tr.second = nullptr;
        }
        root = merge(l_tr.first, temp.second);
    }

    int get_rank_by_key(node *p, int key) {
        auto temp = split(p, key - 1);
        int ret = (temp.first == nullptr ? 0 : temp.first->size) + 1;
        root = merge(temp.first, temp.second);
        return ret;
    }

    int get_key_by_rank(node *p, int rank) {
        auto temp = split_by_rank(p, rank);
        int ret = temp._2->key;
        root = merge(temp.first, merge(temp._2, temp._3));
        return ret;
    }

    int get_prev(int key) {
        auto temp = split(root, key - 1);
        int ret = get_key_by_rank(temp.first, temp.first->size);
        root = merge(temp.first, temp.second);
        return ret;
    }

    int get_nex(int key) {
        auto temp = split(root, key);
        int ret = get_key_by_rank(temp.second, 1);
        root = merge(temp.first, temp.second);
        return ret;
    }
} tr;
