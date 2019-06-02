#include "dbscan.h"
#include "kmeans.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <math.h>
#include <set>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <vector>

using namespace std;

#include "ACC.cpp"

int method = 0;
unsigned int min_pts = 4;
double radius = 73;

int standard_group[NumS];
double Correlation[NumS][NumS];
int temp_w[NumS][NumF];

void do_kmeans() {
	Kmeans_clustering<NumF, NumS> k;

    k.set_Correlation(Correlation);
    k.cluster();

    for (int i = 0; i < NumS; i++) {
        int from = k.result[i];
        int to = standard_group[i];

        if (from != -1) {
            temp_w[from][to]++;
        }
    }
}

void do_dbscan() {
	DBSCAN_clustering<NumF, NumS> d;

    d.set_Correlation(Correlation);
    d.set_parameter(radius, min_pts);
    d.cluster();

    cout << "non clustered points =" << d.non_clustered << endl;

    for (int i = 0; i < NumS; i++) {
        int from = d.result[i];
        int to = standard_group[i];

        if (from != -1) {
            temp_w[from][to]++;
        }
    }
}

int main(int argc, char **argv) {
    ifstream fin;
    fin.open(argv[1]);

	ofstream fout;
	fout.open(argv[2]);

	unsigned int RANDOM_SEED = atoi(argv[4]);

    for (int i = 0; i < NumS; i++) {
        for (int j = 0; j < NumS; j++) {
            fin >> Correlation[i][j];
        }
    }

    ifstream findata;
    findata.open(argv[3]);
    for (int i = 0; i < NumS; i++) {
        findata >> standard_group[i];
    }

	cout << argv[1] << "	" << argv[2] << "	" << RANDOM_SEED << endl;

	srand(RANDOM_SEED);

	double ave = 0;
	double var = 0;
	for (int T = 0; T < MAXT; T++) {
		memset(temp_w, 0, sizeof temp_w);

		switch (method) {
		case 0:
			do_kmeans();
			break;
		case 1:
			do_dbscan();
			break;
		}

		// for (int i = 0; i < NumF; i++) {
		// 	for (int j = 0; j < NumF; j++) {
		// 		cout << temp_w[i][j] << " ";
		// 	}
		// 	cout << endl;
		// }

		double acc = ACC::ACC(temp_w);

		ave = ave + acc;
		var = var + acc * acc;
	}

	ave = ave / MAXT;
	var = var / MAXT;
	var = var - ave * ave;

	cout << "ave: " << ave << endl;
	// cout << "var: " << var << endl;
	fout << "ave: " << ave << endl;
	// fout << "var: " << var << endl;

    return 0;
}
