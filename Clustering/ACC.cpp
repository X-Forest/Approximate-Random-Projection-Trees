#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>

using namespace std;

namespace ACC {
const int inf = 0x3c3c3c3c;

int w[NumF][NumF], vis[2 * NumF + 2], dis[2 * NumF + 2], head[2 * NumF + 2];

struct edge {
    int v, a, w, next;
} e[2 * NumF * NumF + 4 * NumF];

int s = 2 * NumF, t = 2 * NumF + 1, cnt, ans;

void insert(int u, int v, int a, int w) {
    e[cnt] = (edge){v, a, w, head[u]};
    head[u] = cnt++;
    e[cnt] = (edge){u, 0, -w, head[v]};
    head[v] = cnt++;
}

int spfa() {
    for (int i = 0; i < 2 * NumF + 2; i++) {
        dis[i] = -inf;
        vis[i] = 0;
    }

    queue<int> q;

    q.push(t);
    dis[t] = 0;
    vis[t] = 1;

    while (!q.empty()) {
        int u = q.front();

        q.pop();
        vis[u] = 0;

        for (int i = head[u]; i != -1; i = e[i].next) {
            int v = e[i].v;

            if (e[i ^ 1].a != 0 && dis[v] < dis[u] - e[i].w) {
                dis[v] = dis[u] - e[i].w;
                if (!vis[v]) {
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
    }

    return dis[s] > -inf;
}

int dfs(int u, int a) {
    if (u == t) {
        return a;
    }
    vis[u] = 1;

    int flow = 0;

    for (int i = head[u]; a != 0 && i != -1; i = e[i].next) {
        int v = e[i].v;

        if (!vis[v] && e[i].a != 0 && dis[u] == dis[v] + e[i].w) {
            int f = dfs(v, min(a, e[i].a));

            e[i].a -= f;
            e[i ^ 1].a += f;
            a -= f;
            flow += f;

            ans += f * e[i].w;
        }
    }

    return flow;
}

void mcmf() {
    while (spfa()) {
        vis[t] = 1;
        while (vis[t]) {
            memset(vis, 0, sizeof vis);
            dfs(s, inf);
        }
    }
}

double ACC(int w[NumF][NumF]) {
    for (int i = 0; i < 2 * NumF + 2; i++) {
        head[i] = -1;
    }
	cnt = 0;
	ans = 0;

    for (int i = 0; i < NumF; i++) {
        for (int j = 0; j < NumF; j++) {
            insert(i, NumF + j, 1, w[i][j]);
        }
    }

    for (int i = 0; i < NumF; i++) {
        insert(s, i, 1, 0);
        insert(NumF + i, t, 1, 0);
    }

    mcmf();

    return 1.0 * ans / NumS;
}
} // namespace ACC
