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

ll n, m, r, R[9], a[20000], b[20000], c[20000], dst[201][201], dstr[9][9], dp[1<<8][8];

void warshall_floid(){
    for(ll k = 1; k <= n; k++)
        for(ll i = 1; i <= n; i++)
            for(ll j = 1; j <= n; j++)
                dst[i][j] = min(dst[i][k]+dst[k][j], dst[i][j]);
}

int main() {
    cin >> n >> m >> r;
    for(ll i = 0; i < r; i++)cin >> R[i];
    for(ll i = 1; i <= n; i++){for(ll j = 1; j <= n; j++){dst[i][j] = INF;} dst[i][i] = 0;}
    for(ll i = 0; i < m; i++){
        cin >> a[i] >> b[i] >> c[i];
        dst[a[i]][b[i]] = c[i];
        dst[b[i]][a[i]] = c[i];
    }
    
    warshall_floid();
    
    for(ll i = 0; i < r; i++){for(ll j = 0; j < r; j++){dstr[i][j] = dst[R[i]][R[j]];}}
    for(int bit = 0; bit < (1<<r); bit++){for(ll i = 0; i < r; i++){dp[bit][i] = INF;}}
    for(ll i = 0; i <= r; i++){dp[1<<i][i] = 0;}
    
    for(int bit = 0; bit < (1<<r); bit++){
        for(ll i = 0; i < r; i++){
            if(bit&(1<<i)){
                for(ll j = 0; j < r; j++){
                    if(bit&(1<<j) && j != i){
                        dp[bit][i] = min(dp[bit&~(1<<i)][j]+dstr[j][i], dp[bit][i]);
                    }
                }	
            }
        }
    }
    //for(ll i = 1; i <= n; i++){for(ll j = 1; j <= n; j++){cout << dst[i][j];}cout << endl;}
    //for(ll i = 0; i < r; i++){for(ll j = 0; j < r; j++){cout << dstr[i][j];}cout << endl;}
    ll ans = INF;
    for(ll i = 0; i < r; i++){ans = min(dp[(1<<r)-1][i], ans);}
    cout << ans;
    //for(int bit = 0; bit < (1<<r); bit++){for(ll i = 0; i < r; i++){cout << dp[bit][i] << endl;}}
    return 0;
}