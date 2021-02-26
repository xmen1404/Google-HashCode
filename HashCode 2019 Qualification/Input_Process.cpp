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

int n = 0, m = 0, Total;
bool visit[N];
vector<image> himg, vimg;
pair<char, vector<string> > image_tmp[N];
map<string, int> mp;
set<string> st;
vector<int> tmp;
bool done[N];

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

bool cmp(const image x, const image y) { return SZ(x.tag) < SZ(y.tag); }
void prepare() {
	random_shuffle(vimg.begin(), vimg.end());
	while(SZ(vimg) >= 2) {
		// cerr << "done " << i << '\n';
		auto cur_img = vimg.back(); vimg.pop_back();
		int best = -1, minn = 0;
		FOR(i, 1, int(1e4)) {
			if(i > SZ(vimg)) break;
			int id = SZ(vimg) - i, same = same_count(cur_img, vimg[id]);
			if(best == -1 || minn > abs(SZ(cur_img.tag) + SZ(vimg[id].tag) - same - 20) * same) {
				best = id;
				minn = abs(SZ(cur_img.tag) + SZ(vimg[id].tag) - same - 30) * same;
			}
		}
		if(int(1e4) < SZ(vimg)) {
			FOR(test, 1, 10) {
				int id = Rand(0, int(SZ(vimg) - int(1e4)));
				int same = same_count(cur_img, vimg[id]);
				if(best == -1 || minn > abs(SZ(cur_img.tag) + SZ(vimg[id].tag) - same - 20) * same) {
					best = id;
					minn = abs(SZ(cur_img.tag) + SZ(vimg[id].tag) - same - 30) * same;
				}
			}
		}
		// we have the best
		// cerr << SZ(vimg[best].tag) << ' ' << SZ(cur_img.tag) << '\n';
		swap(vimg[best], vimg[SZ(vimg) - 1]);
		cur_img.pid = vimg.back().id;

		for(auto v: cur_img.tag) vimg.back().tag.pb(v);
		sort(vimg.back().tag.begin(), vimg.back().tag.end());
		cur_img.tag.clear();
		FOR(i, 0, SZ(vimg.back().tag) - 1) if(i == SZ(vimg.back().tag) - 1 || vimg.back().tag[i] != vimg.back().tag[i + 1])
			cur_img.tag.pb(vimg.back().tag[i]);
		vimg.pop_back();

		himg.pb(cur_img);
		n += 1;
	}
}

signed main()
{
 //    freopen("a_example.txt", "r", stdin);
    // freopen("b_lovely_landscapes.txt", "r", stdin);
	// freopen("c_memorable_moments.txt", "r", stdin);
	freopen("d_pet_pictures.txt", "r", stdin);
	// freopen("e_shiny_selfies.txt", "r", stdin);
	freopen("d_pet_pictures_input.txt", "w", stdout);


    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cerr << "Processing Input...";

    cin >> Total;
    FOR(i, 0, Total - 1) {
    	char c; int x;
    	cin >> c >> x;
    	image_tmp[i].fi = c;
    	FOR(j, 0, x - 1) {
    		string s; cin >> s;
    		image_tmp[i].se.pb(s);
    		st.insert(s);
    	}
    }

    int cnt = 0;
    for(auto it = st.begin(); it != st.end(); ++it) {
    	mp[(*it)] = ++cnt;
    }
    FOR(i, 0, Total - 1) {
    	image cur;
    	cur.id = i; cur.pid = -1;
    	for(auto v: image_tmp[i].se)
    		cur.tag.pb(mp[v]);
    	sort(cur.tag.begin(), cur.tag.end());
    	if(image_tmp[i].fi == 'H') {
    		n += 1;
    		himg.pb(cur);
    	} else {
    		m += 1;
    		vimg.pb(cur);
    	}
    }
    // cerr << m << '\n';
    cerr << "Done Input!\nProcessing Preapration...";

    prepare();
    cout << n << '\n';
    for(auto v: himg) {
    	if(v.pid == -1) {
    		cout << "0 " << v.id << ' ' << SZ(v.tag) << ' ';
    		for(auto x: v.tag) cout << x << ' ';
    		cout << '\n';
    	} else {
    		cout << "1 " << v.id << ' ' << v.pid << ' ' << SZ(v.tag) << ' ';
    		for(auto x: v.tag) cout << x << ' ';
    		cout << '\n';
    	}
    }

 	// cerr << "score = " << result << '\n';
    cerr << "Done!";
}