#include <bits/stdc++.h>
using namespace std;
/* TYPES  */
#define int long long
#define mask(x) (1 << x)
#define all(x) x.begin(), x.end()
/* FUNCTIONS */
void ckmax(int &a, int b) { a = max(a, b); }
void ckmin(int &a, int b) { a = min(a, b); }
int gcd(int a, int b) { if (b==0) return a; return gcd(b, a%b); }
int lcm(int a, int b) { return a/gcd(a,b)*b; }
/* PRINTS */
const int INF = 4e18;
const int MOD = 1e9 + 7;

int binpow(int a, int b) {
    if (b == 0) return 1;
    int x = binpow(a, b / 2);
    if (b & 1) return x * x % MOD * a % MOD;
    return x * x % MOD;
}

const int N = 200000;
vector<int> it[2]; // it[0]: số lượng, it[1]: tổng vị trí
void update(int idx, int L, int R, int pos, int val, int t) {
    if (L == R) {
        it[t][idx] = (it[t][idx] % MOD + val % MOD) % MOD;
        return;
    }
    int M = (L + R) / 2;
    if (pos <= M) {
        update(idx * 2, L, M, pos, val, t);
    } 
    else {
        update(idx * 2 + 1, M + 1, R, pos, val, t);
    }
    it[t][idx] = (it[t][idx * 2] % MOD + it[t][idx * 2 + 1] % MOD) % MOD;
}

int get(int idx, int L, int R, int l, int r, int t) {
    if (l > R || r < L) return 0;
    if (l <= L && R <= r) {
        return it[t][idx];
    }
    int M = (L + R) / 2;
    return (get(idx * 2, L, M, l, r, t) % MOD + get(idx * 2 + 1, M + 1, R, l, r, t) % MOD) % MOD;
}

void OI() {
    it[0].assign(4 * (N + 1), 0);
    it[1].assign(4 * (N + 1), 0);
    int n; cin >> n;
    vector<int> a(n);
    for (int i=0; i<n; i++) {
        cin >> a[i];
    }
    update(1, 0, N, a[0], 1, 0);
    update(1, 0, N, a[0], a[0], 1); 
    int p = 1;
    for (int i=1; i<n; i++) {
        int cnt_left = get(1, 0, N, 0, a[i] - 1, 0);
        int cnt_right = get(1, 0, N, a[i] + 1, N, 0);
        int sum_left = get(1, 0, N, 0, a[i] - 1, 1);
        int sum_right = get(1, 0, N, a[i] + 1, N, 1);
        int cost_left = ((cnt_left % MOD) * (a[i] % MOD)) % MOD;
        cost_left = (cost_left - (sum_left % MOD) + MOD) % MOD;
        int cost_right = (sum_right % MOD);
        cost_right = (cost_right - (a[i] % MOD * cnt_right % MOD) + MOD) % MOD;
        int cur_cost = (cost_left % MOD + cost_right % MOD) % MOD;
        p = (p % MOD * cur_cost % MOD) % MOD;
        update(1, 0, N, a[i], 1, 0);
        update(1, 0, N, a[i], a[i], 1);
    }
    cout << p;
}
/*
https://codeforces.com/gym/625300/problem/R
x[i] = 10
[1, 4, 5, 6, x[i]] 
+ cost_left = (x[i] - 6) + (x[i] - 5) + (x[i] - 4) + (x[i] - 1)
+ cost_left = num_tree_left * x[i] - sum_pos_tree_left
[x[i], 11, 12, 15]
+ cost_right = (15 - x[i]) + (12 - x[i]) + (11 - x[i])
+ cost_right = sum_pos_tree_right - x[i] * num_tree_right
cost[x[i]]: cost_left + cost_right
*/
signed main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    int t = 1;
    while (t--) {
        OI();
    }
    return 0; 
}