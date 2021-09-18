#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
const ll n=4;
const ll number_of_generation=10000;
const ll size=n;
vector<vector<ll>> dist(n,vector<ll>(n,0));
struct seq
{
    ll fitness_value=0;

    ll id;
    string val="";
};
seq current_population[size];
seq new_generation[size];
void clear()
{
    for (int i = size/2; i <size ; ++i) {
        new_generation[i].val="";
    }
}
void create_offspring(ll p1,ll p2,ll id)
{
    bool used[n];
    memset(used,0,sizeof(used));
    for (int i = 0; i <n+1 ; ++i) {

        char r1=current_population[p1].val[i];
        char r2=current_population[p2].val[i];
        if((!used[r1- '0']&&!used[r2- '0'])||(r1=='0')) {
            if (r1 != r2) {
                char l1 = current_population[p1].val[i - 1];
                char l2 = current_population[p2].val[i - 1];
                if (dist[l1 - '0'][r1 - '0'] < dist[l2 - '0'][r2 - '0'])new_generation[id].val += r1;
                else new_generation[id].val += r2;
            } else new_generation[id].val += r1;
        }
        else
        {
            for (ll j = 0; j <n ; ++j) {
                if(!used[j]){new_generation[id].val += to_string(j);break;}
            }
        }
        used[new_generation[id].val[i]-'0']=1;
    }
    ll x=0,y=0;
    while(x==y) {
        x = 1 + (rand() * 2) % (n - 1);
        y = 1 + rand() % (n - 1);
    }
    swap(new_generation[id].val[x],new_generation[id].val[y]);
}

void Fitness_calc(seq& s)
{
    s.fitness_value=0;
    for (ll i = 0; i <s.val.size() ; i++) {
        if(i==n-1)s.fitness_value+=dist[s.val[i]-'0'][0];
        else if(i!=n)s.fitness_value+=dist[s.val[i]-'0'][s.val[i+1]-'0'];
    }
}
void survival()
{

    sort(current_population,current_population+size,[](seq x,seq y){return x.fitness_value<=y.fitness_value;});
    for (ll i = 0; i <size/2 ; ++i) {
        new_generation[i]=current_population[i];
    }
}
void create_new_generation() {
    for(ll i=0;i<size/2;i++)
    {
        create_offspring(i,i+1,(size/2)+i);
    }

    for(ll i=0;i<size;i++)
    {
        current_population[i]=new_generation[i];
    }
    for (ll i = 0; i <size ; ++i) {
        Fitness_calc(current_population[i]);
    }
}
int main()
{
    for(ll i=0;i<n;i++)
    {
        for(ll j=0;j<n;j++)
        {
            ll cost;
            cin>>cost;
            dist[i][j]=cost;
        }
    }
    for (ll i = 0; i<size ; ++i) {
        for (ll j = 0; j <n ; ++j) {
            current_population[i].id=i;
            if(i==0)current_population[i].val+=to_string(j);
            else if(j==0)  current_population[i].val=current_population[i-1].val;
            else if(j!=0&&j!=n-1)swap(current_population[i].val[j],current_population[i].val[j+1]);
        }
        if(!i) current_population[0].val+='0';
    }
    for (ll i = 0; i < size ; ++i) {
        Fitness_calc(current_population[i]);
    }
    for (ll i = 0; i < number_of_generation; ++i) {

        survival();
        clear();
        create_new_generation();


    }


    sort(current_population,current_population+size,[](seq x,seq y){return x.fitness_value<=y.fitness_value;});
    cout<<current_population[0].fitness_value;




}
