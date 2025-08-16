// Trying out GPT-5 (low reasoning) in Windsurf. Following https://info.atcoder.jp/entry/ahc-llm-rules-en Version 20250616

#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <string>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <random>

using namespace std;

struct Point { long long x, y; };

struct SorterSpec {
    bool installed = false;
    int k = -1; // sorter type index [0..K-1]
    int v1 = -1; // destination id [0..N+M-1]
    int v2 = -1; // destination id [0..N+M-1]
};

struct Solution {
    vector<int> d;      // size N, processor type at each processor location [0..N-1]
    int s = 0;          // inlet destination [0..N+M-1]
    vector<SorterSpec> sorters; // size M
};

struct Problem {
    int N=0, M=0, K=0;
    vector<Point> procPos;   // size N
    vector<Point> sortPos;   // size M
    vector<vector<double>> p; // K x N, p[k][type]

    // Node indexing: 0..N-1 processors, N..N+M-1 sorters, src = N+M
    int inletId() const { return N + M; }
    int nodes() const { return N + M + 1; }

    static int sign(long long x){ return (x>0) - (x<0); }
    static int orientation(const Point& a, const Point& b, const Point& c){
        long long cross = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
        return sign(cross);
    }
    static bool segmentsIntersect(const Point& p1, const Point& p2, const Point& q1, const Point& q2){
        if (max(p1.x, p2.x) < min(q1.x, q2.x) ||
            max(q1.x, q2.x) < min(p1.x, p2.x) ||
            max(p1.y, p2.y) < min(q1.y, q2.y) ||
            max(q1.y, q2.y) < min(p1.y, p2.y)) return false;
        int o1 = orientation(p1,p2,q1);
        int o2 = orientation(p1,p2,q2);
        int o3 = orientation(q1,q2,p1);
        int o4 = orientation(q1,q2,p2);
        return (o1 * o2 <= 0) && (o3 * o4 <= 0);
    }

    Point nodePoint(int v) const {
        if (0 <= v && v < N) return procPos[v];
        if (N <= v && v < N+M) return sortPos[v - N];
        // inlet
        return Point{0,5000};
    }

    // Build edges based on solution
    void buildEdges(const Solution& sol, vector<pair<int,int>>& edges) const {
        edges.clear();
        edges.emplace_back(inletId(), sol.s);
        for(int i=0;i<M;i++) if(sol.sorters[i].installed){
            edges.emplace_back(N+i, sol.sorters[i].v1);
            edges.emplace_back(N+i, sol.sorters[i].v2);
        }
    }

    bool validateSolution(const Solution& sol, string& reason) const {
        // Check sizes
        if((int)sol.d.size()!=N){ reason = "d size mismatch"; return false; }
        if((int)sol.sorters.size()!=M){ reason = "sorters size mismatch"; return false; }
        // Check d range 0..N-1
        for(int i=0;i<N;i++) if(sol.d[i]<0 || sol.d[i]>=N){ reason = "d[i] out of range"; return false; }
        // Check inlet destination
        if(sol.s < 0 || sol.s >= N+M){ reason = "inlet destination out of range"; return false; }

        // Check sorter specs
        for(int i=0;i<M;i++){
            const auto& sp = sol.sorters[i];
            if(!sp.installed) continue;
            if(sp.k < 0 || sp.k >= K){ reason = "sorter type out of range"; return false; }
            if(sp.v1 < 0 || sp.v1 >= N+M || sp.v2 < 0 || sp.v2 >= N+M){ reason = "sorter destination out of range"; return false; }
        }
        // Any dest that is sorter must be installed
        auto isSorter = [&](int v){ return (N <= v && v < N+M); };
        if(isSorter(sol.s) && !sol.sorters[sol.s - N].installed){ reason = "inlet points to uninstalled sorter"; return false; }
        for(int i=0;i<M;i++) if(sol.sorters[i].installed){
            const auto& sp = sol.sorters[i];
            if(isSorter(sp.v1) && !sol.sorters[sp.v1 - N].installed){ reason = "edge to uninstalled sorter"; return false; }
            if(isSorter(sp.v2) && !sol.sorters[sp.v2 - N].installed){ reason = "edge to uninstalled sorter"; return false; }
        }

        // Build edges and check for cycles via Kahn
        vector<pair<int,int>> edges; buildEdges(sol, edges);
        int V = nodes();
        vector<vector<int>> adj(V);
        vector<int> indeg(V,0);
        for(auto [u,v]: edges){
            if(u==v){ reason = "self-loop"; return false; }
            if(v<0 || v>=N+M){ reason = "edge out of range"; return false; }
            adj[u].push_back(v);
            indeg[v]++;
        }
        queue<int> q;
        for(int i=0;i<V;i++) if(indeg[i]==0) q.push(i);
        int popped=0;
        while(!q.empty()){
            int u=q.front(); q.pop(); popped++;
            for(int v: adj[u]) if(--indeg[v]==0) q.push(v);
        }
        if(popped!=V){ reason = "cycle detected"; return false; }

        // Geometry: belts are edges as segments; belts that do not share endpoints must not intersect
        vector<pair<Point,Point>> segs;
        segs.reserve(edges.size());
        for(auto [u,v]: edges){ segs.emplace_back(nodePoint(u), nodePoint(v)); }
        for(size_t i=0;i<segs.size();i++){
            for(size_t j=i+1;j<segs.size();j++){
                // Allow sharing endpoints
                auto [a1,a2] = segs[i];
                auto [b1,b2] = segs[j];
                auto samePoint = [](const Point& A, const Point& B){ return A.x==B.x && A.y==B.y; };
                bool share = samePoint(a1,b1)||samePoint(a1,b2)||samePoint(a2,b1)||samePoint(a2,b2);
                if(share) continue;
                if(segmentsIntersect(a1,a2,b1,b2)){
                    reason = "segment intersection"; return false;
                }
            }
        }
        return true;
    }

    // Compute q_i for i=0..N-1 by propagating per-type probabilities along the DAG
    vector<double> computeQi(const Solution& sol) const {
        vector<pair<int,int>> edges; buildEdges(sol, edges);
        int V = nodes();
        vector<vector<int>> adj(V);
        vector<int> indeg(V,0);
        for(auto [u,v]: edges){ adj[u].push_back(v); indeg[v]++; }
        // topo order
        queue<int> q;
        for(int i=0;i<V;i++) if(indeg[i]==0) q.push(i);
        vector<int> topo; topo.reserve(V);
        while(!q.empty()){ int u=q.front(); q.pop(); topo.push_back(u); for(int v: adj[u]) if(--indeg[v]==0) q.push(v);}        
        vector<double> qi(N,0.0);
        // For each type, propagate
        for(int t=0;t<N;t++){
            vector<double> mass(V,0.0);
            mass[inletId()] = 1.0;
            for(int u: topo){
                if(mass[u]==0.0) continue;
                if(0 <= u && u < N){
                    // processor node
                    if(sol.d[u]==t){ qi[t] += mass[u]; }
                    continue;
                }
                if(u==inletId()){
                    int v = sol.s;
                    mass[v] += mass[u];
                    continue;
                }
                // sorter
                int sid = u - N;
                if(sid>=0 && sid<M && sol.sorters[sid].installed){
                    const auto& sp = sol.sorters[sid];
                    double prob1 = p[sp.k][t];
                    mass[sp.v1] += mass[u] * prob1;
                    mass[sp.v2] += mass[u] * (1.0 - prob1);
                }
            }
        }
        // Clamp minor FP error
        for(double& x: qi){ if(x<0) x=0; if(x>1) x=1; }
        return qi;
    }

    long long absoluteScore(const vector<double>& qi) const {
        long double s = 0.0L;
        for(int i=0;i<N;i++) s += (1.0L - (long double)qi[i]);
        s /= (long double)N; // average over N to match raw score
        return llround(1e9L * s);
    }
};

// --- Helpers ---
static Solution makeBaseline(const Problem& pb){
    Solution base;
    base.d.resize(pb.N);
    for(int i=0;i<pb.N;i++) base.d[i] = i;
    base.sorters.assign(pb.M, SorterSpec{});
    // inlet -> nearest processor
    const long long ix = 0, iy = 5000;
    long long bestd2 = (1LL<<62); int bp = 0;
    for(int i=0;i<pb.N;i++){
        long long dx = pb.procPos[i].x - ix;
        long long dy = pb.procPos[i].y - iy;
        long long d2 = dx*dx + dy*dy;
        if(d2 < bestd2){ bestd2 = d2; bp = i; }
    }
    base.s = bp;
    return base;
}

static long long evaluate(const Problem& pb, const Solution& sol){
    auto qi = pb.computeQi(sol);
    return pb.absoluteScore(qi);
}

static void precomputeArgExtrema(const Problem& pb, vector<int>& argmaxK, vector<int>& argminK){
    argmaxK.assign(pb.K, 0);
    argminK.assign(pb.K, 0);
    for(int k=0;k<pb.K;k++){
        int imx=0, imn=0;
        for(int t=1;t<pb.N;t++){
            if(pb.p[k][t] > pb.p[k][imx]) imx = t;
            if(pb.p[k][t] < pb.p[k][imn]) imn = t;
        }
        argmaxK[k]=imx; argminK[k]=imn;
    }
}

static Solution randomizedSearch(const Problem& pb, const Solution& base, int time_ms_budget, long long& bestScoreOut, uint64_t& samplesOut){
    using clk = chrono::high_resolution_clock;
    auto start = clk::now();
    auto time_ok = [&](){
        auto now = clk::now();
        double ms = chrono::duration<double, milli>(now - start).count();
        return ms < time_ms_budget;
    };

    // RNG
    uint64_t seed = chrono::duration_cast<chrono::nanoseconds>(start.time_since_epoch()).count();
    std::mt19937_64 rng(seed);
    uniform_int_distribution<int> distK(0, max(0, pb.K-1));
    uniform_int_distribution<int> distProc(0, max(0, pb.N-1));

    // Best initialization
    string reason;
    Solution bestSol = base;
    bestScoreOut = evaluate(pb, bestSol);

    // Helper: segment storage for geometry checks (built per candidate)
    auto sharePoint = [](const Point& A, const Point& B){ return A.x==B.x && A.y==B.y; };
    auto addEdgeNoIntersect = [&](vector<pair<int,int>>& edges, const pair<int,int>& e){
        Point a1 = pb.nodePoint(e.first), a2 = pb.nodePoint(e.second);
        for(const auto& ex: edges){
            Point b1 = pb.nodePoint(ex.first), b2 = pb.nodePoint(ex.second);
            if(sharePoint(a1,b1)||sharePoint(a1,b2)||sharePoint(a2,b1)||sharePoint(a2,b2)) continue;
            if(Problem::segmentsIntersect(a1,a2,b1,b2)) return false;
        }
        edges.push_back(e);
        return true;
    };

    uint64_t samples = 0;
    while(time_ok()){
        // Build a completely random multi-sorter candidate edge-by-edge without intersections
        Solution cand;
        cand.d = base.d;
        cand.sorters.assign(pb.M, SorterSpec{});
        vector<pair<int,int>> edges; // for geometry checks only

        // Random order of sorter indices to try to install
        vector<int> order(pb.M);
        iota(order.begin(), order.end(), 0);
        shuffle(order.begin(), order.end(), rng);

        // First, choose a first sorter to try as inlet destination; fallback to processor if cannot
        bool inletSet = false;
        for(int idx=0; idx<(int)order.size() && !inletSet; ++idx){
            int sid = order[idx];
            int k = (pb.K>0 ? distK(rng) : -1);
            if(k<0) break;
            // Choose random v1,v2 among processors only (no installed sorters yet)
            bool installedThis = false;
            for(int att=0; att<20; ++att){
                int v1 = distProc(rng);
                int v2 = distProc(rng);
                cand.sorters[sid].installed = true;
                cand.sorters[sid].k = k;
                cand.sorters[sid].v1 = v1;
                cand.sorters[sid].v2 = v2;
                // Try add sorter exits
                vector<pair<int,int>> localEdges = edges;
                if(!addEdgeNoIntersect(localEdges, {pb.N+sid, v1})) { continue; }
                if(!addEdgeNoIntersect(localEdges, {pb.N+sid, v2})) { continue; }
                // Try inlet -> this sorter
                if(!addEdgeNoIntersect(localEdges, {pb.inletId(), pb.N+sid})) { continue; }
                // Accept
                edges.swap(localEdges);
                inletSet = true;
                installedThis = true;
                break;
            }
            if(!installedThis){
                // revert installation
                cand.sorters[sid] = SorterSpec{};
            }
        }
        if(!inletSet){
            // Set inlet to a random processor that doesn't intersect anything (edges is empty now)
            int v = distProc(rng);
            addEdgeNoIntersect(edges, {pb.inletId(), v});
            cand.s = v;
        }else{
            cand.s = edges.back().second; // last added inlet edge destination
        }

        // Install remaining sorters in random order; destinations can be processors or already installed sorters
        vector<char> installed(pb.M, 0);
        for(int i=0;i<pb.M;i++) if(cand.sorters[i].installed) installed[i]=1;
        for(int sid: order){
            if(installed[sid]) continue; // already installed as first
            int k = (pb.K>0 ? distK(rng) : -1);
            if(k<0) continue;
            // Build candidate exits, picking random destinations from processors and installed sorters
            vector<int> destPool;
            destPool.reserve(pb.N + pb.M);
            for(int i=0;i<pb.N;i++) destPool.push_back(i);
            for(int i=0;i<pb.M;i++) if(installed[i]) destPool.push_back(pb.N + i);
            if(destPool.empty()) continue;
            uniform_int_distribution<size_t> distPool(0, destPool.size()-1);
            bool ok = false;
            for(int att=0; att<20; ++att){
                int v1 = destPool[distPool(rng)];
                int v2 = destPool[distPool(rng)];
                vector<pair<int,int>> localEdges = edges;
                if(!addEdgeNoIntersect(localEdges, {pb.N+sid, v1})) continue;
                if(!addEdgeNoIntersect(localEdges, {pb.N+sid, v2})) continue;
                // Accept install
                edges.swap(localEdges);
                cand.sorters[sid].installed = true;
                cand.sorters[sid].k = k;
                cand.sorters[sid].v1 = v1;
                cand.sorters[sid].v2 = v2;
                installed[sid] = 1;
                ok = true;
                break;
            }
            (void)ok;
        }

        // Validate full candidate (ranges, installed-destination, DAG) and evaluate
        if(!pb.validateSolution(cand, reason)) continue;
        long long sc = evaluate(pb, cand);
        if(sc < bestScoreOut){ bestScoreOut = sc; bestSol = cand; }
        samples++;
    }
    samplesOut = samples;
    return bestSol;
}

static void outputSolution(const Solution& sol){
    int N = (int)sol.d.size();
    int M = (int)sol.sorters.size();
    for(int i=0;i<N;i++){
        if(i) cout << ' ';
        cout << sol.d[i];
    }
    cout << '\n';
    cout << sol.s << '\n';
    for(int i=0;i<M;i++){
        if(sol.sorters[i].installed){
            const auto& sp = sol.sorters[i];
            cout << sp.k << ' ' << sp.v1 << ' ' << sp.v2 << '\n';
        }else{
            cout << -1 << '\n';
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K;
    if(!(cin >> N >> M >> K)) return 0;

    vector<pair<int,int>> proc(N), sorters(M);
    for(int i=0;i<N;i++) cin >> proc[i].first >> proc[i].second;
    for(int i=0;i<M;i++) cin >> sorters[i].first >> sorters[i].second;
    vector<vector<double>> prob(K, vector<double>(N));
    for(int i=0;i<K;i++){
        for(int j=0;j<N;j++) cin >> prob[i][j];
    }

    // Build problem model
    Problem pb;
    pb.N = N; pb.M = M; pb.K = K;
    pb.procPos.resize(N);
    pb.sortPos.resize(M);
    for(int i=0;i<N;i++){ pb.procPos[i] = Point{proc[i].first, proc[i].second}; }
    for(int i=0;i<M;i++){ pb.sortPos[i] = Point{sorters[i].first, sorters[i].second}; }
    pb.p = std::move(prob);

    // Build baseline and search
    Solution base = makeBaseline(pb);
    long long bestScore = 0;
    uint64_t samples = 0;
    Solution bestSol = randomizedSearch(pb, base, 1900, bestScore, samples);

    outputSolution(bestSol);
    cerr << "abs_score=" << bestScore << ", samples=" << samples << "\n";
    return 0;
}
