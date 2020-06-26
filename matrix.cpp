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
行列累乗, ModInt
verify: https://atcoder.jp/contests/dp/tasks/dp_r

TODO: 入出力を整える
*/


template<typename T> struct Matrix {
    vector<vector<T>> A;

    Matrix(int n, int m, T x) : A(n, vector<T> (n, x)) {}
    Matrix(vector<vector<T>> a) {
        A.resize(a.size());
        for (int i = 0; i < a.size(); i++) {
            A[i].resize(a[i].size());
            for (int j = 0; j < a[i].size(); j++)
                A[i][j] = a[i][j];
        }
    }
    
    size_t size() const {return A.size();}
    vector<T>& operator [] (int i) {return A[i];}
    const vector<T>& operator [] (int i) const {return A[i];}

    Matrix operator * (const Matrix &B) {
        Matrix<T> R(A.size(), B[0].size(), 0);
        for (int i = 0; i < A.size(); i++)
            for (int j = 0; j < B[0].size(); j++)
                for (int k = 0; k < B.size(); k++)
                    R[i][j] += A[i][k] * B[k][j];
        return R;
    }
};

template<typename T> Matrix<T> identity(int n) {
    Matrix<T> R(n, n, 0);
    for (int i = 0; i < n; i++) R[i][i] = 1;
    return R;
}

template<typename T> Matrix<T> pow(const Matrix<T> &A, long long x) {
    if (x == 0)return identity<T>(A.size());
    Matrix<T> R = pow(A, x / 2);
    return (x % 2)? R * R * A : R * R;
}


struct ModInt {
    long long v;
    //static long long MOD;
    
    ModInt (long long v) : v((v % MOD + MOD) % MOD) {}

    ModInt& operator += (const ModInt a) {v += a.v; v %= MOD; return *this;}
    ModInt& operator *= (const ModInt a) {v *= a.v; v %= MOD; return *this;}

    ModInt operator + (const ModInt a) const {return ModInt(*this) += a;}
    ModInt operator * (const ModInt a) const {return ModInt(*this) *= a;}

    //ostream
};


int main(){
    cin.tie(0); ios::sync_with_stdio(false);
    
    ll n, k; cin >> n >> k;
    Matrix<ModInt> a(n, n, 0);
    zep(i, 0, n){
        zep(j, 0, n){
            ll buf; cin >> buf;
            a[i][j] = buf;
        }
    }

    auto res = pow(a, k);
    ModInt ans = 0;
    zep(i, 0, n){
        zep(j, 0, n){
            ans += res[i][j];
        }
    }
    print(ans.v)
    return 0;
}