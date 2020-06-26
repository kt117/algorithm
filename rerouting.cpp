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


/*
verify: https://atcoder.jp/contests/abc160/tasks/abc160_f
*/


ll n;
vector<vector<ll>> g, dp;

vector<ll> ide(){
    return {1, 0};
}

vector<ll> f1(vector<ll> a, vector<ll> b){
    return {a[0]*b[0]%MOD, (a[0]*b[1]%MOD+a[1]*b[0]%MOD+a[1]*b[1]%MOD)%MOD};
}

vector<ll> f2(vector<ll> a){
    return {(a[0]+a[1])%MOD, a[0]};
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

void dfs2(ll at, ll from = -1, vector<ll> x = ide()){
    dp[at] = f2(f1(dp[at], x));

    ll m = g[at].size();
    vector<ll> l[m], r[m];
    zep(i, 0, m){l[i] = r[i] = (g[at][i] == from)? x : f2(dp[g[at][i]]);}
    rep(i, 1, m-1){l[i] = f1(l[i], l[i-1]);}
    rrep(i, m-2, 0){r[i] = f1(r[i], r[i+1]);}

    zep(i, 0, m){
        ll nx = g[at][i];
        if(nx != from){
            vector<ll> tmp = ide();
            if(i > 0){tmp = f1(tmp, l[i-1]);}
            if(i < m-1){tmp = f1(tmp, r[i+1]);}
            dfs2(nx, at, f2(tmp));
        }
    }
}


int main(){
    cin.tie(0); ios::sync_with_stdio(false);

    cin >> n;
    g.resize(n);
    dp.resize(n);
    zep(i, 0, n-1){
        ll a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs1(0);
    dfs2(0);
    print((dp[0][0]+dp[0][1])%MOD)
    return 0;
}