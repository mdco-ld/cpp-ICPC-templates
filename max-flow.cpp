#include <vector>
#include <functional>
#include <queue>
#include <climits>
using namespace std;

using ll = long long;

template<typename T>
using Fn = function<T>;

struct FlowGraph {
	struct Edge {
		int to;
		int rev;
		ll f;
		ll c;
	};
	vector<vector<Edge>> edges;
	vector<int> lvl;
	vector<int> nxt;
	FlowGraph(int n): edges(n), lvl(n), nxt(n) {
	}
	void addEdge(int from, int to, ll cap) {
		edges[from].emplace_back(to, edges[to].size(), 0, cap);
		edges[to].emplace_back(from, edges[from].size() - 1, 0, 0);
	}
	ll flow(int s, int t) {
		auto bfs = [&]() -> bool {
			fill(lvl.begin(), lvl.end(), 0);
			queue<int> q;
			q.push(s);
			lvl[s] = 1;
			while (q.size()) {
				int v = q.front();
				q.pop();
				for (auto &e: edges[v]) {
					if (lvl[e.to] || e.c == e.f) {
						continue;
					}
					lvl[e.to] = lvl[v] + 1;
					if (e.to == t) {
						return true;
					}
					q.push(e.to);
				}
			}
			return false;
		};
		Fn<ll(int, ll)> dfs = [&](int v, ll pushed) -> ll {
			if (v == t) {
				return pushed;
			}
			for (; nxt[v] < edges[v].size(); nxt[v]++) {
				auto &e = edges[v][nxt[v]];
				if (lvl[e.to] != lvl[v] + 1 || e.c == e.f) {
					continue;
				}
				if (ll df = dfs(e.to, min(pushed, e.c - e.f))) {
					return df;
				}
			}
			return 0;
		};
		ll mf = 0;
		while (bfs()) {
			fill(nxt.begin(), nxt.end(), 0);
			while (ll df = dfs(s, LLONG_MAX)) {
				mf += df;
			}
		}
		return mf;
	}
};
