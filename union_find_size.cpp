#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> P;
const ll MOD = 1e9+7;
const ll INF = 1e18;
#define rep(i,m,n) for(int i = (m); i <= (n); i++)
#define zep(i,m,n) for(int i = (m); i < (n); i++)
#define rrep(i,m,n) for(int i = (m); i >= (n); i--)
#define print(x) cout << (x) << endl;
#define printa(x,m,n) for(int i = (m); i <= n; i++){cout << (x[i]) << " ";} cout<<endl;

struct union_find {
    vector<int> par, siz;
    union_find(int n) {
        par.resize(n);
        siz.resize(n);
        for(int i = 0; i < n; i++){
            par[i] = i;
            siz[i] = 1;
        }
    }
    
    int find(int x) {
        if (par[x] == x) return x;
        return par[x] = find(par[x]);
    }
 
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y)return;
        if (siz[x] < siz[y]) {
            par[x] = y;
            siz[y] += siz[x];
        }
        else {
            par[y] = x;
            siz[x] += siz[y];
        }
    }
    
    long long size(int x){
        return siz[find(x)];
    }

    bool same(int x, int y) {
        return (find(x) == find(y));
    }
};

int main(){
    cin.tie(0); ios::sync_with_stdio(false);
    
    ll n, m; cin >> n >> m;
    vector<vector<ll>> e;
    zep(i, 0, n-1){
        ll u, v, w; cin >> u >> v >> w;
        u--; v--;
        e.push_back({w, u, v});
    }
    sort(e.begin(), e.end());

    vector<P> pq(m);
    zep(i, 0, m){
        ll q; cin >> q;
        pq[i] = P(q, i);
    }
    sort(pq.begin(), pq.end());

    union_find uf(n);
    ll it = 0;
    ll res = 0;
    ll ans[m];
    zep(i, 0, m){
        while(it < e.size() && e[it][0] <= pq[i].first){
            if(!uf.same(e[it][1], e[it][2])){
                res += uf.size(e[it][1])*uf.size(e[it][2]);
                uf.unite(e[it][1], e[it][2]);
            }
            it++;
        }
        ans[pq[i].second] = res;
    }

    zep(i, 0, m){
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}