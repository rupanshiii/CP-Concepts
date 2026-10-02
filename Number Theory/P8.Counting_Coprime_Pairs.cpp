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

///////////////////////////////////
///////////////////////////////////
// YET TO BE SOLVED!!!!!!!!!!!!!!!!
// YET TO BE SOLVED!!!!!!!!!!!!!!!!
// YET TO BE SOLVED!!!!!!!!!!!!!!!!
// YET TO BE SOLVED!!!!!!!!!!!!!!!!
///////////////////////////////////
///////////////////////////////////

void solve(){
    ll n; cin>>n;
    vector<ll> a(n);
    ll maxm = 0;
    for(ll i=0; i<n; i++) {cin>>a[i]; maxm = max(maxm, a[i]);}
    vector<ll> spf(maxm+1, -1);
    spf[1] = spf[0] = 0;
    for(ll i=2; i*i<=maxm; i++){
        if(spf[i] == -1){
            spf[i] = i;
            for(ll j = i*i; j<=maxm; j+=i){
                if(spf[j] == -1) spf[j] = i;
            }
        }
    }
    for(ll i=2; i<=maxm; i++) if(spf[i] == -1) spf[i] = i;
    map<ll, ll> mp;
    for(ll i=0; i<n; i++){
        set<ll> st;
        while(a[i]>1 && (a[i]%spf[a[i]] == 0)) {
            st.insert(spf[a[i]]);
            a[i] /= spf[a[i]];
        }
        for(auto x: st) mp[x]++;
    }
    ll ans = (n*(n-1))/2;
    for(auto [x, y]: mp) ans -= (y*(y-1))/2 ;
    cout<<ans<<endl;
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