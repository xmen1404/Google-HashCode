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
const int oo = 1e7;
const int N = 2e3 + 100;
typedef pair<int, int> ii;

struct data {
	int x, y, sum;
	int item[N];
} house[N], order[N];

struct package {
	int order_id, item_id, item_num, dist;
	package(int order_id = 0, int item_id = 0, int item_num = 0, int dist = 0) : order_id(order_id), item_id(item_id), item_num(item_num), dist(dist) {}
};

int R, C, cdrone, maxTime, maxLoad, cType, corder, chouse;
int witem[N];
vector<ii> ditem[20][N]; // house - order => item_id - number
vector< package > hpackage[20]; // list of package for each delivery stored at the houses
ii drone[N];

struct Mincost {
    int n, source, sink;
    struct edge {
        int flow, cap, cost, v, rev;
    };
    vector< vector<edge> > vi;
    vector< ii > pr;
    vector<int> dist;
    vector<bool> inqueue;


    Mincost(int n = 0, int source = 0, int sink = 0) : n(n), source(source), sink(sink) {
        vi.assign(n + 2, vector<edge>() );
        pr.assign(n + 2, ii(0, 0));
        dist.assign(n + 2, 0);
        inqueue.assign(n + 2, 0);
    }
    void addeg(int u, int v, int cap, int cost) {
        edge A = {0, cap, cost, v, SZ(vi[v])};
        edge B = {0, 0, -cost, u, SZ(vi[u])};
        vi[u].pb(A); vi[v].pb(B);
    }

    bool find() {
        FOR(i, 0, n) dist[i] = oo, inqueue[i] = 0;
        dist[source] = 0;
        queue<int> pq; pq.push(source); inqueue[source] = 1;

        while(!pq.empty()) {
            int u = pq.front(); pq.pop();
            inqueue[u] = false;

            FOR(i, 0, SZ(vi[u]) - 1) {
                auto v = vi[u][i];
                if(dist[v.v] > dist[u] + v.cost && v.cap > v.flow) {
                    dist[v.v] = dist[u] + v.cost;
                    pr[v.v] = {u, i};
                    if(!inqueue[v.v]) {
                        inqueue[v.v] = 1; pq.push(v.v);
                    }
                }
            }
        }
        return dist[sink] < oo;
    }

    void trace() {
        int flow = oo, cur = sink;
        while(cur != source) {
            int u = pr[cur].fi, id = pr[cur].se;
            flow = min(flow, vi[u][id].cap - vi[u][id].flow);
            cur = u;
        }
        cur = sink;
        while(cur != source) {
            int u = pr[cur].fi, id = pr[cur].se;
            vi[u][id].flow += flow;
            vi[ vi[u][id].v ][ vi[u][id].rev ].flow -= flow;
            cur = u;
        }
    }

    int solve(int id) {
        while(find())  { trace();}
        FOR(i, 1, chouse) for(auto v: vi[i]) if(v.v > chouse && v.cost >= 0 && v.cap > 0){
        	ditem[chouse][v.v - chouse].pb({id, v.cap});
        }

        int res = 0;
        for(auto v: vi[0]) if(v.flow > 0) {
            res += v.flow;
        }
        return res;
    }

} mc;

int dist(int x, int y, int x1, int y1) {
	return int(ceil( sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1)) ));
}

void prepare_mc(int id) {
	int sum = 0; 
	FOR(i, 1, chouse) if(house[i].item[id] > 0)  {
		mc.addeg(0, i, house[i].item[id], 0);
		// sum += house[i].item[id];
	}
	FOR(i, 1, corder) if(order[i].item[id] > 0)  {
		mc.addeg(i + chouse, mc.sink, order[i].item[id], 0);
		// sum += order[i].item[id];
	}
	FOR(h, 1, chouse) FOR(o, 1, corder) {
		mc.addeg(h, h + o, oo, dist(house[h].x, house[h].y, order[o].x, order[o].y));
	}
}

int solve()

signed main()
{
    freopen("busy_day.in", "r", stdin);
    // freopen("mother_of_all_warehouses.in", "r", stdin);
    // freopen("redundancy.in", "r", stdin);
    // input
    scanf("%d%d%d%d%d", &R, &C, &cdrone, &maxTime, &maxLoad);
    scanf("%d", &cType);
    FOR(i, 1, cType) scanf("%d", &witem[i]);

    scanf("%d", &chouse);
    FOR(i, 1, chouse) {
    	FOR(j, 0, cType) house[i].item[j] = 0;
    	scanf("%d%d", &house[i].x, &house[i].y);
    	FOR(j, 1, cType) scanf("%d", &house[i].item[j]);
    }

    int sum = 0;
    scanf("%d", &corder);
    FOR(i, 1, corder) {
    	FOR(j, 0, cType) order[i].item[j] = 0;
    	scanf("%d%d", &order[i].x, &order[i].y);
    	int x; scanf("%d", &x); // number of ordered items
    	sum += x;
    	while(x--) {
    		int y; scanf("%d", &y); // type of the item
    		order[i].item[y + 1] ++;
    	}
    	order[i].sum = 0;
    	FOR(j, 1, cType) order[i].sum += order[i].item[j];
    }
    // use mincost maxflow to calculate the
    cerr << cType << '\n'; 
    FOR(i, 1, cType) {
    	int sum = 0;
    	FOR(j, 1, corder) sum += order[j].item[i];
    	cerr << i << " total = " << sum << "...";

    	int source = 0, sink = chouse + corder + 1;
    	int n = chouse + corder + 2;
    	mc = Mincost(n, source, sink); 
    	prepare_mc(i);
    	cerr << mc.solve(i) - sum << " ... done\n";
    	// we have info about which amount of item of each type if delivered from where to where directly
    	// oke now we try to join the order
    }

    FOR(h, 1, chouse) {
		vector<ii> tmp;
		FOR(o, 1, corder) tmp.pb({dist(house[h].x, house[h].y, order[o].x, order[o].y) * order[o].sum, o});
		sort(tmp.begin(), tmp.end());
		
		// start putting items into each delivery
		vector<iii> cur_item;
		for(auto u: tmp) { // order id
			for(auto v: ditem[h][u.se]) { // id item - number
				cur_item.pb({u.se, v});
			}
		}

		int ptr = 0, load = 0;
		while(ptr < SZ(cur_item)) { // order_id, item_id, item_num, dist;
			auto x = cur_item[ptr];
			package cur_pk = package(x.fi, x.se.fi, x.se.se, dist(house[h].x, house[h].y, order[x.fi].x, order[x.fi].y));
			cur_item[ptr].se.se = 0;
			while(load + witem[cur_pk.item_id] * cur_pk.item_num > maxLoad) {
				cur_pk.item_num -= 1;
				cur_item[ptr].se.se += 1;
			}

			if(cur_item[ptr].se.se == 0) ptr += 1;
			else {
				load = 0;
				if(cur_pk.item_num > 0) {
					hpackage[h].pb(cur_pk);
				}
			}
		}
	}
	FOR(i, 1, chouse) reverse(hpackage[i].begin(), hpackage[i].end());
	// we done with assigning items into packages for each delivery
	// time to make the delivery

	cout << solve();
}