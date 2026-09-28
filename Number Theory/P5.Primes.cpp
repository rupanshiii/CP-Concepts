// Check if at least k prime numbers from 2 to n inclusively can be expressed as the sum of three integer numbers: two neighboring prime numbers and 1. 
//For example, 19 = 7 + 11 + 1, or 13 = 5 + 7 + 1. Two prime numbers are called neighboring if there are no other prime numbers between them.
// Input: The first line of the input contains two integers n (2 ≤ n ≤1000) and k (0 ≤k≤1000).
// Output: Output "YES" or "NO".

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
const ll N = 1000;

ll add(ll x, ll y)  { return (x%MOD + y%MOD)%MOD; }
ll sub(ll x, ll y)  { return (x%MOD - y%MOD + MOD)%MOD; }
ll mul(ll x, ll y)  { return (x%MOD * y%MOD)%MOD; }

// Total time complexity - O(NloglogN)+O(t*logn)

void solve(vector<ll>& sum, vector<ll>& np){
    ll n, k;
    cin>>n>>k;
    // O(logn) - now we are finding the index of the biggest prime sum <= n, np[p] will give the number of prime sums upto there
    ll p = upper_bound(sum.begin(), sum.end(), n) - sum.begin() - 1;
    if(np[p]>=k) cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<ll> seive(2*N+5, 1);
    seive[0] = seive[1] = 0;
    vector<ll> prime;

    // O(Nlog(logN))
    for(ll i=2; i*i<=2*N; i++){
        if(seive[i]){
            for(ll j=i*i; j<=2*N; j+=i) seive[j] = 0;
        }
    }

    // O(N) - we are finding all the prime numbers upto N
    for(ll i=2; i<=N; i++){
        if(seive[i]) prime.push_back(i);
    }
    ll sz = prime.size();
    vector<ll> sum(sz);

    // O(N) - Then we are calculating the sum of adjacent primes+1
    for(ll i=1; i<sz; i++){
        sum[i] = prime[i] + prime[i-1] + 1;
    }
    vector<ll> np(sz, 0);

    // O(N) - Then we are taking the prefix sum, basically we are calculating how many sums till ith index are prime
    for(ll i=1; i<sz; i++){
        np[i] = np[i-1] + seive[sum[i]];
    }
    ll t = 1;
    while(t--){
        solve(sum, np);
    }

    return 0;
}