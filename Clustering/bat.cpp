#include "basic.h"
#include <unistd.h>

int err;

int MAXT = 10;
int MAXR = 10;
int NumS = 569;
int NumF = 2;

string dataname = "";
string labename = "wdbc_label";

void Runner_Task(string dataname, int T, int RANDOM_SEED) {
    stringstream c_runner;
    c_runner << "./main.out ";
    c_runner << "EXPRIDATA/" << dataname << "/" << T << "/"
             << "pureRandom.txt ";
    c_runner << "EXPRI_LOG/" << dataname << "_" << T << "_"
             << "_log ";
    c_runner << "EXPRIDATA/" << labename << " ";
    c_runner << RANDOM_SEED << " ";

    string c_runner_str = c_runner.str();

    cout << c_runner_str << endl;

    err = system(c_runner_str.c_str());
}

int main() {
    err = system("rm log");

    ifstream fin("EXPRIDATA/wdbc_dir", ios::in);

    stringstream compiler;
    compiler << "g++ main.cpp -o main.out --std=c++11 -O2 ";
    compiler << "-DMAXT=" << MAXT << " ";
    compiler << "-DNumS=" << NumS << " ";
    compiler << "-DNumF=" << NumF << " ";

    string compiler_str = compiler.str();

    cout << compiler_str << endl;

    err = system(compiler_str.c_str());

    while (fin >> dataname) {
        thread *task[MAXR];

        for (int T = 0; T < MAXR; T++) {
            unsigned int RANDOM_SEED = rand();
            task[T] = new thread(Runner_Task, dataname, T, RANDOM_SEED);
        }

        for (int T = 0; T < MAXR; T++) {
            task[T]->join();
        }

        // {
        //     stringstream compiler;
        //     compiler << "g++ main.cpp -o main.out --std=c++11 -O2 ";
        //     compiler << "-DMAXT=" << MAXT << " ";
        //     compiler << "-DNumS=" << NumS << " ";
        //     compiler << "-DNumF=" << NumF << " ";

        //     stringstream c_runner;
        //     c_runner << "./main.out ";
        //     c_runner << "EXPRIDATA/" << dataname << "/"
        //              << T << "/" << "kRandom.txt ";
        //     c_runner << "EXPRIDATA/" << labename;

        //     string compiler_str = compiler.str();
        //     string c_runner_str = c_runner.str();

        //     cout << compiler_str << endl;
        //     cout << c_runner_str << endl;

        //     err = system(compiler_str.c_str());
        //     err = system(c_runner_str.c_str());
        // }
    }
}
