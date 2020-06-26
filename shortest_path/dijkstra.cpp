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
#define printa(x,m,n) for(int i = (m); i <= n; i++){cout << (x[i]) << " ";} cout<<endl;


/*
verify: https://atcoder.jp/contests/abc164/tasks/abc164_e
reference: プログラミングコンテストチャレンジブック [第2版]
*/


struct dijkstra{
    vector<long long> min_dst;
    vector<vector<pair<long long, long long>>> G;

    dijkstra(int n){
        min_dst.resize(n);
        G.resize(n);
    }

    void append(int u, int v, long long cost){G[u].push_back(make_pair(v, cost));}
    
    void run(int s){
        priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> que;
        fill(min_dst.begin(), min_dst.end(), -1);
        min_dst[s] = 0;
        que.push(make_pair(0, s));
        
        while(!que.empty()){
            auto p = que.top(); que.pop();
            int at = p.second;
            if(min_dst[at] < p.first){continue;}
            for(int i = 0; i < G[at].size(); i++){
                int to = G[at][i].first;
                long long cost = G[at][i].second;
                if(min_dst[to] == -1 || min_dst[at] + cost < min_dst[to]){
                    min_dst[to] = min_dst[at] + cost;
                    que.push(make_pair(min_dst[to], to));
                }
            }
        }	
    }
    
    long long get(int at){return min_dst[at];}
};


int main(){
    cin.tie(0); ios::sync_with_stdio(false);
    
    ll n, m, s; cin >> n >> m >> s;
    ll u[m], v[m], a[m], b[m];
    zep(i, 0, m){
        cin >> u[i] >> v[i] >> a[i] >> b[i];
        u[i]--; v[i]--;
    }    
    ll c[n], d[n]; zep(i, 0, n)cin >> c[i] >> d[i];

    ll mo = 50*n;
    dijkstra di(n*(mo+1));
    zep(i, 0, m){
        rep(j, a[i], mo){
            di.append(u[i]*(mo+1)+j, v[i]*(mo+1)+j-a[i], b[i]);
            di.append(v[i]*(mo+1)+j, u[i]*(mo+1)+j-a[i], b[i]);
        }
    }

    zep(i, 0, n){
        rep(j, 0, mo-c[i]){
            di.append(i*(mo+1)+j, i*(mo+1)+j+c[i], d[i]);
        }
    }

    ll st = min(s, mo);
    di.run(st);

    zep(i, 1, n){
        ll ans = INF;
        rep(j, 0, mo){
            ans = min(ans, di.get(i*(mo+1)+j));
        }
        print(ans)
    }
    
    return 0;
}