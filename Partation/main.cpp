#include "basic.h"
#include "mmath.h"
#include "nvector.h"
#include "partation.h"


typedef NVector<NumF> Feature;

Feature feature[NumS];
int label[NumS];

Similarity<Feature, NumS, NumK, 0> similar0;
// Similarity<Feature, NumS, NumK, 2> similar2;

int main(int argc, char **argv) {
    srand(atoi(argv[2]));

    ifstream fin(argv[1], ios::in);
	ofstream fout("DATANAME/force.txt", ios::out);

    for (int i = 0; i < NumS; i++) {
        double pix[NumF];
        for (int j = 0; j < NumF; j++) {
            fin >> pix[j];
        }
        feature[i] = Feature(pix);
    }

	for (int i = 0; i < NumS; i++) {
		for (int j = 0; j < NumS; j++) {
			fout << feature[i] * feature[j] << " ";
		}
		fout << endl;
	}

    cout << "pureRandom" << endl;
    similar0.SetFeature(feature);
    auto time0S = chrono::system_clock::now();
    similar0.Partation();
    auto time0E = chrono::system_clock::now();
    auto duration0 = chrono::duration_cast<chrono::nanoseconds>(time0E - time0S);
    cout << ((double)duration0.count()) * chrono::nanoseconds::period::num /
                chrono::nanoseconds::period::den
         << endl;
    similar0.print();

    // cout << "kRandom" << endl;
    // similar2.SetFeature(feature);
    // auto time2S = chrono::system_clock::now();
    // similar2.Partation();
    // auto time2E = chrono::system_clock::now();
    // auto duration2 = chrono::duration_cast<chrono::nanoseconds>(time2E - time2S);
    // cout << ((double)duration2.count()) * chrono::nanoseconds::period::num /
    //             chrono::nanoseconds::period::den
    //      << endl;
    // similar2.print();

    return 0;
}
