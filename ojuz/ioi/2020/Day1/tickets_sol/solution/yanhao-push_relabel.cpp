#include "tickets.h"
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

struct Edge {
  int from, to, cap, flow, index;
  Edge(int from, int to, int cap, int flow, int index) :
    from(from), to(to), cap(cap), flow(flow), index(index) {}
};

struct PushRelabel {
  int N;
  vector<vector<Edge> > G;
  vector<LL> excess;
  vector<int> dist, active, count;
  queue<int> Q;

  PushRelabel(int N) : N(N), G(N), excess(N), dist(N), active(N), count(2*N) {}

  void AddEdge(int from, int to, int cap) {
    G[from].push_back(Edge(from, to, cap, 0, G[to].size()));
    if (from == to) G[from].back().index++;
    G[to].push_back(Edge(to, from, 0, 0, G[from].size() - 1));
  }

  void Enqueue(int v) {
    if (!active[v] && excess[v] > 0) { active[v] = true; Q.push(v); }
  }

  void Push(Edge &e) {
    int amt = int(min(excess[e.from], LL(e.cap - e.flow)));
    if (dist[e.from] <= dist[e.to] || amt == 0) return;
    e.flow += amt;
    G[e.to][e.index].flow -= amt;
    excess[e.to] += amt;
    excess[e.from] -= amt;
    Enqueue(e.to);
  }

  void Gap(int k) {
    for (int v = 0; v < N; v++) {
      if (dist[v] < k) continue;
      count[dist[v]]--;
      dist[v] = max(dist[v], N+1);
      count[dist[v]]++;
      Enqueue(v);
    }
  }

  void Relabel(int v) {
    count[dist[v]]--;
    dist[v] = 2*N;
    for (int i = 0; i < G[v].size(); i++)
      if (G[v][i].cap - G[v][i].flow > 0)
	dist[v] = min(dist[v], dist[G[v][i].to] + 1);
    count[dist[v]]++;
    Enqueue(v);
  }

  void Discharge(int v) {
    for (int i = 0; excess[v] > 0 && i < G[v].size(); i++) Push(G[v][i]);
    if (excess[v] > 0) {
      if (count[dist[v]] == 1)
	Gap(dist[v]);
      else
	Relabel(v);
    }
  }

  LL GetMaxFlow(int s, int t) {
    count[0] = N-1;
    count[N] = 1;
    dist[s] = N;
    active[s] = active[t] = true;
    for (int i = 0; i < G[s].size(); i++) {
      excess[s] += G[s][i].cap;
      Push(G[s][i]);
    }

    while (!Q.empty()) {
      int v = Q.front();
      Q.pop();
      active[v] = false;
      Discharge(v);
    }

    LL totflow = 0;
    for (int i = 0; i < G[s].size(); i++) totflow += G[s][i].flow;
    return totflow;
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
    PushRelabel din(k+c+2);
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
    din.GetMaxFlow(source, sink);

    /*for(Edge x: din.E) {
        if(x.from < k && x.to < k+c && x.v>=k) {
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
    }*/
    for(int i=0; i<din.N; i++) {
        for(Edge x: din.G[i]) {
            if(x.from < k && x.to < k+c && x.to>=k) {
                int day = x.from;
                int company = x.to - k;
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
    }
    allocate_tickets(ret);
    return ans;
}
