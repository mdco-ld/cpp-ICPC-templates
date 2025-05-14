#include <vector>
using namespace std;

struct Segtree {
    using E = int;
    E e = 0;
    vector<E> t;
    int n;
    E op(E x, E y) { return x + y; }
    void build(int N) {
        n = N;
        t.assign(2 * N, e);
    }
    void update(int i, E x) {
        t[i += n] = x;
        for (i >>= 1; i > 0; i >>= 1) {
            t[i] = op(t[i << 1], t[i << 1 | 1]);
        }
    }
    int query(int l, int r) {
        E al = e, ar = e;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                al = op(al, t[l++]);
            if (r & 1)
                ar = op(t[--r], ar);
        }
        return op(al, ar);
    }
};
