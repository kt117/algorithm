#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> P;
const ll MOD = 1e9+7;
const ll INF = 1e18;
#define rep(i,m,n) for(ll i = (m); i <= (n); i++)
#define zep(i,m,n) for(ll i = (m); i < (n); i++)
#define rrep(i,m,n) for(ll i = (m); i >= (n); i--)
#define print(x) cout << (x) << endl;
#define printa(x,m,n) for(ll i = (m); i <= n; i++){cout << (x[i]) << " ";} cout<<endl;

struct union_find{
    vector<int> rnk, par;
    
    union_find(int n){
        rnk.resize(n);
        par.resize(n);
        for(int i = 0; i < n; i++){
            par[i] = i;
            rnk[i] = 0;
        }
    }
    
    int find(int x){
        if (par[x] == x) return x;
        return par[x] = find(par[x]);
    }
 
    void unite(int x, int y){
        x = find(x);
        y = find(y);
        if (x == y)return;
        if (rnk[x] < rnk[y]){
            par[x] = y;
        }
        else{
            par[y] = x;
            if (rnk[x] == rnk[y])rnk[x]++;
        }
    }
    
    bool same(int x, int y){
        return find(x) == find(y);
    }
};

int main(){
    cin.tie(0); ios::sync_with_stdio(false);
    
    ll n, q, p, a, b;
    cin >> n >> q;
    union_find u(n);
    zep(i, 0, q){
        cin >> p >> a >> b;
        if(p){
            print((u.same(a, b))? "Yes" : "No")
        }
        else{
            u.unite(a, b);
        }
    }
    return 0;
}
