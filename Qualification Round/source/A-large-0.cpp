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
#include "deque"
using namespace std;
typedef long long i64;

struct Button {
  int seq;
  int pos;
  Button(int s, int p) : seq(s), pos(p) {}
};


int main() {
  int T; scanf("%d", &T);
  for (int Ti = 1; Ti <= T; ++Ti) {
    fprintf(stderr, "Case #%d of %d...\n", Ti, T);
    int N; scanf("%d", &N);
    deque<Button> orange, blue;
    for (int i=0;i<N;++i) {
      char R[2];
      int P;
      scanf("%s %d", R, &P);
      if (R[0] == 'O') {
        orange.push_back(Button(i, P));
      } else {
        blue.push_back(Button(i, P));
      }
    }

    int seq = 0, time = 0;
    int o_pos = 1, b_pos = 1;
    while (!orange.empty() || !blue.empty()) {
      bool pushed = false;
      if (!orange.empty()) {
        if (orange.front().pos < o_pos) o_pos--;
	else if (orange.front().pos > o_pos) o_pos++;
	else if (orange.front().seq == seq) {
          orange.pop_front();
	  seq++;
	  pushed = true;
	  fprintf(stderr, "OPush %d", o_pos);
	}
      }
      if (!blue.empty()) {
        if (blue.front().pos < b_pos) b_pos--;
	else if (blue.front().pos > b_pos) b_pos++;
	else if (!pushed && blue.front().seq == seq) {
          blue.pop_front();
	  seq++;
	  pushed = true;
	  fprintf(stderr, "BPush %d", b_pos);
	}
      }
      time++;
      fprintf(stderr, " Time %d\n", time);
    }

    printf("Case #%d: %d\n", Ti, time);
  }
  return 0;
}
