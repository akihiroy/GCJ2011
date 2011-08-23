#include "cmath"
#include "cstdio"
#include "algorithm"
#include "map"
#include "numeric"
#include "queue"
#include "set"
#include "string"
#include "utility"
#include "vector"
using namespace std;
typedef long long i64;

struct Walkway {
	int B;
	int E;
	int w;
	Walkway(int B_, int E_, int w_) : B(B_), E(E_), w(w_) {}
	bool operator<(const Walkway& rhs) const {
		return w < rhs.w;
	}
};
std::vector<Walkway> walkways;

int main() {
	int T; scanf("%d", &T);
	for (int Ti = 1; Ti <= T; ++Ti) {
		walkways.clear();

		fprintf(stderr, "Case #%d of %d...\n", Ti, T);
		int X, S, R, t, N;
		scanf("%d %d %d %d %d", &X, &S, &R, &t, &N);

		for (int i = 0; i < N; ++i) {
			int B, E, w;
			scanf("%d %d %d", &B, &E, &w);

			int last_E = walkways.empty() ? 0 : walkways.back().E;
			if (last_E < B) {
				// No walkway area
				walkways.push_back(Walkway(last_E, B, 0));
			}
			walkways.push_back(Walkway(B, E, w));
		}
		int last_E = walkways.empty() ? 0 : walkways.back().E;
		if (last_E < X) {
			walkways.push_back(Walkway(last_E, X, 0));
		}

		std::sort(walkways.begin(), walkways.end());

		double time = 0.0;
		double runnable = (double)t;
		for (std::vector<Walkway>::const_iterator it = walkways.begin(); it != walkways.end(); ++it) {
			double len = it->E - it->B;
			if (runnable * (R + it->w) < len) {
				// Run and Walk
				len -= runnable * (R + it->w); 
				time += runnable + len / (S + it->w);
				runnable = 0.0;
			} else {
				// Run
				double run_time = len / (R + it->w);
				time += run_time;
				runnable -= run_time;
			}
		}

		printf("Case #%d: %.08f\n", Ti, time);
	}
	return 0;
}
