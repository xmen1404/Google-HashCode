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

struct library {
	int signup_time, ship_limit, book_num;
	vector<int> book; 
} lib[N];

int cbook, clib, cday;
int book_score[N];
bool visit[N];
vector<int> rem_lib;

bool cmp(const int x, const int y) { 
	return book_score[x] > book_score[y];
}
int solve() {
	int result = 0;
	int cur_time = 0, rem_size = clib;
	FOR(i, 0, clib - 1) rem_lib.pb(i);
	while(cur_time < cday && rem_size > 0) {
		int best = -1;
		double best_score = 0.0;
		int best_rem_slot = 0;
		FOR(i, 0, rem_size - 1) {
			int id = rem_lib[i];
			if(cur_time + lib[id].signup_time > cday) continue;

			int tmp = SZ(lib[id].book);
			FOR(j, 0, tmp - 1) { // we erase the used book
				if(j >= SZ(lib[id].book)) { break; }
				if(visit[lib[id].book[j]] == 1) {
					swap(lib[id].book[j], lib[id].book[ SZ(lib[id].book) - 1]);
					if(j < SZ(lib[id].book) - 1) j -= 1;
					lib[id].book.pop_back();
				}
			}
			sort(lib[id].book.begin(), lib[id].book.end(), cmp);

			int rem_slot = (cday - (cur_time + lib[id].signup_time)) * lib[id].ship_limit;
			double cur_sum = 0;
			FOR(j, 0, min(rem_slot - 1, SZ(lib[id].book) - 1)) {
				cur_sum += 1.00 * (book_score[lib[id].book[j]]);
			}
			if(best == -1 || best_score < cur_sum / (1.00 * lib[id].signup_time)){
				best = i;
				best_score = cur_sum / (1.00 * lib[id].signup_time);
				best_rem_slot = rem_slot;
			} 
			// else if(abs(rem_slot - cur_sum / (1.00 * lib[id].signup_time)) <= 50.0 && rem_slot > best_rem_slot) {
			// 	best = i;
			// 	best_score = cur_sum / (1.00 * lib[id].signup_time);
			// 	best_rem_slot = rem_slot;
			// } 
		}
		if(best == -1) break;

		int id = rem_lib[best];
		int rem_slot = (cday - (cur_time + lib[id].signup_time)) * lib[id].ship_limit;
		// cerr << best_score << ' ' << id << ' ' << SZ(lib[id].book) << '\n';
		FOR(j, 0, min(rem_slot - 1, SZ(lib[id].book) - 1)) {
			// cerr << id << ' ' << lib[id].book[j] << ' ' << book_score[lib[id].book[j]] << ' ' << visit[lib[id].book[j]] << '\n';
			result += book_score[lib[id].book[j]];
			// cerr << lib[id].book[j] << ' ' << book_score[lib[id].book[j]] << ' ' << visit[lib[id].book[j]] << '\n';
			visit[lib[id].book[j]] = 1;
		}
		swap(rem_lib[best], rem_lib[SZ(rem_lib) - 1]);
		rem_lib.pop_back();
		rem_size -= 1;

		cur_time += lib[id].signup_time;
		// cerr << cur_time << ' ' << lib[id].signup_time << '\n';
	}
	return result;
}

signed main()
{
	freopen("a_example.txt", "r", stdin);
    // freopen("b_read_on.txt", "r", stdin);
    // freopen("c_incunabula.txt", "r", stdin);
    // freopen("d_tough_choices.txt", "r", stdin);
    // freopen("e_so_many_books.txt", "r", stdin);
    // freopen("f_libraries_of_the_world.txt", "r", stdin);
    // ios_base::sync_with_stdio(false);
    // cin.tie(0); cout.tie(0);
	
	cerr << "Processing Input...";
	scanf("%d%d%d", &cbook, &clib, &cday);
	FOR(i, 0, cbook - 1) {
		scanf("%d", &book_score[i]);
	}
	return cerr << max_score, 0;
	FOR(i, 0, clib - 1) {
		scanf("%d%d%d", &lib[i].book_num, &lib[i].signup_time, &lib[i].ship_limit);
		FOR(j, 1, lib[i].book_num) {
			int x; scanf("%d", &x);
			lib[i].book.pb(x);
		}
	}
	cerr << "Done!\nProcessing Algorithm...";

	int res = solve();

	cerr << "Done!\nResult = " << res;
}
// g++ -std=c++11 Main.cpp -o Main.exe && Main.exe