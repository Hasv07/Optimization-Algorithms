#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
const ll n=5;
const ll t_max=10000;
const ll t_min=1;
vector<vector<ll>> dist(n,vector<ll>(n,0));
string path;
double Fitness_calc(string path)
{
    ll ans=0;
    for (ll i = 0; i <path.size() ; i++) {
        if(i==n-1)ans+=dist[path[i]-'0'][0];
        else if(i!=n)ans+=dist[path[i]-'0'][path[i+1]-'0'];
    }
    return -1*ans;
}
string next(string path)
{
    ll x=0,y=0;
    while(x==y) {
        x = 1 + (rand() * 2) % (n - 1);
        y = 1 + rand() % (n - 1);
    }
    swap(path[x],path[y]);
    return path;
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

    for (ll i = 0; i < n; ++i) {
    path+=to_string(i);
    }
    path+='0';
    string next_path;
    double En,Ec,delta_E,d;
    for (double t = t_max; t>=t_min ; t--) {
        Ec=Fitness_calc(path);
        next_path=next(path);
        En=Fitness_calc(next_path);
        delta_E=En-Ec;
        d=exp(delta_E/t*1.0);
        double r = ((double) rand() / (RAND_MAX));
        if(delta_E>0)path=next_path;
        else if(d>r)path=next_path;

    }
    cout<<-1*Fitness_calc(path);
}
