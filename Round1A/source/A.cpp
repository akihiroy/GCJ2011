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

bool test(i64 N, int Pd, int Pg)
{
	if (Pg == 0) {
		return Pd == 0;
	} else if (Pg == 100) {
		return Pd == 100;
	}

	for(i64 D=1;D<=N;++D) {
		i64 Wd = D * Pd;
		if (Wd % 100 != 0) continue;
		//Wd /= 100;
		return true;
	}
	return false;
}

int main() {
	int T; scanf("%d", &T);
	for (int Ti = 1; Ti <= T; ++Ti) {
		fprintf(stderr, "Case #%d of %d...\n", Ti, T);
		i64 N; int Pd, Pg; scanf("%lld %d %d", &N, &Pd, &Pg);
		if (test(N,Pd,Pg)) printf("Case #%d: Possible\n", Ti);
		else printf("Case #%d: Broken\n", Ti);
	}
	return 0;
}
