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

struct image {
	int id, pid;
	vector<int> tag;
};

int n;
vector<image> himg;
vector<image> rem;
vector<image> final;

int Rand(int lef, int rig) {
	return (rand() * 812 + rand() * 129 + rand() * 3) % (rig - lef + 1) + lef;
}

int same_count(image x, image y) {
	int ptr = 0, same = 0;
	for(auto v: x.tag) {
		while(ptr < SZ(y.tag) && v >= y.tag[ptr]){
			same += (v == y.tag[ptr]);
			ptr += 1;
		}
	}
	return same;
}
int calc(image x, image y) {
	int same = same_count(x, y);
	return min(same, min(SZ(x.tag) - same, SZ(y.tag) - same));
}

int solve() {
	random_shuffle(himg.begin(), himg.end());
	int cnt = 0, max_score = 0, st = 0;

	FOR(i, 1, SZ(himg) - 1) if(SZ(himg[i].tag) > SZ(himg[st].tag)) {
		st = i;
	}
	swap(himg[SZ(himg) - 1], himg[st]);
	final.pb(himg.back());
	himg.pop_back();

	while(SZ(himg) > 0) {
		rem.pb(himg.back());
		himg.pop_back();
		cnt += 1;
		max_score += SZ(rem.back().tag);
	} 
	max_score /= 2;
	// cerr << SZ(rem) << ' ' << SZ(himg) << '\n'; 

	int result = 0;
	while(SZ(rem) > 0) {
		// cerr << SZ(rem) << ' ' << SZ(himg) << '\n';
		int best = -1, best_union = 0;
		FOR(i, 0, SZ(rem) - 1) {
			if(best == -1 || best_union < calc(final.back(), rem[i])) {
				best_union = calc(final.back(), rem[i]);
				best = i;
			} 
		}
		result += best_union;
		cerr << best_union << '\n';
		final.pb(rem[best]);
		swap(rem[best], rem[SZ(rem) - 1]);
		rem.pop_back();
		if(SZ(himg) > 0) {
			rem.pb(himg.back());
			himg.pop_back();
		}
		if(result > int(400000)) break;
	}
	return result;
}

signed main()
{
 //    freopen("a_example.txt", "r", stdin);
    freopen("b_lovely_landscapes_input.txt", "r", stdin);
	// freopen("c_memorable_moments.txt", "r", stdin);
	// freopen("d_pet_pictures.txt", "r", stdin);
	// freopen("e_shiny_selfies_input.txt", "r", stdin);


    // ios_base::sync_with_stdio(false);
    // cin.tie(0); cout.tie(0);

	scanf("%d", &n);
	FOR(i, 1, n) {
		int t; scanf("%d", &t);
		image cur; cur.pid = -1;
		if(t == 0) {
			int x;
			scanf("%d%d", &cur.id, &x);
			FOR(j, 1, x) {
				int y; scanf("%d", &y);
				cur.tag.pb(y);
			}
		} else {
			int x; scanf("%d%d%d", &cur.id, &cur.pid, &x);
			FOR(j, 1, x) {
				int y; scanf("%d", &y);
				cur.tag.pb(y);
			}
		}
		himg.pb(cur);
	}    
	cerr << "Done input!\nProcessing...";

	cerr << "Result = " << solve() << "...Done!";
}