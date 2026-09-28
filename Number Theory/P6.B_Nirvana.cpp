// https://codeforces.com/problemset/problem/1143/B

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef pair<ll, ll> pp;
typedef priority_queue<ll> maxpq;
typedef priority_queue<ll, vector<ll>, greater<ll>> minpq;
typedef priority_queue<pp> pairmaxpq;
typedef priority_queue<pp, vector<pp>, greater<pp>> pairminpq;

//find_by_order() returns iterator, so use * notation;   order_of_key()
typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> aset;
typedef tree<ll, null_type, greater<ll>, rb_tree_tag, tree_order_statistics_node_update> dset;
typedef tree<ll, null_type, less_equal<ll>, rb_tree_tag, tree_order_statistics_node_update> aqset;
typedef tree<ll, null_type, greater_equal<ll>, rb_tree_tag, tree_order_statistics_node_update> deqset;

void printGraph(vector<vector<ll>>& a, ll n){
    for(ll i=1; i<=n; i++) {
       cout<<i<<": ";
       for(ll j=0; j<a[i].size(); j++) cout<<a[i][j]<<" "; cout<<endl;
    }
}
void printArray(vector<ll>& a){
    ll n = a.size();
    for(ll i=0; i<n; i++) {
        cout<<a[i]<<" ";
    }
    cout<<endl;
}
const ll MOD = 1e9+7;
const ll INF = 1e18;

ll add(ll x, ll y)  { return (x%MOD + y%MOD)%MOD; }
ll sub(ll x, ll y)  { return (x%MOD - y%MOD + MOD)%MOD; }
ll mul(ll x, ll y)  { return (x%MOD * y%MOD)%MOD; }


// void solve(){
//     string s;
//     cin>>s;
//     ll n = s.length();
//     ll maxm = 1;
//     for(auto x: s){
//         maxm *= (x-'0');
//     }
//     for(ll i=0; i<n; i++){
//         ll cnt = 1;
//         if(i==0 && s[i]=='1'){
//             for(ll j=1; j<n; j++) cnt*=9;
//         }
//         else if(s[i]>'0'){
//             for(ll j=0; j<n; j++){
//                 if(j<i) cnt *= (s[j]-'0');
//                 else if(j==i) cnt *= (s[j]-'0')-1;
//                 else cnt *= 9;
//             }
//         }
//         maxm = max(maxm, cnt);
//     }

//     cout<<maxm<<endl;
// }

// Better way is instead of using strings, use number directly, here we are just making the last x digits 9, and then calculating the product
ll calc(ll r){
    ll sum = 1;
    while(r>0){
        sum*=(r%10);
        r/=10;
    }
    return sum;
}

void solve(){
    ll n;
    cin>>n;
    n++;
    ll p = 1;
    ll maxm = 0;
    while(n!=0){
        ll r = n*p - 1;
        n/=10; p*=10;
        maxm = max(maxm, calc(r));
    }
    cout<<maxm<<endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t = 1;
    // cin>>t;
    while(t--){
        solve();
    }

    return 0;
}