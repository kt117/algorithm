#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> P;
const ll MOD = 1e9+7;
const ll INF = 1e18;
#define rep(i,m,n) for(ll i = (m); i <= (n); i++)
#define rrep(i,m,n) for(ll i = (m); i >= (n); i--)
#define print(x) cout << (x) << endl;
#define printa(x,m,n) for(ll i = (m); i <= n; i++){cout << (x[i]) << " ";} cout<<endl;

struct dijkstra{//1-origin
    vector<ll> min_dst;
    vector<vector<P>> G;
    dijkstra(ll n){
        min_dst.resize(n);
        G.resize(n);
    }

    void append(ll u, ll v, ll cost){G[u-1].push_back(P(v-1, cost));}
    
    void run(ll s){
        priority_queue<P, vector<P>, greater<P>> que;
        fill(min_dst.begin(), min_dst.end(), -1);
        min_dst[s-1] = 0;
        que.push(P(0, s-1));
        
        while(!que.empty()){
            P p = que.top(); que.pop();
            ll at = p.second;
            if(min_dst[at] < p.first){continue;}
            for(ll i = 0; i < G[at].size(); i++){
                ll to = G[at][i].first;
                ll cost = G[at][i].second;
                if(min_dst[to] == -1 || min_dst[at]+cost < min_dst[to]){
                    min_dst[to] = min_dst[at]+cost;
                    que.push(P(min_dst[to], to));
                }
            }
        }	
    }
    
    ll get(ll at){return min_dst[at-1];}
};

ll n, m, l, r, c;
string s;

int main(){
    cin.tie(0); ios::sync_with_stdio(false);
    
    cin >> n >> m;
    dijkstra d(n);
    rep(i, 1, m){
        cin >> l >> r >> c;
        d.append(l, r, c);
    }
    rrep(i, n-1, 1){
        d.append(i+1, i, 0);
    }
    d.run(1);
    print(d.get(n))
    return 0;
}