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

int N;
char m[100][100];
double WP[100];
double OWP[100];
double OOWP[100];

double calcWP(char *row,int op=-1)
{
	int w=0,l=0;
	for (int i=0;i<N;++i) {
		if(i==op) continue;
		if(row[i]=='1') w++;
		else if(row[i]=='0')l++;
	}
	return (double)w/(w+l);
}

int main() {
	int T; scanf("%d", &T);
	for (int Ti = 1; Ti <= T; ++Ti) {
		fprintf(stderr, "Case #%d of %d...\n", Ti, T);
		scanf("%d", &N);
		for (int i=0;i<N;++i) {
			scanf("%s",m[i]);
			WP[i] = calcWP(m[i]);
		}
		for (int i=0;i<N;++i) {
			double a=0.0;
			int count =0;
			for (int j=0;j<N;++j) {
				if(m[i][j] != '.') {
					a += calcWP(m[j], i);
					count++;
				}
			}
			OWP[i]=a/count;
		}

		printf("Case #%d:\n", Ti);

		for (int i=0;i<N;++i) {
			double a=0.0;
			int count=0;
			for (int j=0;j<N;++j) {
				if(m[i][j]!='.') {
					a+=OWP[j];
					count++;
				}
			}
			OOWP[i]=a/count;
			
			double RPI=0.25*WP[i]+0.50*OWP[i]+0.25*OOWP[i];
			printf("%.12g\n", RPI);
		}

	}
	return 0;
}
