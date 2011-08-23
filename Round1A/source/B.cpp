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

vector<string> dict;

bool is_skip(int *live, char c)
{
	for (int i=0;i<dict.size();++i) {
		if (live[i]) {
			if (dict[i].find(c, 0) != string::npos) return false;
		}
	}
	return true;
}

int get_lose_point(int choice, char *list)
{
	size_t len = dict[choice].size();
	vector<int> live;
	live.reserve(dict.size());
	for (int i=0;i<dict.size();++i) {
		live.push_back(dict[i].size() == len);
	}
	
	int lose = 0;
	for (int n=0;n<26;++n) {
		char c = list[n];
		if (is_skip(&live[0], c)) continue;

		size_t start_pos = 0;
		size_t pos = dict[choice].find(c, start_pos);
		if (pos == string::npos) {
			lose++;
			// Except the word including letter c
			for (int i=0;i<dict.size();++i) {
				if (live[i] && i != choice) {
					if (dict[i].find(c, 0) != string::npos) live[i] = 0;
				}
			}
		} else {
			while (pos != string::npos) {
				for (int i=0;i<dict.size();++i) {
					if (live[i] && i != choice) {
						if (dict[i].find(c, start_pos) != pos) live[i] = 0;	
					}
				}
				start_pos = pos + 1;
				pos = dict[choice].find(c, start_pos);
			}
			for (int i=0;i<dict.size();++i) {
				if (live[i] && i != choice) {
					if (dict[i].find(c, start_pos) != string::npos) live[i] = 0;
				}
			}
		}
	}
	return lose;
}

int solve(char *list)
{
	if (dict.size() == 1) return 0;

	int max_lose = -1;
	int max_lose_index = 0;
	for (int i=0;i<dict.size();++i) {
		int lose = get_lose_point(i, list);
		if (max_lose < lose) {
			max_lose = lose;
			max_lose_index = i;
		}
	}
	return max_lose_index;
}

int main() {
	int T; scanf("%d", &T);
	for (int Ti = 1; Ti <= T; ++Ti) {
		//fprintf(stderr, "Case #%d of %d...\n", Ti, T);
		int N, M; scanf("%d %d", &N, &M);
		dict.clear();
		for(int i=0;i<N;++i) {
			char word[16];
			scanf("%s", word);
			dict.push_back(word);
		}
		printf("Case #%d:", Ti);
		for(int i=0;i<M;++i) {
			char list[32];
			scanf("%s", list);
			printf(" %s", dict[solve(list)].c_str());
		}
		printf("\n");
	}
	return 0;
}
