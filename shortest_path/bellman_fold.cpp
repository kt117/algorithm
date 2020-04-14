#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> P;
const ll MOD = 1e9 + 7;
const ll INF = 1e18;
#define rep(i,m,n) for(ll i = (m); i <= (n); i++)
#define rrep(i,m,n) for(ll i = (m); i >= (n); i--)
#define print(x) cout << (x) << endl;
#define printa(x,m,n) for(ll i = (m); i <= n; i++){cout << (x[i]) << " ";} cout<<endl;

struct bellman_fold{//1-origin
    vector<ll> min_dst;
    vector<vector<ll>> edge;
    bool negative_loop = false;
    bellman_fold(ll n){
        min_dst.resize(n);
    }

    void append(ll u, ll v, ll cost){edge.push_back({u-1, v-1, cost});}
    
    void run(ll s){
        fill(min_dst.begin(), min_dst.end(), 1e18);
        min_dst[s-1] = 0;
        
        for(ll ite = 1; ite <= min_dst.size(); ite++){
            for(ll j = 0; j < edge.size(); j++){
                if(min_dst[edge[j][0]]+edge[j][2] < min_dst[edge[j][1]]){
                    min_dst[edge[j][1]] = min_dst[edge[j][0]] + edge[j][2];
                    if(ite == min_dst.size()){
                        negative_loop = true;
                    }
                }
            }
        }
    }
    
    ll get(ll at){return min_dst[at-1];}
    
    bool loop(){return negative_loop;}
};

ll n, m, p, a, b, c;

int main(){
    cin.tie(0); ios::sync_with_stdio(false);
    
    cin >> n >> m >> p;
    bellman_fold bf(n);
    rep(i, 1, n){
        cin >> a >> b >> c;
        bf.append(a, b, -c+p);
    }
    bf.run(1);
    
    if(bf.loop()){
        print(-1)
    }
    else{
        print(max(-bf.get(n), 0LL))
    }
    return 0;
}