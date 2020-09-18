#include "tickets.h"
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

struct Edge {
  int u, v;
  int cap, flow;
  Edge() {}
  Edge(int u, int v, LL cap): u(u), v(v), cap(cap), flow(0) {}
};

struct Dinic {
  int N;
  vector<Edge> E;
  vector<vector<int>> g;
  vector<int> d, pt;

  Dinic(int N): N(N), E(0), g(N), d(N), pt(N) {}

  void AddEdge(int u, int v, LL cap) {
    if (u != v) {
      E.emplace_back(Edge(u, v, cap));
      g[u].emplace_back(E.size() - 1);
      E.emplace_back(Edge(v, u, 0));
      g[v].emplace_back(E.size() - 1);
    }
  }

  bool BFS(int S, int T) {
    queue<int> q({S});
    fill(d.begin(), d.end(), N + 1);
    d[S] = 0;
    while(!q.empty()) {
      int u = q.front(); q.pop();
      if (u == T) break;
      for (int k: g[u]) {
        Edge &e = E[k];
        if (e.flow < e.cap && d[e.v] > d[e.u] + 1) {
          d[e.v] = d[e.u] + 1;
          q.emplace(e.v);
        }
      }
    }
    return d[T] != N + 1;
  }

  LL DFS(int u, int T, LL flow = -1) {
    if (u == T || flow == 0) return flow;
    for (int &i = pt[u]; i < g[u].size(); ++i) {
      Edge &e = E[g[u][i]];
      Edge &oe = E[g[u][i]^1];
      if (d[e.v] == d[e.u] + 1) {
        LL amt = e.cap - e.flow;
        if (flow != -1 && amt > flow) amt = flow;
        if (LL pushed = DFS(e.v, T, amt)) {
          e.flow += pushed;
          oe.flow -= pushed;
          return pushed;
        }
      }
    }
    return 0;
  }

  LL MaxFlow(int S, int T) {
    LL total = 0;
    while (BFS(S, T)) {
      fill(pt.begin(), pt.end(), 0);
      while (LL flow = DFS(S, T))
        total += flow;
    }
    return total;
  }
};

pair<int,int> p[1505][1505]; // (position, company, index)
int sums[(int)3e6];
long long find_maximum(int k, std::vector<std::vector<int>> d) {
    int c = d.size();
    int s = d[0].size();
    vector<vector<int>> ret(c);
    for(int i=0; i<c; i++) {
        for(int j=0; j<s; j++) {
            ret[i].push_back(-1);
        }
    }
    long long ans = 0;
    Dinic din(k+c+2);
    int source = k+c;
    int sink = k+c+1;
    for(int i=0; i<k; i++) {
        din.AddEdge(source, i, c/2);
        for(int j=k; j<k+c; j++) {
            din.AddEdge(i, j, 1);
        }
    }
    vector<int> pl[c];
    vector<int> mi[c];

    for(int i=0; i<c; i++) {
        for(int j=0; j<s; j++) {
            p[i][j] = make_pair(d[i][j], j);
        }
        sort(p[i], p[i]+s);
        for(int j=0; j<k; j++) {
            sums[i*k+j] = p[i][j].first + p[i][s-k+j].first;
        }
    }
    sort(sums, sums+c*k);
    int median = sums[(c*k)/2];
    int extras = 0;
    for(int i=c*k/2-1; i>=0; i--) {
        if(sums[i]==median) extras++;
    }
    for(int i=0; i<c; i++) {
        for(int j=0; j<k; j++) {
            if(p[i][j].first+p[i][s-k+j].first<median) {
                mi[i].push_back(p[i][j].second);
            } else if(p[i][j].first+p[i][s-k+j].first==median && extras>0) {
                mi[i].push_back(p[i][j].second);
                extras--;
            } else if(p[i][j].first+p[i][s-k+j].first>=median) {
                pl[i].push_back(p[i][s-k+j].second);
            }
        }
        din.AddEdge(i+k, sink, pl[i].size());
    }
    din.MaxFlow(source, sink);
    for(Edge x: din.E) {
        if(x.u < k && x.v < k+c && x.v>=k) {
            int day = x.u;
            int company = x.v - k;
            if(x.flow == 1) {
                ret[company][pl[company].back()] = day;
                ans += d[company][pl[company].back()];
                pl[company].pop_back();
            } else {
                ret[company][mi[company].back()] = day;
                ans -= d[company][mi[company].back()];
                mi[company].pop_back();
            }
        }
    }
    allocate_tickets(ret);
    return ans;
}
