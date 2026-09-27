#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void printPrimeFactors(ll n){
    for(ll i = 2; i*i <= n; i++){ // as we divide n, breaking condition will keep collapsing

        while(n%i == 0){
            cout<<i<<" "; n/=i;
        }
    }

    if(n!=1) {
        cout<<n<<" "; // as discussed in the md file, one divisor could be remaining
    }
    cout<<endl;
}

void solve(){
    ll n; cin>>n;
    printPrimeFactors(n);
    cout<<(-5)/3<<endl;
    cout<<(-5)%3<<endl;
    cout<<5/(-3)<<endl;
    cout<<5%(-3)<<endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t = 1;
    while(t--){
        solve();
    }

    return 0;
}