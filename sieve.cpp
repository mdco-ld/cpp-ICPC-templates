#include <vector>
using namespace std;
struct Sieve {
    vector<int> spf, pr;
    
    Sieve(int n) : spf(n + 1) {
        for (int i = 2; i <= n; i++) {
            if (!spf[i]) {
                spf[i] = i;
                pr.push_back(i);
            }
            for (int p : pr) {
                if (p > spf[i] || i * p > n) break;
                spf[i * p] = p;
            }
        }
    }
    
    bool is_prime(int x) { return spf[x] == x; }
};
