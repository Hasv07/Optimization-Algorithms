#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
const ll n=5;
ll all_done=(1<<n)-1;
vector<vector<ll>> dist(n,vector<ll>(n,0));
vector<vector<ll>> dp(n,vector<ll>(pow(2,n),-1));

ll tsp(ll node,ll s)
{
    if(s==all_done)return dist[node][0];
    if(dp[node][s]!=-1)return dp[node][s];
    ll ans=1e18;
    for(ll city=0;city<n;city++)
    {
      if((s&(1<<city))==0)
        ans=min(ans,dist[node][city]+tsp(city,(s|(1<<city))));
    }
    dp[node][s]=ans;
    return dp[node][s];
}
int main() {

    for(ll i=0;i<n;i++)
    {
        for(ll j=0;j<n;j++)
        {
            ll cost;
            cin>>cost;
            dist[i][j]=cost;
        }
    }
    cout<<tsp(0,1);
}
