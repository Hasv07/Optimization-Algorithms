#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
const ll n=4;
bool vis[n];
vector<vector<ll>> dist(n,vector<ll>(n,0));
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
ll min,node=0,idx;
ll ans=0;
    vis[0]=1;
    for (ll i = 0; i < n ; ++i) {
        min=1e18;
        for (ll city = 0; city < n; ++city) {
            if((dist[node][city]<min)&&(!vis[city]))min=dist[node][city],idx=city;
        }
        if(i!=n-1) {
            ans += dist[node][idx];
            node = idx, vis[idx] = 1;
        } else{
            ans+=dist[node][0];
        }
    }
    cout<<ans;
}
