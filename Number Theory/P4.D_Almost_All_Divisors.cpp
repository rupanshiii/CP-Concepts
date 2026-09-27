// https://codeforces.com/problemset/problem/1165/D

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


void solve(){
    ll n;
    cin>>n;
    set<ll> st;
    for(ll i=0; i<n; i++) {
        ll x; cin>>x;
        st.insert(x);
    }
    vector<ll> v;
    for(auto x: st) v.push_back(x);
    ll ans = v[0]*v[v.size()-1];

    // this is approach 1 (my approach): here we are calculating the total number of divisors using Trial Division method and then checking if the number of divisors match and finally testing if all the numbers present in the set divides the ans, which is also a good approach
    // ll cnt = 1;
    // ll x = ans;
    // for(ll i=2; i*i<=x; i++){
    //     ll r = 0;
    //     while(x%i == 0){
    //         r++;
    //         x/=i;
    //     }
    //     cnt = cnt*(r+1);
    // }
    // if(x>1) cnt = cnt*2;
    // for(auto x: v){
    //     if(ans%x!=0) {cout<<-1<<endl; return;}
    // }
    // if(cnt-2 == st.size()) cout<<ans<<endl;
    // else cout<<"-1"<<endl;


    // But a better approach is just to find all the divisors, it is easier than you think in O(sqrt(n))
    vector<ll> div;
    for(ll i=2; i*i<=ans; i++){
        if(ans%i == 0){
            div.push_back(i);
            if(i!=(ans/i)) div.push_back(ans/i);
        }
    }
    sort(div.begin(), div.end());
    if(div.size()!=v.size()){cout<<-1<<endl; return;}
    for(ll i=0; i<div.size(); i++){
        if(div[i]!=v[i]){cout<<-1<<endl; return;}
    }
    cout<<ans<<endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t = 1;
    cin>>t;
    while(t--){
        solve();
    }

    return 0;
}