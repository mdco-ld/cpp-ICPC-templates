#include <vector>
#include <numeric>
using namespace std;

struct Sieve {
	vector<int> spf, pr;
	Sieve(int n): spf(n) {
		iota(spf.begin(), spf.end(), 0);
		for (int i = 2; i < n; i++) {
			if (spf[i] == i) {
				pr.push_back(i);
			}
			for (int j = 0; pr[j] * i < n && j < pr.size(); j++) {
				spf[pr[j] * i] = pr[j];
				if (pr[j] == spf[i]) {
					break;
				}
			}
		}
	}
};
