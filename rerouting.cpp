//後で抽象化します。
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

const long long MAX = 2e5+100;
long long fac[MAX], finv[MAX], inv[MAX];

void COMinit() {
    fac[0] = fac[1] = 1;
    finv[0] = finv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < MAX; i++){
        fac[i] = fac[i - 1] * i % MOD;
        inv[i] = MOD - inv[MOD%i] * (MOD / i) % MOD;
        finv[i] = finv[i - 1] * inv[i] % MOD;
    }
}

long long COM(int n, int k){
    if (n < k) return 0;
    if (n < 0 || k < 0) return 0;
    return fac[n] * (finv[k] * finv[n - k] % MOD) % MOD;
}

ll n;
vector<vector<ll>> g;
P dp[MAX];

P ide(){
    return P(0, 1);
}

P f1(P a, P b){
    return P(a.first+b.first, (a.second*b.second%MOD)*COM(a.first+b.first, b.first)%MOD);
}

P f2(P a){
    return P(a.first+1, a.second);
}

void dfs1(ll at, ll from = -1){
    dp[at] = ide();
    zep(i, 0, g[at].size()){
        ll nx = g[at][i];
        if(nx != from){
            dfs1(nx, at);
            dp[at] = f1(dp[at], f2(dp[nx]));
        }
    }
}

void dfs2(ll at, ll from = -1, P x = P(0, 1)){
    dp[at] = f2(f1(dp[at], x));

    ll m = g[at].size();
    P l[m], r[m];
    zep(i, 0, m){l[i] = r[i] = (g[at][i] == from)? x : f2(dp[g[at][i]]);}
    rep(i, 1, m-1){l[i] = f1(l[i], l[i-1]);}
    rrep(i, m-2, 0){r[i] = f1(r[i], r[i+1]);}

    zep(i, 0, m){
        ll nx = g[at][i];
        if(nx != from){
            P tmp = ide();
            if(i > 0){tmp = f1(tmp, l[i-1]);}
            if(i < m-1){tmp = f1(tmp, r[i+1]);}
            dfs2(nx, at, f2(tmp));
        }
    }
}

int main(){
    cin.tie(0); ios::sync_with_stdio(false);
    
    COMinit();

    cin >> n;
    g.resize(n);
    zep(i, 0, n-1){
        ll a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs1(0);    
    dfs2(0);

    zep(i, 0, n){print(dp[i].second)}
    return 0;
}