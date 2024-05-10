#include <bits/stdc++.h>
#include <windows.h>

#define ll long long
#define ull unsigned long long
#define ld long double
#define print_lst_1x(lst) for (auto el: lst){cout << el << ' ';} cout << endl;
#define print_lst_2x(lst) for (auto el: lst){for (auto zn: el) {cout << zn << ' ';} cout << '\n';} cout << endl;
using namespace std;


struct edge {
    int a, b, cap, flow;
};


bool bfs(int s, int t, vector<vector<int>> &graf, vector<edge> &edges, vector<int> &q, vector<int> &d) {
    int qh = 0, qt = 0;
    q[qt++] = s;
    for (int i = 0; i < d.size(); i++) {
        d[i] = -1;
    }
    d[s] = 0;
    while (qh < qt && d[t] == -1) {
        int v = q[qh++];
        for (size_t i = 0; i < graf[v].size(); ++i) {
            int id = graf[v][i],
                    to = edges[id].b;
            if (d[to] == -1 && edges[id].flow < edges[id].cap) {
                q[qt++] = to;
                d[to] = d[v] + 1;
            }
        }
    }
    return d[t] != -1;
}


int dfs(int v, int fn, int flow, vector<vector<int>> &graf, vector<edge> &edges, vector<int> &ptr, vector<int> &d) {
    if (!flow) return 0;
    if (v == fn) return flow;
    for (; ptr[v] < (int) graf[v].size(); ++ptr[v]) {
        int id = graf[v][ptr[v]],
                to = edges[id].b;
        if (d[to] != d[v] + 1) continue;
        int pushed = dfs(to, fn, min(flow, edges[id].cap - edges[id].flow), graf, edges, ptr, d);
        if (pushed) {
            edges[id].flow += pushed;
            edges[id ^ 1].flow -= pushed;
            return pushed;
        }
    }
    return 0;
}


int dinic(int s, int t, vector<vector<int>> &graf, vector<edge> &edges) {
    int flow = 0;

    vector<int> d(graf.size()), q(graf.size());

    while (bfs(s, t, graf, edges, q, d)) {
        vector<int> ptr(graf.size(), 0);
        while (int pushed = dfs(s, t, INT_MAX, graf, edges, ptr, d))
            flow += pushed;
    }
    return flow;
}


void add_edge(int st, int fn, int cap, vector<vector<int>> &graf, vector<edge> &edges) {
    edge e1 = {st, fn, cap, 0};
    edge e2 = {fn, st, 0, 0};
    graf[st].push_back((int) edges.size());
    edges.push_back(e1);
    graf[fn].push_back((int) edges.size());
    edges.push_back(e2);
}


int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graf(n, vector<int>(n, 0));
    vector<edge> edges;
    int st, fn, cap;
    for (int i = 0; i < m; i++) {
        cin >> st >> fn >> cap;
        add_edge(st, fn, cap, graf, edges);
    }

    cout << dinic(0, 5, graf, edges) << endl;
}


/**
Примеры входных данных (графы):

6 8
0 1 11
0 2 12
1 3 12
2 1 1
2 4 11
3 5 19
4 3 7
4 5 4

6 10
0 1 16
0 2 13
1 2 10
1 3 12
2 1 4
2 4 14
3 2 9
3 5 20
4 3 7
4 5 4

6 10
0 1 3
0 2 7
1 3 9
1 4 9
2 1 9
2 4 9
2 5 4
3 5 3
4 5 7
0 4 10


 */
