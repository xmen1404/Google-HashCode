//wkingforACM
#include<bits/stdc++.h>
using namespace std;
 
#define fi first
#define se second
#define FOR(a, b, c) for(int a = b; a <= c; ++a)
#define FORW(a,b,c) for(int a = b; a >= c; --a)
#define pb push_back
// #define int long long
#define SZ(a) (int)(a.size())
#define mtp make_tuple
 
const int MOD = 998244353;
const int oo = 2e9;
const int N = 1e5 + 100;
typedef pair<int, int> ii;

struct street {
	int st, en, cross_time;
	int cross_count, total_score;
	string name;
} road[N];

int duration, n, m, ccar, bonus;
int total_cross_time[N];
vector<int> car_road[N];
vector<ii> vi[N], vi_rev[N];
map<string, int> mp;
vector<pair<int, vector<pair<string, int> > > > trace;
vector<int> tmp;

int Rand(int lef, int rig) {
	return (rand() * rand() + rand() * rand()) % (rig - lef + 1) + lef;
}
bool cmp(const int x, const int y) { 
	return road[x].total_score * road[y].cross_count < road[y].total_score * road[x].cross_count;
}

int main(int argc,char **argv)
{
	// freopen("a.txt", "r", stdin);
    // freopen("b.txt", "r", stdin);
    // freopen("c.txt", "r", stdin);
    // freopen("d.txt", "r", stdin);
    // freopen("e.txt", "r", stdin);
    // freopen("f.txt", "r", stdin);
    // freopen("a_out.txt", "w", stdout);

    string FileName = argv[1];

    cerr << "RUNNING " << FileName << "...\n";

    freopen((FileName + ".txt").c_str(),"r",stdin);
    freopen((FileName + ".out").c_str(),"w",stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
	
	cin >> duration >> n >> m >> ccar >> bonus;
	FOR(i, 0, m - 1) {
		cin >> road[i].st >> road[i].en >> road[i].name >> road[i].cross_time;
		vi[road[i].st].pb({road[i].en, i});
		vi_rev[road[i].en].pb({road[i].st, i});
		mp[road[i].name] = i;
		road[i].cross_count = road[i].total_score = 0;
	}

	FOR(i, 0, ccar - 1) {
		int x; cin >> x;
		vector<int> cur_tmp;
		FOR(j, 1, x) {
			string s; cin >> s;
			int id = mp[s];
			cur_tmp.pb(id);
			car_road[i].pb(id);
			if(j > 1) total_cross_time[i] += road[id].cross_time + 1;
			else total_cross_time[i] += 1;
			road[id].cross_count += 1;
		}
		// for(auto v: cur_tmp) if(total_cross_time[i] <= duration) {
		// 	road[v].cross_count += 1;
		// }
	}

	FOR(i, 0, n - 1) if(SZ(vi_rev[i]) > 0) {
		tmp.clear();
		for(auto v: vi_rev[i]) if(road[v.se].cross_count > 0) 
			tmp.pb(v.se);
		if(SZ(tmp) == 0) continue;
		// cerr << SZ(tmp) << '\n';
		sort(tmp.begin(), tmp.end(), cmp);

		int sum = 0;
		for(auto v: tmp) sum += road[v].cross_count;
		sum /= SZ(tmp); if(!sum) sum += 1;

		pair<int, vector<pair<string, int> > > cur;
		cur.fi = i;
		FOR(i, 0, SZ(tmp) - 1) {
			auto v = tmp[i];
			cur.se.pb({road[v].name, 1});
		}
		trace.pb(cur);
	}
	cout << SZ(trace) << '\n';
	for(auto v: trace) {
		cout << v.fi << '\n' << SZ(v.se) << '\n';
		for(auto u: (v.se)) 
			cout << u.fi << ' ' << u.se << '\n';
	}
	cerr << "...Done!";
}
// g++ -std=c++11 main.cpp -o OUT && OUT + FileName nhớ