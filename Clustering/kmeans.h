#ifndef __KMEANS_H__
#define __KMEANS_H__

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <cstring>
#include <deque>
#include <fstream>
#include <iostream>
#include <vector>

#define random(x) (rand() % x)

using namespace std;

template <int catagory, int N> class Kmeans_clustering {
  private:
    double center[catagory][N];
    double now_center[catagory][N];
    double Correlation[N][N];
    set<int> previous_group[catagory];
    set<int> now_group[catagory];

  public:
	Kmeans_clustering() {
		memset(center, 0, sizeof center);
		memset(now_center, 0, sizeof now_center);
		memset(Correlation, 0, sizeof Correlation);

		for (int i = 0; i < catagory; i++) {
			previous_group[i].clear();
			now_group[i].clear();
		}
	}
    int result[N];

    void set_Correlation(const double C[N][N]) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                Correlation[i][j] = C[i][j];
            }
        }
    }

    void cluster() {
        for (int i = 0; i < catagory; i++) {
            double sum = 0;
            for (int j = 0; j < N; j++) {
                int tmp = random(100);
                center[i][j] = tmp;
                sum += tmp;
            }
            for (int j = 0; j < N; j++) {
                center[i][j] /= sum;
            }
        }

        for (int i = 0; i < N; i++) {
            int g = find_nearest(i);
            now_group[g].insert(i);
        }

        while (!equal()) {
            for (int i = 0; i < catagory; i++) {
                previous_group[i] = now_group[i];
            }

            for (int i = 0; i < catagory; i++) {
                now_group[i].clear();
            }

            for (int i = 0; i < catagory; i++) {
                calculate_center(i);
            }

            for (int i = 0; i < N; i++) {
                int g = find_nearest(i);
                now_group[g].insert(i);
            }
        }

        for (int i = 0; i < catagory; i++) {
            for (set<int>::iterator it = now_group[i].begin();
                 it != now_group[i].end(); it++) {
                result[*it] = i;
            }
        }
        return;
    }

    void calculate_center(int g) {
        double s = previous_group[g].size();
        memset(center[g], 0, sizeof(center[g]));
        for (set<int>::iterator it = previous_group[g].begin();
             it != previous_group[g].end(); it++) {
            center[g][*it] = 1 / s;
        }
    }

    int find_nearest(int point) {
        double distance[catagory];
        for (int i = 0; i < catagory; i++) {
            distance[i] = calculate_distance(point, i);
        }
        double minimum = DBL_MAX;
        for (int i = 0; i < catagory; i++) {
            if (distance[i] < minimum) {
                minimum = distance[i];
            }
        }
        for (int i = 0; i < catagory; i++) {
            if (minimum == distance[i]) {
                return i;
            }
        }
        return -1;
    }

    double cattel_product(int a, int b) { return Correlation[a][b]; }

    double calculate_distance(int pt, int kernel) {
        double result = cattel_product(pt, pt);
        for (int i = 0; i < N; i++) {
            result -= 2 * center[kernel][i] * cattel_product(pt, i);
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                result += center[kernel][i] * center[kernel][j] *
                          cattel_product(i, j);
            }
        }
        return result;
    }

    bool equal() {
        for (int i = 0; i < catagory; i++) {
            if (previous_group[i].size() != now_group[i].size()) {
                return false;
            }
            for (set<int>::iterator it1 = previous_group[i].begin(),
                                    it2 = now_group[i].begin();
                 it1 != previous_group[i].end(), it2 != now_group[i].end();
                 it1++, it2++) {
                if (*it1 != *it2) {
                    return false;
                }
            }
        }
        return true;
    }
};

#endif
