#include <bits/stdc++.h>
using namespace std;
#define loop(i, len) for (long long i = 0; i < len; ++i)
#define loopr(i, len) for (long long i = len; i >=0; --i)
typedef  long long ll;
const ll n=5;
double upper_bound1=1e18;
ll all_done=(1<<n)-1;
ll id_cnt=0;
struct node
{
    ll id;
    double lower_bound;
    ll city;
    ll mask;

    node(ll id,double lower_bound,ll city, ll mask)
    {
        this->id=id;
        this->city=city;
        this->lower_bound=lower_bound;
        this ->mask=mask;
    };
};
vector<node> leafs;
vector<vector<ll>> dist(n,vector<ll>(n,0));
vector<ll> node_costs;
pair<double,double> arr[n];
ll calculate_initial_lowerbound()
{
    double ans=0;
    loop(i,n){
        node_costs.clear();
        loop(j,n) {
            if (i != j) {
                node_costs.push_back(dist[i][j]);
            }
        }
        sort(node_costs.begin(),node_costs.end());
        if(i!=0)arr[i]={node_costs[0],node_costs[1]};
        else arr[i]={node_costs[1],node_costs[0]};
        ans=ans+(node_costs[0]+node_costs[1])/2.0;
    }
    return ans;
}
void kill_node(ll idx)
{
    vector<node>::iterator it;
    it=leafs.begin();
    for(auto &leaf:leafs)
    {
        if(leaf.id==idx)leafs.erase(it);
        it++;

    }
}
void update_upperbound(double val)
{
    upper_bound1=val;
    for(auto&leaf:leafs)
    {
        if(leaf.lower_bound>=upper_bound1)kill_node(leaf.id);
    }
}
void tsp(node x)
{
    vector<node> children;
    kill_node(x.id);

    if(x.mask==all_done)
    {
        double value=x.lower_bound-((arr[x.city].second+arr[0].first)/2.0)+(double)dist[x.city][0];
        if(value<upper_bound1)update_upperbound(value);
        return;
    }
    for(ll city=0;city<n;city++) {
        if ((x.mask & (1 << city)) == 0) {
            double l_b=x.lower_bound-((arr[x.city].second+arr[city].first)/2.0)+(double)dist[x.city][city];
            node new_node(id_cnt,l_b,city,(x.mask|(1<<city)));
            id_cnt++;
            leafs.push_back(new_node);
            children.push_back(new_node);
        }
    }

    sort(children.begin(),children.end(),[](node x, node y){return x.lower_bound<=y.lower_bound;});
    tsp(children[0]);

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
    node initial(0,calculate_initial_lowerbound(),0,1);
    id_cnt++;
    leafs.push_back(initial);
     while (!leafs.empty())
     {
         tsp(leafs[0]);
     }
     cout<<ceil(upper_bound1);

}
