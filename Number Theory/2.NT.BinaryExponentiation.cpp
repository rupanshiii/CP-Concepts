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

ll exp(ll a, ll b){
    if(b == 0) return 1; // base condition
    ll x = exp(a, b/2); // x = a^(b/2)
    if(b%2 == 0) return x*x;
    else return x*x*a;
}

void solve(){
    ll a, b;
    cin>>a>>b;
    cout<<exp(a, b)<<endl;
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