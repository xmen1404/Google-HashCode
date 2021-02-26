#include <bits/stdc++.h>

using namespace std;

#define ll  long long
#define ld  double

#define sz(x)   (int)x.size()
#define all(x)  x.begin(),x.end()

#define pb  emplace_back
#define X   first
#define Y   second

int n, m;
int Time;
int cars;

int bonus_point;
string name[100005];

vector<int> adj[100005];

int cost[100005];
int src[100005];
int dst[100005];

vector<int> paths[10005];

typedef pair<int,int>   Dat;

set<Dat>    green[100005];
vector<Dat> schedule[100005];

int last[100005];

vector<int> fr[100005];
vector<int> to[100005];

int val[100005];
int cnt[100005];

int main(int argc,char **argv)  {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string FileName = argv[1];

    freopen((FileName + ".txt").c_str(),"r",stdin);
    freopen((FileName + ".out").c_str(),"w",stdout);

    cin >> Time;
    cin >> n >> m;
    cin >> cars;
    cin >> bonus_point;

    map<string,int> index;

    for(int i = 0 ; i < m ; ++i)    {
        cin >> src[i];
        cin >> dst[i];

        fr[src[i]].pb(i);
        to[dst[i]].pb(i);

        cin >> name[i];
        cin >> cost[i];

        index[name[i]] = i;
    }
    for(int i = 0 ; i < cars ; ++i) {
        int c;  cin >> c;

        while (c--) {
            string Name;
            cin >> Name;

            paths[i].pb(index[Name]);
        }
        int Sum = 0;

        reverse(all(paths[i]));

        for(int j : paths[i])   {
            val[j] += Sum;
            cnt[j]++;
            Sum += cost[j];
        }
        cnt[paths[i][0]]--;
    }
    int count_intersection = 0;

    for(int i = 0 ; i < n ; ++i)    {
        sort(all(to[i]),[&](int a,int b)    {
            return  val[a] > val[b];
        });
        for(int j : to[i])  if (val[j])
            schedule[i].pb(j,cnt[j] / 50 + 1);
        
        if (schedule[i].size())
            count_intersection++;
    }

    /*for(int i = 0 ; i < n ; ++i)    if (green[i].size())    {
        int lst_time = -1;
        int lst_road = -1;

        for(Dat Through : green[i]) {
            int road     = Through.second;
            int duration = Through.first - lst_time;

            if (road != lst_road)   schedule[i].pb(road,0), lst_road = road;
            if (road == lst_road)   schedule[i].back().second += duration;

            lst_time += duration;
        }
        if (schedule[i].size()) {
            schedule[i].back().second += period - lst_time;
            count_intersection++;
        }
    }*/
    cout << count_intersection << "\n";

    for(int i = 0 ; i < n ; ++i)    if (schedule[i].size()) {
        //schedule.back().second += 200 - lst;

        cout << i << "\n";
        cout << sz(schedule[i]) << "\n";

        for(Dat Light : schedule[i])    {
            cout << name[Light.first] << " ";
            cout << Light.second << "\n";
        }
    }
}