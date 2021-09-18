#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
const ll n=5;
vector<vector<ll>> dist(n,vector<ll>(n,0));
vector<ll> make_group(ll l,ll r,vector<ll> cities)
{
    vector<ll> group;
    for (ll i = l; i < r ; ++i) {
        group.push_back(cities[i]);

    }
    return group;
};
ll connect(vector<ll>A,vector<ll>B)
{
    ll ans=0;
    bool vis[n]={0};
    ll min=1e18;
    vector<pair<ll,pair<ll,ll>>> pairs;

    for(auto&city1:A)
    {
        for(auto&city2:B)
        {
            ll cost=dist[city1][city2];
            if(dist[city1][city2]<min)
            {
                pairs.push_back({cost,{city1,city2}});
            }

        }
    }
    sort(pairs.begin(),pairs.end());
    ll c1,c2;
    ll cnt=0;
    for(auto&pair:pairs)
    {
        ll a=pair.second.first;
        ll b=pair.second.second;

        if(!vis[a]&&!vis[b])
        {
            cnt++;
            if(cnt==1) {
                c1 = b;
                ans += pair.first;
            } else
            {
                c2 = b;
                ans += pair.first;
                if(A.size()>2||B.size()>2)ans-=dist[c1][c2];
            }
            vis[a]=1,vis[b]=1;
        }
    }
    return ans;

}
ll connect3(vector<ll>A,vector<ll>B)
{
    return dist[A[0]][B[0]]+dist[A[0]][B[1]];
}

ll tsp(vector<ll> cities)
{
    ll ans=0;
    if(cities.size()>2)
    {
        vector<ll> groupA;
        vector<ll> groupB;
        groupA=make_group(0,cities.size()/2,cities);
        groupB=make_group((cities.size()/2),cities.size(),cities);
        ans+=tsp(groupA);
        ans+=tsp(groupB);
        if(groupA.size()==1)ans+=connect3(groupA,groupB);
        else ans+=connect(groupA,groupB);


    } else
    {
        if(cities.size()==2)return dist[cities[0]][cities[1]];
        else return 0;
    }
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
    vector<ll> cities;
    for (ll i = 0; i < n; ++i) {
        cities.push_back(i);
    }
    cout<<tsp(cities);
}

