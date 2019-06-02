#ifndef __PARTATION_H__
#define __PARTATION_H__

#include "basic.h"
#include "mmath.h"
#include "nvector.h"

class Node {
  public:
    int depth;
    vector<int> data;
    Node *child[2];

    void DeleteChildren() {
		if (child[0])
			child[0]->DeleteChildren(), delete child[0];
		if (child[1])
			child[1]->DeleteChildren(), delete child[1];
    }

    int getDepth() {
        int maxDepth = depth;
		if (child[0])
			maxDepth = max(maxDepth, child[0]->getDepth());
		if (child[1])
			maxDepth = max(maxDepth, child[1]->getDepth());
        return maxDepth;
    }

    void Display() {
        cout << "(";
        for (int i : data) {
            cout << i << ",";
        }
        cout << ")" << endl;
    }
};

template <class T, int N, int K, int METHOD = 0> class Similarity {
  private:
    double correlation[N][N];

#ifdef ALGO
    double inner_product[K][N];
    T direction[K];
#endif

    T feature[N];
    Node *Root;

    void Partation(Node *curr) {
        if (curr->data.size() <= MINIMUM) {
            return;
        }

        int n = curr->data.size();

#ifndef ALGO
        T direction;
        direction.random();
#endif

        vector<double> product;
        double innerMax = -DBL_MAX, innerMin = DBL_MAX;

        for (int i : curr->data) {
#ifdef ALGO
            double inner = inner_product[curr->depth % K][i];
#else
            double inner = direction * feature[i];
#endif
            innerMax = max(innerMax, inner);
            innerMin = min(innerMin, inner);
            product.push_back(inner);
        }
        double split = RandomUniform(innerMin, innerMax);

        curr->child[0] = new Node();
        curr->child[0]->depth = curr->depth + 1;

        curr->child[1] = new Node();
        curr->child[1]->depth = curr->depth + 1;

        for (int i = 0; i < n; i++) {
            if (product[i] <= split) {
                curr->child[0]->data.push_back(curr->data[i]);
            } else {
                curr->child[1]->data.push_back(curr->data[i]);
            }
        }

        Partation(curr->child[0]);
        Partation(curr->child[1]);
    }

  public:
    Similarity() {
        memset(correlation, 0, sizeof correlation);
        Root = new Node();
    }

    void print() {
        ofstream fout;
        fout.open("DATANAME/speed_only.txt");

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                fout << correlation[i][j] << " ";
            }
            fout << endl;
        }
    }

    void SetFeature(T *feature) {
        T featureMax(1.0), featureMin(0.0);

        for (int i = 0; i < N; i++) {
            featureMax = T::max(featureMax, feature[i]);
            featureMin = T::min(featureMin, feature[i]);
        }

        for (int i = 0; i < N; i++) {
            this->feature[i] = (feature[i] - featureMin) / (featureMax - featureMin);
            Root->data.push_back(i);
        }
    }

#ifdef ALGO
    void OrthogonalDistance() {
        for (int k = 0; k < K; k++) {
            direction[k].random();
        }
    }
#endif

    void Partation() {
        double ave_depth = 0;

        for (int i = 0; i < MAXIMUM; i++) {
#ifdef ALGO
            OrthogonalDistance();

            for (int k = 0; k < K; k++) {
                for (int i = 0; i < N; i++) {
                    inner_product[k][i] = feature[i] * direction[k];
                }
            }
#endif
            Partation(Root);

            ave_depth += Root->getDepth();
            Root->DeleteChildren();
        }

        ave_depth /= MAXIMUM;
        cout << "average max depth: " << ave_depth << endl;
    }
};

#endif
