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

vector<string> combines;
vector<string> opposed;

int ToID(char e)
{
  switch (e) {
  case 'Q': return 0;
  case 'W': return 1;
  case 'E': return 2;
  case 'R': return 3;
  case 'A': return 4;
  case 'S': return 5;
  case 'D': return 6;
  case 'F': return 7;
  default: throw;
  }
}

char Combine(char e1, char e2)
{
  for (vector<string>::const_iterator it = combines.begin(); it != combines.end(); ++it) {
    const string& s = *it;
    if ((s[0] == e1 && s[1] == e2) || (s[0] == e2 && s[1] == e1)) return s[2];
  }
  return 0;
}

bool Oppose(int *base_elements)
{
  for (vector<string>::const_iterator it = opposed.begin(); it != opposed.end(); ++it) {
    const string& s = *it;
    if (s[0] == s[1]) {
      if (base_elements[ToID(s[0])] >= 2) return true;
    } else {
      if (base_elements[ToID(s[0])] >= 1 && base_elements[ToID(s[1])] >= 1) return true;
    }
  }
  return false;
}

int main() {
  int T; scanf("%d", &T);
  for (int Ti = 1; Ti <= T; ++Ti) {
    fprintf(stderr, "Case #%d of %d...\n", Ti, T);

    int C;
    scanf("%d", &C);
    combines.clear();
    for (int i=0;i<C;++i) {
      char str[4];
      scanf("%s", str);
      combines.push_back(str);
    }

    int D;
    scanf("%d", &D);
    opposed.clear();
    for (int i=0;i<D;++i) {
      char str[4];
      scanf("%s", str);
      opposed.push_back(str);
    }

    int N;
    scanf("%d", &N);
    char invokes[101];
    scanf("%s", invokes);

    vector<char> elements;
    int base_elements[8]={0,0,0,0,0,0,0,0}; 
    for (int i=0;i<N;++i) {
      if (elements.empty()) {
        elements.push_back(invokes[i]);
	base_elements[ToID(invokes[i])]=1;
	continue;
      }
      char c = Combine(elements.back(), invokes[i]);
      if (c) {
        base_elements[ToID(elements.back())]--;
        elements.back() = c;
      } else {
        elements.push_back(invokes[i]);
	base_elements[ToID(invokes[i])]++;
	if (Oppose(base_elements)) {
          elements.clear();
	  memset(base_elements, 0, sizeof(int)*8);
	}
      }
    }

    printf("Case #%d: [", Ti);
    for (size_t i=0;i< elements.size();++i) {
      if (i==0) printf("%c", elements[i]);
      else printf(", %c", elements[i]);
    }
    printf("]\n");
  }
  return 0;
}
