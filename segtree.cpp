#include <vector>

using namespace std;

struct Segtree {
	using Elem = int;
	const Elem e = 0;
	vector<Elem> t;
	int n;
	Elem op(Elem x, Elem y) {
		return x + y;
	}
	void build(int n) {
		t.assign(2 * n, e);
		this->n = n;
	}
	int get(int i) {
		return t[i + n];
	}
	void set(int i, Elem val) {
		t[i += n] = val;
		for (i >>= 1; i > 0; i >>= 1) {
			t[i] = op(t[i << 1], t[i << 1 | 1]);
		}
	}
	int query(int l, int r) {
		Elem al = e, ar = e;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) {
				al = op(al, t[l++]);
			}
			if (r & 1) {
				ar = op(t[--r], ar);
			}
		}
		return op(al, ar);
	}
};
