#ifndef __DBSCAN_H__
#define __DBSCAN_H__

#include <algorithm>
#include <cmath>
#include <cstring>
#include <deque>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

template <int catagory, int N> class DBSCAN_clustering {
  private:
    double Correlation[N][N];
    bool is_visited[N];
    bool is_kernel[N];
    int group_num = 0;
    double radius;
    unsigned int min_pts;

  public:
	DBSCAN_clustering() {
		memset(Correlation, 0, sizeof Correlation);
		memset(is_visited, 0, sizeof is_visited);
		memset(is_kernel, 0, sizeof is_kernel);
	}

    int non_clustered = 0;
    int result[N];
    void set_Correlation(const double C[N][N]) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                Correlation[i][j] = C[i][j];
            }
        }
    }

    int get_groupnum() { return group_num; }

    void set_parameter(const double a, const unsigned int b) {
        radius = a;
        min_pts = b;
    }

    double distance(int i, int j) {
        double d = sqrt(1 - Correlation[i][j]) * 100;
        return d;
    }

    void cluster() {
        deque<int> kernel_element;
        vector<int> surrounding[N];

		// for (int i = 0; i < N; i++) {
		// 	cout << Correlation[0][i] << ", " << distance(0, i) << endl;
		// }
		// cout << endl;

        for (int i = 0; i < N; i++) {
            result[i] = -1;
			is_visited[i] = 0;

            for (int j = 0; j < N; j++) {
                if (distance(i, j) <= radius) {
                    surrounding[i].push_back(j);
                }
            }

            if (surrounding[i].size() >= min_pts) {
                kernel_element.push_back(i);
                is_kernel[i] = true;
            }
        }

        while (!kernel_element.empty()) {
            int head_elem = kernel_element.front();
            is_visited[head_elem] = true;
            result[head_elem] = group_num;

            deque<int> deq;
            deq.push_back(head_elem);

            while (!deq.empty()) {
                int head = deq.front();

                deq.pop_front();
                is_visited[head] = true;
                for (vector<int>::iterator it = surrounding[head].begin();
                     it != surrounding[head].end(); it++) {
                    if (!is_visited[*it]) {
                        result[*it] = group_num;
                        is_visited[*it] = true;
                        if (is_kernel[*it]) {
                            deq.push_back(*it);
                        }
                    }
                }
            }

            while ((!kernel_element.empty()) &&
                   is_visited[kernel_element.front()]) {
                kernel_element.pop_front();
            }

            group_num++;
        }

        for (int i = 0; i < N; i++) {
            if ((!is_visited[i])) {
                non_clustered++;
            }
        }
    }
};

#endif
