#include "basic.h"
#include <omp.h>

int err;

int MINIMUM = 3;
int MAXIMUM = 1000;

double beta = 0.1;

int NumS = 47;
int NumF = 35;
int NumK = 2;

int MAXT = 1;

string filename = "./soybean_47_35_4";
string dataname = "soybean_algo";

int main() {
    for (NumK = 1; NumK <= 16; NumK *= 2) {
        for (MAXIMUM = 160; MAXIMUM <= 2000; MAXIMUM = MAXIMUM * 2) {
            // for (beta = 0; beta >= 0; beta -= 0.05) {
            {
                stringstream dircmove;
                dircmove << "mkdir " << dataname << "_" << 1 - beta << "_" << MAXIMUM << "_"
                         << NumK;

                stringstream compiler;
                compiler << "g++ main.cpp -o main.out --std=c++11 -O2 ";
                compiler << "-DMINIMUM=" << MINIMUM << " ";
                compiler << "-DMAXIMUM=" << MAXIMUM << " ";
                compiler << "-Dbeta=" << 1 - beta << " ";
                compiler << "-DNumS=" << NumS << " ";
                compiler << "-DNumF=" << NumF << " ";
                compiler << "-DNumK=" << NumK << " ";
                compiler << "-DALGO";

                string dircmove_str = dircmove.str();
                string compiler_str = compiler.str();

                // cout << dircmove_str << endl;
                cout << compiler_str << endl;

                // err = system(dircmove_str.c_str());
                err = system(compiler_str.c_str());
            }

            for (int T = 0; T < MAXT; T++) {
                err = system("mkdir DATANAME");

                unsigned int RANDOM_SEED = rand();

                stringstream c_runner;
                c_runner << "./main.out " << filename << "/source.txt "
                         << RANDOM_SEED << " >> log";

                stringstream filemove;
                filemove << "mv DATANAME " << dataname << "_" << 1 - beta << "_" << MAXIMUM << "_"
                         << NumK << "/" << T;

                string c_runner_str = c_runner.str();
                string filemove_str = filemove.str();

                cout << c_runner_str << endl;
                // cout << filemove_str << endl;

                err = system(c_runner_str.c_str());
                // err = system(filemove_str.c_str());

                err = system("rm DATANAME -rf");
            }

            // {
            //     stringstream dircmove;
            //     dircmove << "mv " << dataname << "_" << 1 - beta << "_" << MAXIMUM << "_" << NumK
            //              << " EXPRIDATA";

            //     string dircmove_str = dircmove.str();

            //     cout << dircmove_str << endl;

            //     err = system(dircmove_str.c_str());
            // }
        }
    }
}
