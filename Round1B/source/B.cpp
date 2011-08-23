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

struct Word {
	int index;
	int group_next[26];
};

vector<string> dict_string;
vector<Word> dict[10];
vector<int> letter_counts[10];

vector<int> live;


int get_lose_point(const vector<Word>& d, int *letter_count, int choice, char *list, int max_lose)
{
	live.assign(d.size(), 0);
	live[choice] = -1;
	size_t live_actual_size = live.size();
	int cur_live = 0;

	int lose = 0;
	for (int n=0;n<26;++n) {
		// Abort if impossible to get over max_lose
		if (lose + (26 - n) < max_lose) {
			return lose;
		}

		int c = list[n] - 'a';
		if (letter_count[c] == 0) continue;

		int next = d[choice].group_next[c];
		if (next == -1) {
			// Except the word including letter c
			bool skip = true;
			size_t s = live_actual_size;
			for (int i=0;i<s;++i) {
				if (live[i] == cur_live) {
					if (d[i].group_next[c] != -1) {
						// Kill this word
						skip = false;
						letter_count[c]--;
					} else {
						live[i]++;
					}
					live_actual_size = i + 1;
				}
			}

			if (!skip) lose++;
		} else {
			while (next != choice) {
				live[next]++;
				next = d[next].group_next[c];
			}
		}
		cur_live++;
	}
	return lose;
}

int solve(char *list)
{
	if (dict_string.size() == 1) return 0;

	int max_lose = -1;
	int max_lose_index = 0;
	for (int j=0;j<10;++j) {
		for (int i=0;i<dict[j].size();++i) {
			int local_letter_count[26];
			for (int k=0;k<26;++k) {
				local_letter_count[k] = letter_counts[j][k];
			}
			int lose = get_lose_point(dict[j], local_letter_count, i, list, max_lose);
			if (max_lose < lose || (max_lose == lose && max_lose_index > dict[j][i].index)) {
				max_lose = lose;
				max_lose_index = dict[j][i].index;
			}
		}
	}
	return max_lose_index;
}

void prepare()
{
	for(int j=0;j<10;++j) {
		letter_counts[j].assign(26, 0);
		for(int n=0;n<26;++n) {
			map< unsigned int, vector<int> > m;
			for (size_t i=0;i<dict[j].size();++i) {
				// make character bit flag
				const string& str = dict_string[dict[j][i].index];
				unsigned int flag = 0;
				size_t pos = -1;
				while ((pos = str.find('a'+n, pos+1)) != string::npos) {
					flag |= 1 << pos;
				}
				if (flag) {
					m[flag].push_back(i);
					letter_counts[j][n]++;
				}
			}

			for (map< unsigned int, vector<int> >::iterator it = m.begin(); it != m.end(); ++it) {
				const vector<int>& v = it->second;
				for(size_t i=0;i<v.size();++i) {
					dict[j][v[i]].group_next[n] = v[(i+1)%v.size()];
				}
			}
		}
	}
}

int main() {
	Word new_word;
	for (int i=0;i<26;++i) {
		new_word.group_next[i] = -1;
	}
	int T; scanf("%d", &T);
	for (int Ti = 1; Ti <= T; ++Ti) {
		//fprintf(stderr, "Case #%d of %d...\n", Ti, T);
		int N, M; scanf("%d %d", &N, &M);
		dict_string.clear();
		dict_string.reserve(N);
		for(int i=0;i<10;++i) {
			dict[i].clear();
		}
		for(int i=0;i<N;++i) {
			char word[16];
			scanf("%s", word);
			dict_string.push_back(word);
			new_word.index = dict_string.size() - 1;
			dict[dict_string.back().size()-1].push_back(new_word);
		}
		prepare();
		printf("Case #%d:", Ti);
		for(int i=0;i<M;++i) {
			char list[32];
			scanf("%s", list);
			printf(" %s", dict_string[solve(list)].c_str());
		}
		printf("\n");
	}
	return 0;
}
