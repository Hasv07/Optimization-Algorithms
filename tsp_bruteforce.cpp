#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
const int n=4;
ll all_done=(1<<n)-1;
vector<vector<ll>> dist(n,vector<ll>(n,0));
bool vis[n];
ll solve(ll node,ll lvl)
{
    vis[node]=1;
    if (lvl==n){vis[node]=0;return dist[node][0];}
    ll ans=1e18;
    for(ll city=0;city<n;city++)
    {
        if(!vis[city])ans=min(ans,dist[node][city]+solve(city,lvl+1));
    }
    vis[node]=0;
    return ans;
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
    cout<<solve(0,1);
}