#include<bits/stdc++.h>
using namespace std;
 
#define fi first
#define se second
#define FOR(a, b, c) for(int a = b; a <= c; ++a)
#define FORW(a,b,c) for(int a = b; a >= c; --a)
#define pb push_back
// #define int long long
#define SZ(a) (int)(a.size())
 
const int MOD = 998244353;
const int oo = 2e9;
const int N = 1e3 + 100;
typedef pair<int, int> ii;
typedef pair<ii, int> iii;

struct data {
    int rid, lef, rig;
    data(int rid = 0, int lef = 0, int rig = 0) : rid(rid), lef(lef), rig(rig) {}
    bool operator < (const data &x) const {return rig - lef + 1 < x.rig - x.lef + 1;}
};

int row, col, unavail, pcnt, scnt;
ii server[N * N];
bool slot[N][N], visit[N * N];
vector<ii> row_cap[N];
vector<data> aslot;
vector<int> sv;
iii trace[N];

int check[N];

bool cmp(const int x, const int y) {
    return server[x].fi < server[y].fi;
}

int solve() {
    random_shuffle(aslot.begin(), aslot.end());
    memset(visit, false, sizeof visit);
    FOR(i, 1, row) row_cap[i].clear();

    for(auto cur: aslot) {
        int lef = cur.lef, rig = cur.rig;
        random_shuffle(sv.begin(), sv.end());
        FOR(i, 0, SZ(sv) - 1) if(server[sv[i]].fi <= rig - lef + 1 && visit[sv[i]] == false) {
            trace[sv[i]] = {{cur.rid, lef}, 0};
            visit[sv[i]] = true;
            row_cap[cur.rid].pb({server[sv[i]].se, sv[i]});
            lef = lef + server[sv[i]].fi;
        }
    }
    priority_queue<iii, vector<iii>, greater<iii> > pq; // take the minimum
    FOR(i, 1, pcnt) pq.push({{0, 0}, i});
    FOR(i, 1, row) {
        vector<iii> tmp;
        sort(row_cap[i].begin(), row_cap[i].end());
        FORW(j, SZ(row_cap[i]) - 1, 0) {
            if(pq.empty() == true) {
                for(auto v: tmp) pq.push(v);
                tmp.clear();
            }
            tmp.pb(pq.top()); pq.pop();
            trace[row_cap[i][j].se].se = tmp.back().se;

            int sum = tmp.back().fi.fi + tmp.back().fi.se + row_cap[i][j].fi;
            int maxn = max(row_cap[i][j].fi, tmp.back().fi.se);
            tmp.back().fi = {sum - maxn, maxn};
        }
        for(auto v: tmp) pq.push(v);
    }
    // cout << pq.top().fi.fi << '\n';    
    return pq.top().fi.fi;
}

signed main()
{
    srand(time(NULL));
    freopen("dc.in", "r", stdin);
    scanf("%d%d%d%d%d", &row, &col, &unavail, &pcnt, &scnt);

    memset(slot, 1, sizeof slot);
    FOR(i, 1, unavail) {
        int x, y; scanf("%d%d", &x, &y);
        slot[x][y] = false;
    }

    FOR(i, 1, scnt) {
        scanf("%d%d", &server[i].fi, &server[i].se); // size - capacity
    }
    FOR(i, 1, row) {
        int st = 0; while(st < col && slot[i][st + 1] == 0) st += 1;
        while(st < col) {
            int rig = st + 1;
            while(rig < col && slot[i][rig + 1] == 1) rig += 1;
            aslot.pb({i, st + 1, rig});
            st = rig + 1;
            while(st < col && slot[i][st + 1] == 0) st += 1;
        }
    }
    
    FOR(i, 1, scnt) sv.pb(i);
    sort(sv.begin(), sv.end(), cmp);

    int res = 0;
    FOR(i, 1, 1000) res = max(res, solve());
    cout << res;
}
